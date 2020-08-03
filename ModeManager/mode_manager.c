/*
 * mode_manager.c
 *
 *  Created on: 03.08.2020
 *      Author: Igor
 */

#include "mode_manager.h"


void modeManagerInit(){
	driveMode = EN;
	RCmode = MODE_JOYSICK;
	HAL_TIM_Base_Start_IT(&PROCESS_TIMER);
}


void getData_Rx(uint32_t frame_id, uint8_t* data, uint8_t dlc){

}


uint8_t isJoystickMode(){
	if (driveMode == EN && RCmode == MODE_JOYSICK){
		return 1;
	}
	else return 0;
}


