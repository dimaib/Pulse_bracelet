#include "hr_defines.h"
#include "arm_math.h"

typedef struct{
uint32_t blockSize;
float32_t rate1Prev;
float32_t derivPrev;
float32_t prevPulses;
float32_t rate2Prev;
float32_t signPrev;
uint32_t num[5];
uint32_t sum;
float32_t tailDeriv[BLOCK_SIZE/4];
float32_t tailSign[BLOCK_SIZE/4];
float32_t buf1[BLOCK_SIZE];
float32_t buf2[BLOCK_SIZE];
float32_t filteredSignal[BLOCK_SIZE];
float32_t prevWindow[BLOCK_SIZE];
arm_biquad_cascade_df2T_instance_f32 *HighPassDetrending;
arm_biquad_cascade_df2T_instance_f32 *LowPassSmoothing;
arm_fir_instance_f32 *LowPassDerivative;
} hr_meter_f32_inst;

void hr_meter_f32_init (hr_meter_f32_inst *inst,
					arm_biquad_cascade_df2T_instance_f32 *HighPassDetrending,
					arm_biquad_cascade_df2T_instance_f32 *LowPassSmoothing,
					arm_fir_instance_f32 *LowPassDerivative);

float32_t hr_meter_f32 (hr_meter_f32_inst *inst, float32_t *window);
