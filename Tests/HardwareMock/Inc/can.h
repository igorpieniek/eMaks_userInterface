/*
 * can.h
 *
 *  Created on: 29.06.2019
 *      Author: Lukas
 */

#ifndef HARDWAREMOCK_CAN_H_
#define HARDWAREMOCK_CAN_H_
#include "adc.h"

void hal_can_send(uint16_t frame, uint8_t data_lenght, uint8_t* data);
#endif /* HARDWAREMOCK_CAN_H_ */
