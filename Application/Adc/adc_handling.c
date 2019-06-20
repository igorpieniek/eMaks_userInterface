/*
 * adc_handling.c
 *
 *  Created on: 20.06.2019
 *      Author: Lukas
 */
#include "adc_handling.h"

uint32_t* convert_adc_values(uint32_t* adc_values){
     adc_values = get_adc_raw_data();

     for(uint8_t i = 0 ; i < NUMBER_OF_CHANNELS; i++){
    	 adc_values[i]= adc_values[i]* 3.3f / 4096.0;
     }
}


void process_received_data(void){

}
