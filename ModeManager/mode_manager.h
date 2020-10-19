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
#include "can.h"
#include "stm32f1xx_hal_tim.h"

#define IDLE_TIMER htim2
#define PROCESS_TIMER htim3

#define VELOCITY_FRAME_ID   0x23E //TODO
#define TURN_FRAME_ID  		0x24D
#define STATUS_FRAME_ID  	0x25D

#define I3_VELOCITY_FRAME_ID    0x26D
#define I3_TURN_FRAME_ID  		0x27D

#define STATUS_MODE_BYTE      2
#define STATUS_PERMITION_BYTE 1

#define JOYSTICK_MODE_MSG 	0x00
#define ACRO_MODE_MSG		0x01
#define SEMI_MODE_MSG		0x02
#define AUTONOMOUS_MODE_MSG 0x03

#define ENABLE_DRIVE_MSG  	0x01
#define DISABLE_DRIVE_MSG 	0x00

// Tx
#define STEERING_FRAME_LENGTH 4
#define STEERING_VELOCITY_FRAME_ID  0x21D //old x axis
#define STEERING_TURN_FRAME_ID   	0x22D // old y axis

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

enum SEND_MODE{
	TURN = 0,
	VELOCITY,
	STATUS
};

hal_can_messageRx  canMsgRx;
hal_can_messageTx  canMsgTx;
void modeManagerInit();
uint8_t isJoystickMode();
void getData_Rx(uint32_t frame_id, uint8_t* data, uint8_t dlc);
void convertStatusData_Rx(uint8_t * data);
enum RC_MODE getRCmodeStatus_Rx(uint8_t status);
enum DRIVE_MODE getDriveModestatus_Rx(uint8_t permition);
void statusUpdate(enum RC_MODE RCstatus, enum DRIVE_MODE drivestatus);

void setVelocity(uint8_t* vel, enum MSG_ORIGIN origin);
void setTurn(uint8_t* turn, enum MSG_ORIGIN origin);

uint8_t turnPermission(enum MSG_ORIGIN origin);
uint8_t velocityPermission(enum MSG_ORIGIN origin);

void sendMsg(enum SEND_MODE mode, uint8_t * msgData);
void custom_hal_can_send(uint32_t frame_id, uint32_t dlc);
void fill_frame();

void startIdleTimer();
void stopIdleTimer();
void resetIdleTimer();




#endif /* MODEMANAGER_MODE_MANAGER_H_ */
