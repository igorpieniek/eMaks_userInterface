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

joystick* get_joy_pointer(void){
	return &joy;
}

void get_adc_data(joystick* joy,uint32_t* data){
	for(uint8_t i = 0 ; i < NUMBER_OF_AXIS; i++){
		joy->measurements[i].raw_data = data[i];
	}
}

void convert_adc_value(joystick* joy, uint32_t* raw_adc_data){
	get_adc_data(joy,raw_adc_data);
	uint32_t divider = pow(2, joy->bit_resolution);
	//todo Lukas: add offset
	for(uint8_t i = 0 ; i < NUMBER_OF_AXIS;i++){
		if(joy->measurements[i].raw_data == NULL){
			joy->measurements[i].converted_data = -1.0;
			continue;
		}
		joy->measurements[i].converted_data =
				((float)joy->measurements[i].raw_data
				* joy->reference_voltage)/(float)divider;
	}
}

void calculate_percentages_voltage(joystick* joy){
	for(uint8_t i = 0 ; i < NUMBER_OF_AXIS; i++){
		if(joy->measurements[i].converted_data > joy->reference_voltage){
			joy->measurements[i].percentage_value = 100.0;
			continue;
		}
		joy->measurements[i].percentage_value =
				joy->measurements[i].converted_data / joy->reference_voltage *
				100.0;
	}
}

void calculate_joy_data(void){

	joystick* joy = get_joy_pointer();
	convert_adc_value(joy,get_hal_adc_raw_data());
	calculate_percentages_voltage(joy);
}
