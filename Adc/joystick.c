/*
 * joystick.c
 *
 *  Created on: 29.06.2019
 *      Author: Lukas
 */
#include "joystick.h"
#include <math.h>
 joystick joy ={
		 .bit_resolution = ADC_BIT_RESOLUTION,
		 .reference_voltage = ADC_REFERENCE_VOLTAGE,
 };

 joy_axis axis ={
		 .params =joy_axis_params,
		 .size = sizeof(joy_axis_params)/sizeof(ax_params)
 };

 void joy_params_init(void){
	 for(uint8_t i = 0; i < axis.size; i++){
		 joy.measurements[axis.params[i].index].v_max_normalized =
				 axis.params[i].v_max -axis.params[i].v_neutral;
		 joy.measurements[axis.params[i].index].v_min_normalized =
				 axis.params[i].v_min -axis.params[i].v_neutral;
	 }
 }

joystick* get_joy_pointer(void){
	return &joy;
}

void get_adc_data(joystick* joy,uint32_t* data){
	for(uint8_t i = 0 ; i < NUMBER_OF_CHANNELS; i++){
		joy->measurements[i].raw_data = data[i];
	}
}

void convert_adc_values(void){
	get_adc_data(&joy,get_hal_adc_raw_data());
	uint32_t divider = pow(2, joy.bit_resolution);
	//todo Lukas: add offset
	for(uint8_t i = 0 ; i < NUMBER_OF_CHANNELS;i++){
		if(joy.measurements[i].raw_data == NULL){
			joy.measurements[i].converted_data = -1.0;
			continue;
		}
		joy.measurements[i].converted_data =
				((float)joy.measurements[i].raw_data
				* joy.reference_voltage)/(float)divider;
	}
}
bool is_joy_near_neautral(ax_params params){
	return(joy.measurements[params.index].converted_data > (params.v_neutral - MEASUREMENT_ERROR)
			&& joy.measurements[params.index].converted_data < (params.v_neutral + MEASUREMENT_ERROR ));
}


void calcualate_axis_voltage(ax_params params){
	if(is_joy_near_neautral(params)){
		joy.measurements[params.index].percentage_value = 0.0;
		joy.measurements[params.index].sign = positive;
		return;
	}
	if (joy.measurements[params.index].converted_data >= params.v_max){
		joy.measurements[params.index].percentage_value = 100.0;
		joy.measurements[params.index].sign = positive;
		return;
	}

	if( joy.measurements[params.index].converted_data > params.v_neutral ){
		joy.measurements[params.index].percentage_value =
		fabs((joy.measurements[params.index].converted_data -params.v_neutral)
				/ joy.measurements[params.index].v_max_normalized) * 100.0;
		joy.measurements[params.index].sign = positive;
	}
	else{
		joy.measurements[params.index].percentage_value =
		fabs((joy.measurements[params.index].converted_data -params.v_neutral)
				/ joy.measurements[params.index].v_min_normalized) * 100.0;
		joy.measurements[params.index].sign = negative;
	}
}

///todo Lukas: update tests
void calculate_joy_data(void){
	for(uint8_t i = 0 ; i < axis.size; i++){
		calcualate_axis_voltage(axis.params[i]);
	}
}

