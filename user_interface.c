/*
 * user_interface.c
 *
 *  Created on: 29.06.2019
 *      Author: Lukas
 */


#include "user_interface.h"
extern TIM_HandleTypeDef htim3;

int main(void){
	hal_init();
	joy_params_init();
	modeManagerInit();
	while(1){
		if(htim3.Instance->CNT ==900 && isJoystickMode()){
			convert_adc_values();
			calculate_joy_data();
			can_transmit_data();
		}
	}
}
