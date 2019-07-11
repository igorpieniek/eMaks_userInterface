/*
 * coders.h
 *
 *  Created on: 30.06.2019
 *      Author: Lukas
 */

#ifndef CAN_CODER_H_
#define CAN_CODER_H_
#include <math.h>

/* type defines for ceedling tests*/
#include "adc.h"

typedef struct{
	uint16_t bits;
	uint16_t offset;
	float range;
}coding_parameter;

uint16_t encode_float_to_uint16(float value, coding_parameter param);
uint8_t* encode_frame_big_endian(uint8_t* data , uint8_t data_length);

#endif /* CAN_CODER_H_ */
