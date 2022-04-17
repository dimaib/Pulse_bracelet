/*
 * hr_defines.h
 *
 *  Created on: Oct 10, 2020
 *      Author: ivan
 */

#ifndef INC_HR_DEFINES_H_
#define INC_HR_DEFINES_H_

/* ----------------------------------------------------------------------
** Macro Defines
** ------------------------------------------------------------------- */

#define BLOCK_SIZE            224
#define NUM_TAPS_DETRENDING   2
#define NUM_TAPS_SMOOTHING    4
#define NUM_TAPS_DERIVATIVE   24
#define TEST_LENGTH_SAMPLES   1000
#define TAIL 12
#define AVERAGING 1
#define AV_FACTOR 15 //always >= 2!!!!!!!!!

#endif /* INC_HR_DEFINES_H_ */
