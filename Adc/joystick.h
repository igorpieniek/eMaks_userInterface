/*
 * joystick.h
 *
 *  Created on: 29.06.2019
 *      Author: Lukas
 */

#ifndef ADC_JOYSTICK_H_
#define ADC_JOYSTICK_H_
#include "math.h"
#include "adc.h"
#define NUMBER_OF_AXIS 2
typedef struct{
	uint32_t raw_data;
	uint32_t converted_data;
	float  percentage_value;
}adc_data;

typedef struct{
	adc_data measurements[NUMBER_OF_AXIS];
	uint8_t bit_resolution;
	float reference_voltage;
}joystick;


#endif /* ADC_JOYSTICK_H_ */
