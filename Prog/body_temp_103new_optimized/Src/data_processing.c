/*
 * data_processing.c
 *
 *  Created on: Oct 10, 2020
 *      Author: ivan
 */

#include "data_processing.h"
#include "hr_defines.h"


/**
 * @details
 * @brief This function limits skew rate of signal to specified limit.
 * @param[in]  *inst      Points to an instance of rate limiter structure.
 * @param[in,out]  pSrc       Input values.
 * @param[in]  limit      Limit.
 * @param[in, out]  prevValue  Previous sample.
 * @return     void
 */

void rate_limiter_f32 (float32_t *pSrc, uint32_t windowLength, float32_t limit, float32_t prevValue){
	float32_t diff = 0;
	for(uint32_t i = 0; i < windowLength; i++){
		diff = pSrc[i] - prevValue;
		if(fabsf(diff) > limit){
			if(signbit(diff)) pSrc[i] = prevValue - limit;
			else pSrc[i] = prevValue + limit;
		}
		prevValue = pSrc[i];
	}
}


/**
 * @details
 * @brief This function limits skew rate of signal to specified limit.
 * @param[in]  *inst        Points to an instance of rate limiter structure.
 * @param[in]  *pSrc        Input values.
 * @param[out] *pDst        Output values.
 * @return     void
 */

void derivative_f32 (float32_t *pSrc, float32_t *pDst, uint32_t windowLength, uint32_t gain, float32_t prevValue){
	for(uint32_t i = 0; i < windowLength; i++){
		pDst[i] = gain*(pSrc[i] - prevValue);
		prevValue = pSrc[i];
	}
}

/**
 * @details
 * @brief This function makes all values below threshold 0.
 * @param[in]  *pSrc          Input values.
 * @param[out] *pDst          Output values.
 * @param[in]  windowLength   Length of window.
 * @param[in]  thrsP          Threshold +.
 * @param[in]  thrsM          Threshold -.
 * @param[out] *tail          Last 10 values.
 * @return     void
 */
void dead_zone_f32 (float32_t *pSrc, uint32_t windowLength, float32_t thrsP, float32_t thrsM, float32_t *tail){
	for(uint32_t i = 0; i < windowLength; i++){
			if(pSrc[i] < thrsP && pSrc[i] > 0) pSrc[i] = 0;
			else if(pSrc[i] > thrsM && pSrc[i] < 0) pSrc[i] = 0;
			if(i >= windowLength - BLOCK_SIZE/4) tail[i] = pSrc[i];
	}
}

/**
 * @details
 * @brief This function finds where function changes sign.
 * @param[in]  *pSrc          Input values.
 * @param[out] *pDst          Output values - if there is maximum then array value is signal amplitude, else there is 0.
 * @param[in]  windowLength   Length of window.
 * @param[out] *tail          Last 10 values of previous window.
 * @param[in]  *curWindow      Filtered signal.
 * @return     void
 */

void sign_f32 (float32_t *pSrc, float32_t *pDst, uint32_t windowLength, float32_t *tail, float32_t *curWindow){
	for(uint32_t i = 0; i < windowLength; i++)
		{
				if(i < TAIL){
				if((pSrc[i] < 0) && (tail[i] > 0)) pDst[i] = curWindow[i];
				else pDst[i] = 0;}
			else{
				if((pSrc[i] < 0) && (pSrc[i - TAIL] > 0)) pDst[i] = curWindow[i];
				else pDst[i] = 0;}
		}
}


uint32_t pulses_f32(float32_t *pSrc, uint32_t *pDst, uint32_t windowLength, float32_t prev){
	uint32_t counter = 0;
	for(uint32_t i = 0; i < windowLength; i++)
	{
		if(pSrc[i] > 0 && prev == 0) {
			pDst[counter] = i;
			counter++;
		}
		prev = pSrc[i];
	}
	return counter;
}


void mins_f32 (float32_t *pSrc, float32_t *pDst, uint32_t windowLength, uint32_t *indexes, uint32_t num){
	float32_t pResult = 0;
	uint32_t pIndex = 0;
	for(uint32_t i = 0; i < num; i++)
	{
		arm_min_f32 (&pSrc[0]+i*windowLength/num, windowLength/num, &pResult, &pIndex);
		pDst[i] = pResult;
		indexes[i] = pIndex;
	}
}