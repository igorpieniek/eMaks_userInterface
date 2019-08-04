/*
 * adc.h
 *
 *  Created on: 29.06.2019
 *      Author: Lukas
 */

#ifndef HARDWAREMOCK_ADC_H_
#define HARDWAREMOCK_ADC_H_

#define uint8_t  unsigned char
#define uint32_t unsigned short
#define uint16_t unsigned  int
#define uint64_t unsigned long


#define NUMBER_OF_CHANNELS   4
#define ADC_BIT_RESOLUTION	   12
#define ADC_REFERENCE_VOLTAGE  3.3

uint32_t* get_hal_adc_raw_data(void);
#endif /* HARDWAREMOCK_ADC_H_ */
