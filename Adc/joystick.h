/*
 * joystick.h
 *
 *  Created on: 29.06.2019
 *      Author: Lukas
 */

//todo Lukas : calibrate joystick better
#ifndef ADC_JOYSTICK_H_
#define ADC_JOYSTICK_H_
#include <math.h>
#include "adc.h"
#define X_AXIS_INDEX   2
#define Y_AXIS_INDEX   1
#define JOYSTICK_OFFSET  1.75f //Volts
#define MAX_JOY_VOLTAGE  2.30f
#define PERCENTAGE_DENOMINATOR 	MAX_JOY_VOLTAGE - JOYSTICK_OFFSET
#define PERCENTAGE_OFFSET 50.0f

typedef struct{
	uint32_t raw_data;
	float converted_data;
	float  percentage_value;
}adc_data;

typedef struct{
	adc_data measurements[NUMBER_OF_CHANNELS];
	uint8_t bit_resolution;
	float reference_voltage;
}joystick;

joystick* get_joy_pointer(void);
void get_adc_data(joystick* joy,uint32_t* data);
void convert_adc_value(joystick* joy, uint32_t* raw_adc_data);
void calculate_percentages_voltage(joystick* joy);
void calculate_joy_data(void);

#endif /* ADC_JOYSTICK_H_ */
