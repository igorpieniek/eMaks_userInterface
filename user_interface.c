/*
 * user_interface.c
 *
 *  Created on: 29.06.2019
 *      Author: Lukas
 */


#include "user_interface.h"
int main(void){
	hal_init();
	while(1){
		if(htim3.Instance->CNT ==500){
			calculate_joy_data();
			can_transmit_data();
		}


	}
}
