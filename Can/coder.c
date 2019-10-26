/*
 * coders.c
 *
 *  Created on: 30.06.2019
 *      Author: Lukas
 */
#include "coder.h"
#include <malloc.h>

coding_parameter uint16_128 ={.bits =16, .offset = 0,.range = 128};
coding_parameter int16_5_5 = {.bits = 16, .offset = 127,.range =100};

uint16_t encode_float_to_uint16(float value, coding_parameter param){
	if( value > param.range){
		return param.range;
	}
	return(uint16_t)((value + param.offset) * pow(2,param.bits) /param.range);
}

uint8_t* encode_frame_big_endian(uint8_t* data , uint8_t data_length){
	if(data_length == 0){
		return NULL;
	}
	 uint8_t* encoded_data = (uint8_t*)calloc(data_length, sizeof(uint8_t));
	for( uint8_t i = 1 ; i <= data_length  ;i++){
		encoded_data[i - 1] = data[data_length-i];
	}
	return encoded_data;
}

