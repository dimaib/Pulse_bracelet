/*
 * data_processing.h
 *
 *  Created on: Oct 10, 2020
 *      Author: ivan
 */

#ifndef INC_DATA_PROCESSING_H_
#define INC_DATA_PROCESSING_H_

#define ARM_MATH_CM3

#include <math.h>
#include "arm_math.h"



//this function limits skew rate of signal to specified limit.
void rate_limiter_f32 (float32_t *pSrc, uint32_t windowLength, float32_t limit, float32_t prevValue);





//this function finds first derivative of signal
void derivative_f32 (float32_t *pSrc, float32_t *pDst, uint32_t windowLength, uint32_t gain, float32_t prevValue);



//this function makes all values below threshold 0.
void dead_zone_f32 (float32_t *pSrc, uint32_t windowLength, float32_t thrsP, float32_t thrsM, float32_t *tail);

//this function finds whether sign has changed within specified window.
void sign_change_f32 (float32_t *pSrc, float32_t *pDst, uint32_t windowLength, float32_t *tail, float32_t *prevWindow, float32_t *curWindow);
 
 
//----------
void sign_f32 (float32_t *pSrc, float32_t *pDst, uint32_t windowLength, float32_t *tail, float32_t *curWindow);

uint32_t pulses_f32(float32_t *pSrc, uint32_t *pDst, uint32_t windowLength, float32_t prev);

void mins_f32 (float32_t *pSrc, float32_t *pDst, uint32_t windowLength, uint32_t *indexes, uint32_t num);
#endif /* INC_DATA_PROCESSING_H_ */
