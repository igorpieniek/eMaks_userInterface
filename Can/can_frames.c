/*
 * can_frames.c
 *
 *  Created on: 30.06.2019
 *      Author: Lukas
 */
#include "can_frames.h"
//todo Lukas: attach hardware function for transmit
extern coding_parameter uint16_5_5 ;
extern coding_parameter int16_5_5 ;

can_functions hardware_can;

can_message can_messages[]={
		{.frame_id = JOY_ERROR_FRAME_ID ,.data_lenght = JOY_ERROR_FRAME_LENGHT},
		{.frame_id = JOY_DATA_FRAME_ID, .data_lenght = JOY_ADC_READINGS_LENGHT}
};

void fill_joy_data_frame(can_message* message, joystick* joy, uint8_t axis_number){

	float axis_data =joy->measurements[axis_number].percentage_value;

	uint16_t encoded_axis_data = encode_float_to_uint16(axis_data,uint16_5_5);

	uint16_t axis_code;
	(axis_number == X_AXIS_INDEX)?
			(axis_code = CAN_X_AXIS_CODE):(axis_code = CAN_Y_AXIS_CODE);


	uint8_t data_to_encode[]={
			(uint8_t)(axis_code >> 8),
			(uint8_t)axis_code,
			(uint8_t)(encoded_axis_data >> 8 ),
			(uint8_t)encoded_axis_data
	};
	message->data  = encode_frame_big_endian(data_to_encode,message->data_lenght);
}
void fill_error_frame(void){
	//todo Lukas: implement this later
}
uint8_t is_hardware_attached_to_pointers(void){
	return ( hardware_can.can_transmit ==NULL)? 0 : 1;
}


void can_transmit_data(void){
	if(!is_hardware_attached_to_pointers()){
		return;
	}
 	can_message* joy_frame= &can_messages[CAN_JOY_FRAME_INDEX];
 	for( uint8_t i = 0 ; i < NUMBER_OF_AXIS ; i++){
 		fill_joy_data_frame(joy_frame,get_joy_pointer(),i);
 		hardware_can.can_transmit(joy_frame->frame_id,joy_frame->data);
 	}
}
