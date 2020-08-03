/*
 * mode_manager.h
 *
 *  Created on: 03.08.2020
 *      Author: Igor
 */

#ifndef MODEMANAGER_MODE_MANAGER_H_
#define MODEMANAGER_MODE_MANAGER_H_

#include "main.h"
#include "tim.h"
#include "stm32f1xx_hal_tim.h"

#define IDLE_TIMER htim4
#define PROCESS_TIMER htim3

void modeManagerInit();
uint8_t isJoystickMode();
void getData_Rx(uint32_t frame_id, uint8_t* data, uint8_t dlc);

enum RC_MODE{
	MODE_JOYSICK = 0,
	MODE_AUTONOMOUS,
	MODE_SEMI,
	MODE_ACRO
}RCmode;

enum DRIVE_MODE{
	DIS = 0,
	EN
}driveMode;

enum MSG_ORIGIN{
	RC = 0,
	I3
};




#endif /* MODEMANAGER_MODE_MANAGER_H_ */
