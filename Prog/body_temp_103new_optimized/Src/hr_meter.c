#include "hr_defines.h"
#include "data_processing.h"
#include "arm_math.h"
#include "hr_meter.h"



void hr_meter_f32_init (hr_meter_f32_inst *inst,
					arm_biquad_cascade_df2T_instance_f32 *HighPassDetrending,
					arm_biquad_cascade_df2T_instance_f32 *LowPassSmoothing,
					arm_fir_instance_f32 *LowPassDerivative)
{
	inst->rate1Prev = 0;
	inst->derivPrev = 0;
	inst->rate2Prev = 0;
	inst->signPrev = 0;
	inst->blockSize = BLOCK_SIZE;
	inst->HighPassDetrending = HighPassDetrending;
	inst->LowPassSmoothing = LowPassSmoothing;
	inst->LowPassDerivative = LowPassDerivative;
	for(uint32_t j=1; j < 5; j++) inst->num[j] = 1;
	inst->sum = 5;
}