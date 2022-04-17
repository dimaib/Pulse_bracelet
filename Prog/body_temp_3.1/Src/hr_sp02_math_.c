#include "filters.h"
//#include "samples.h"
#include "data_processing.h"
#include "arm_math.h"
#include "stdio.h"
#include "string.h"
#include "hr_spo2_math.h"
#include "main.h"



/* ----------------------------------------------------------------------
** Filters' instances declaration.
** ------------------------------------------------------------------- */
	//2-section IIR filter used to eliminate very low frequencies
	arm_biquad_cascade_df2T_instance_f32 HighPassDetrending;
	//4-section IIR filter used for eliminating high-frequency noise in PPG signal
	arm_biquad_cascade_df2T_instance_f32 LowPassSmoothing;
	//24-order FIR filter used for smoothing signal's derivative
	arm_fir_instance_f32 LowPassDerivative;
	//2-section IIR filter used to eliminate very low frequencies
	arm_biquad_cascade_df2T_instance_f32 HighPassDetrendingIR;
	//4-section IIR filter used for eliminating high-frequency noise in PPG signal
	arm_biquad_cascade_df2T_instance_f32 LowPassSmoothingIR;
	/* -------------------------------------------------------------------
	* Declare State buffer of size (numTaps + blockSize - 1) for each filter
	* ------------------------------------------------------------------- */

	static float32_t HighPassDetrendingStateF32[NUM_TAPS_DETRENDING*2];

	static float32_t LowPassSmoothingStateF32[NUM_TAPS_SMOOTHING*2];
	
	static float32_t HighPassDetrendingStateF32IR[NUM_TAPS_DETRENDING*2];

	static float32_t LowPassSmoothingStateF32IR[NUM_TAPS_SMOOTHING*2];

	static float32_t LowPassDerivativeStateF32[BLOCK_SIZE + NUM_TAPS_DERIVATIVE - 1];
	uint32_t blockSize = BLOCK_SIZE;
	uint32_t numBlocks = TEST_LENGTH_SAMPLES/BLOCK_SIZE;
	static float32_t buf1[BLOCK_SIZE];
	static float32_t buf2[BLOCK_SIZE];
	static float32_t filteredSignalIR[BLOCK_SIZE];
  static float32_t filteredSignal[BLOCK_SIZE];

	float32_t ratePrevIR = 0;
	float32_t derivPrev = 0;
  float32_t ratePrev = 0;
	float32_t tail[TAIL] = {0};
	float32_t tail2[TAIL] = {0};
	float32_t tailIR[TAIL] = {0};
	float32_t tailBuf[TAIL] = {0};
	float32_t tailBufIR[TAIL] = {0};
	float32_t prevPulses = 0;
	uint32_t indexesP[TAIL] = {0};
	uint32_t indexesM[TAIL] = {0};
	
	float32_t aIR = 0;
	float32_t a = 0;
	float32_t hr = 80;
	uint32_t num[AV_FACTOR] = {0};
	float32_t spo2a[AV_FACTOR] = {0};
	float32_t spo2;

void hr_filter_init()
{
  /* initialize all filters. */
  arm_biquad_cascade_df2T_init_f32(&HighPassDetrending, NUM_TAPS_DETRENDING, (float32_t *)&HighPassDetrendingCoeffsF32[0], &HighPassDetrendingStateF32[0]);
  arm_biquad_cascade_df2T_init_f32(&LowPassSmoothing, NUM_TAPS_DETRENDING, (float32_t *)&LowPassSmoothingCoeffsF32[0], &LowPassSmoothingStateF32[0]);
  arm_fir_init_f32(&LowPassDerivative, NUM_TAPS_DERIVATIVE, (float32_t *)&LowPassDerivativeCoeffsF32[0], &LowPassDerivativeStateF32[0], blockSize);
	arm_biquad_cascade_df2T_init_f32(&HighPassDetrendingIR, NUM_TAPS_DETRENDING, (float32_t *)&HighPassDetrendingCoeffsF32[0], &HighPassDetrendingStateF32IR[0]);
  arm_biquad_cascade_df2T_init_f32(&LowPassSmoothingIR, NUM_TAPS_DETRENDING, (float32_t *)&LowPassSmoothingCoeffsF32[0], &LowPassSmoothingStateF32IR[0]);
	#if AVERAGING > 0
	for(uint32_t i=0; i < AV_FACTOR; i++)
	{
		num[i] = 2;
		spo2a[i] = 99;
	}
	#endif
}

void hr_math_(float32_t *testInputR, float32_t *testInputIR)
{
	uint32_t sum = 0;//sum of samples
	float32_t ls = 0;//local sum of SpO2
	float32_t meanR = 0;
	float32_t meanIR = 0;

	arm_mean_f32 (&testInputR[0], blockSize, &meanR);
	arm_mean_f32 (&testInputIR[0], blockSize, &meanIR);
	
	if(meanIR>20000&&meanR>20000){
		float32_t rmsIR = 0;
		float32_t meanR = 0;
		float32_t meanIR = 0;
		arm_mean_f32 (&testInputR[0], blockSize, &meanR);
		arm_mean_f32 (&testInputIR[0], blockSize, &meanIR);
		//--------Red filtering-----------
		arm_biquad_cascade_df2T_f32(&HighPassDetrendingIR, &testInputR[0], &buf1[0], blockSize);
		rate_limiter_f32(&buf1[0], blockSize, 10, ratePrevIR);
		arm_biquad_cascade_df2T_f32(&LowPassSmoothingIR, &buf1[0], &filteredSignal[0], blockSize);
		for(uint32_t j=0; j < TAIL; j++) tailBuf[j] = filteredSignal[blockSize - TAIL + j - 1];
		for(int32_t j=blockSize-1; j > 0; j--)                                                      //add delay
			if(j < TAIL) filteredSignal[j] = tail2[j];	else filteredSignal[j] = filteredSignal[j-TAIL];//-------------------
		for(uint32_t j=0; j < TAIL; j++) tail2[j] = tailBuf[j];                                     //-------------------
		//-------------------------------
		arm_biquad_cascade_df2T_f32(&HighPassDetrending, &testInputIR[0], &buf1[0], blockSize);
		rate_limiter_f32(&buf1[0], blockSize, 10, ratePrev);
		arm_biquad_cascade_df2T_f32(&LowPassSmoothing, &buf1[0], &filteredSignalIR[0], blockSize);
		arm_rms_f32 (&filteredSignalIR[0], blockSize, &rmsIR);
		for(uint32_t j=0; j < TAIL; j++) tailBufIR[j] = filteredSignalIR[blockSize - TAIL + j - 1];
		derivative_f32 (&filteredSignalIR[0], &buf1[0], blockSize, 1, derivPrev);
		arm_fir_f32(&LowPassDerivative, &buf1[0], &buf2[0], blockSize);
		//for(uint32_t j=0; j < blockSize; j++){ printf("%.5f\r\n", buf2[j]); HAL_Delay(1);}
		for(uint32_t j=0; j < TAIL; j++) tail[j] = buf2[blockSize - TAIL + j - 1];
		//dead_zone_f32 (&buf2[0], blockSize, 0, -8, &tail[0]);//3
		for(int32_t j=blockSize-1; j > 0; j--)                                                      //add delay
			if(j < TAIL) filteredSignalIR[j] = tailIR[j];	else filteredSignalIR[j] = filteredSignalIR[j-TAIL];//-------------------
		for(uint32_t j=0; j < TAIL; j++) tailIR[j] = tailBufIR[j];                                      //-------------------
		//for(uint32_t j=0; j < blockSize; j++){ printf("%.5f\r\n", filteredSignal[j]); HAL_Delay(1);}
		sign_f32 (&buf2[0], &buf1[0], blockSize, &tail[0], &filteredSignalIR[0]);
		dead_zone_f32 (&buf1[0], blockSize, 50, 0, &tailBufIR[0]);//39
		////dead_zone_f32 (&buf1[0], blockSize, rmsIR/3, 0, &tailBufIR[0]);//39
		#if AVERAGING > 0
		float32_t sum = 0;//sum of samples
		float32_t ls = 0;//local sum of SpO2
		for(uint32_t j=AV_FACTOR-1; j > 0; j--) num[j] = num[j-1];
		num[0] = pulses_f32(&buf1[0], &indexesP[0], blockSize, prevPulses);
		//for(uint32_t j=0; j < blockSize; j++){ printf("%.5f\r\n", buf2[j]); HAL_Delay(1);}
		mins_f32 (&filteredSignalIR[0], &buf1[0], blockSize, &indexesM[0], num[0]);
		for(uint32_t j=0; j < AV_FACTOR; j++) sum += num[j];
		sum /= AV_FACTOR;
		aIR = fabs(filteredSignalIR[indexesP[0]]) + fabs(filteredSignalIR[indexesM[0]]);
		a = fabs(filteredSignal[indexesP[0]]) + fabs(filteredSignal[indexesM[0]]);
		ls = (a*meanIR)/(aIR*meanR);
		for(uint32_t j=AV_FACTOR-1; j > 0; j--) spo2a[j] = spo2a[j-1];
		spo2a[0] = 104-ls*17;//if(num[0] != 0) 
		for(uint32_t j=0; j < AV_FACTOR; j++) ls += spo2a[j];
		spo2 = ls/AV_FACTOR;
		hr = sum*60*100/blockSize;//averaged number of maximums in window*60seconds*100Hz/window length
		printf("heart rate is %.5f, SpO2 is %.5f\r\n", hr, spo2);		
		#else
		float32_t ls = 0;
		num[0] = pulses_f32(&buf1[0], &indexesP[0], blockSize, prevPulses);
		mins_f32 (&filteredSignalIR[0], &buf1[0], blockSize, &indexesM[0], num[0]);
		aIR = fabs(filteredSignalIR[indexesP[0]]) + fabs(filteredSignalIR[indexesM[0]]);
		a = fabs(filteredSignal[indexesP[0]]) + fabs(filteredSignal[indexesM[0]]);
		ls = (a*meanIR)/(aIR*meanR);
		spo2 = 104-ls*17;//if(num[0] != 0) 
		hr = num[0]*60*100/blockSize;
		printf("heart rate is %.5f, SpO2 is %.5f\r\n", hr, spo2);
		#endif
		
		Puls_serv=hr;
		if(spo2<94) 		SpO2=94;
		else if(spo2>98)SpO2=98;
		else						SpO2=(uint8_t)spo2;			
		//sprintf(buf,"heart rate is %.2f, SpO2 is %d\r\n", Puls_serv, SpO2);
		//HAL_UART_Transmit_IT(&huart1,(uint8_t*)buf,strlen(buf));
	}else{
		Puls_serv=0;
		SpO2=0;
	}
	for(uint16_t ii=0;ii<BLOCK_SIZE;ii++){
		testInputR[ii]=0;
		testInputIR[ii]=0;
	}
}