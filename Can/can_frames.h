/*
 * can_frames.h
 *
 *  Created on: 30.06.2019
 *      Author: Lukas
 */

#ifndef CAN_CAN_FRAMES_H_
#define CAN_CAN_FRAMES_H_
#include "coder.h"
#include "joystick.h"
#include "can.h"

/* see can protocol for details ,can_commons repo in the same organization */
#define JOY_ERROR_FRAME_ID 0xE0
#define JOY_DATA_FRAME_ID  0xF0

#define JOY_ERROR_FRAME_LENGHT  2
#define JOY_ADC_READINGS_LENGHT 4

#define CAN_X_AXIS_CODE   0
#define CAN_Y_AXIS_CODE	  1

//todo Lukas: make it more generic
#define CAN_JOY_FRAME_INDEX   0
#define CAN_ERROR_FRAME_INDEX 1
typedef struct{
	uint8_t* data;
	uint8_t dlc;
	uint16_t frame_id;
}can_message;


typedef struct{
	void (*can_transmit)(uint16_t, uint8_t, uint8_t*);
	uint8_t hardware_functions_attached;
}can_functions;

void fill_joy_data_frame(can_message* message, joystick* joy, uint8_t axis_number);
void can_transmit_data(void);
uint8_t is_hardware_attached_to_pointers(void);

#endif /* CAN_CAN_FRAMES_H_ */
