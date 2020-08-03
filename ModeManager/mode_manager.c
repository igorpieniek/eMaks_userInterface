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
	if (frame_id == STATUS_FRAME_ID) convertStatusData_Rx( data); // function also update status in modemanager
	else if ( frame_id == VELOCITY_FRAME_ID ) 		setVelocity( data , RC );
	else if ( frame_id == I3_VELOCITY_FRAME_ID )	setVelocity( data ,I3  );
	else if ( frame_id == TURN_FRAME_ID )			setTurn( data, RC  );
	else if ( frame_id == I3_TURN_FRAME_ID )	 	setTurn( data, I3  );
}

void convertStatusData_Rx(uint8_t * data){

	uint8_t status = data[STATUS_MODE_BYTE];
	uint8_t permition = data[STATUS_PERMITION_BYTE];
	statusUpdate(getRCmodeStatus_Rx( status ), getDriveModestatus_Rx( permition ) );
}

void setVelocity(uint8_t* vel, enum MSG_ORIGIN origin){
	if (velocityPermission(origin)) sendMsg(VELOCITY, vel);
}
void setTurn(uint8_t* turn, enum MSG_ORIGIN origin){
	if (turnPermission(origin)) sendMsg(TURN,turn);
}

void sendMsg(enum SEND_MODE mode, uint8_t * msgData){
	if (mode == TURN && sizeof(msgData)==STEERING_FRAME_LENGTH ){
		hal_can_send( STEERING_VELOCITY_FRAME_ID, STEERING_FRAME_LENGTH , msgData);
	}
	else if (mode == VELOCITY && sizeof(msgData)==STEERING_FRAME_LENGTH){
		hal_can_send( STEERING_TURN_FRAME_ID,  STEERING_FRAME_LENGTH , msgData);
	}
}


enum RC_MODE getRCmodeStatus_Rx(uint8_t status){
	if (status == JOYSTICK_MODE_MSG ) 		return MODE_JOYSICK;
	else if(status == ACRO_MODE_MSG ) 		return MODE_ACRO;
	else if(status == SEMI_MODE_MSG ) 		return MODE_SEMI;
	else if(status == AUTONOMOUS_MODE_MSG ) return MODE_AUTONOMOUS;
}

enum DRIVE_MODE getDriveModestatus_Rx(uint8_t permition){
	if (permition == ENABLE_DRIVE_MSG  ) 		return EN;
	else if(permition ==  DISABLE_DRIVE_MSG ) 	return DIS;
}


void statusUpdate(enum RC_MODE RCstatus, enum DRIVE_MODE drivestatus){
	RCmode = RCstatus;
	driveMode = drivestatus;
	if (RCstatus !=MODE_JOYSICK){
		startIdleTimer();
	}
	else stopIdleTimer();
}
void startIdleTimer(){
	HAL_TIM_Base_Start_IT(&IDLE_TIMER);
}

void stopIdleTimer(){
	HAL_TIM_Base_Stop_IT(&IDLE_TIMER);
	resetIdleTimer();
}
void resetIdleTimer(){
	__HAL_TIM_SET_COUNTER(&IDLE_TIMER, 0);
}

uint8_t velocityPermission(enum MSG_ORIGIN origin){
	resetIdleTimer();
	if (driveMode == EN){
		if(origin == RC && (RCmode == MODE_ACRO ||
  	   	   	     	 	 	RCmode == MODE_SEMI) ){
			return 1;
		}
		else if(origin == I3 && (RCmode == MODE_AUTONOMOUS) ){
			return 1;
		}
		else return 0;
	}
	else return 0;
}

uint8_t turnPermission(enum MSG_ORIGIN origin){
	resetIdleTimer();
	if (driveMode == EN){
		if(origin == RC && RCmode == MODE_ACRO){
			return 1;
		}
		else if(origin == I3 && (RCmode == MODE_AUTONOMOUS ||
				   	   	   	     RCmode == MODE_SEMI) ){
			return 1;
		}
		else return 0;
	}
	else return 0;
}

uint8_t isJoystickMode(){
	if (driveMode == EN && RCmode == MODE_JOYSICK){
		return 1;
	}
	else return 0;
}


