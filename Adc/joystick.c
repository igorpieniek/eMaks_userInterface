/*
 * joystick.c
 *
 *  Created on: 29.06.2019
 *      Author: Lukas
 */
#include "joystick.h"
 joystick joy ={
		 .bit_resolution = ADC_BIT_RESOLUTION,
		 .reference_voltage = ADC_REFERENCE_VOLTAGE
 };

joystick* get_joy_value(void){
	return &joy;
}

void get_adc_data(float* raw_data){
	uint32_t* raw = get_adc_raw_data();
	for(uint8_t i = 0 ; i < NUMBER_OF_AXIS; i++){
		joy.measurements[i].raw_data = raw[i];
	}
}

void convert_adc_value(joystick* joy){
	uint32_t divider = pow(2, joy->bit_resolution);
	for(uint8_t i = 0 ; i < NUMBER_OF_AXIS;i++){
		joy->measurements[i].converted_data =
				((float)joy->measurements[i].raw_data
				* joy->reference_voltage)/(float)divider;
	}
}

void calculate_percentages_voltage(joystick* joy){

	for(uint8_t i = 0 ; i < NUMBER_OF_AXIS; i++){
		joy->measurements[i].percentage_value =
				joy->measurements[i].converted_data * joy->reference_voltage *
				100.0;
	}
}

