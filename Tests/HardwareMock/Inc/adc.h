/*
 * adc.h
 *
 *  Created on: 29.06.2019
 *      Author: Lukas
 */

#ifndef HARDWAREMOCK_ADC_H_
#define HARDWAREMOCK_ADC_H_

#define uint8_t  unsigned short
#define uint32_t unsigned long

#define ADC_BIT_RESOLUTION	   12
#define ADC_REFERENCE_VOLTAGE  3.3

uint32_t* get_hal_adc_raw_data(void);
#endif /* HARDWAREMOCK_ADC_H_ */
