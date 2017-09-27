/*
 * can.h
 *
 *  Created on: 7Aug.,2017
 *      Author: Ovindu
 */

#ifndef CAN_H_
#define CAN_H_

#define CAN_QUEUE_SIZE 2

#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "debug.h"

struct {
	uint8_t queuePosition;
	CanRxMsgTypeDef queue[CAN_QUEUE_SIZE];
} typedef CanQueue;

void Can_Send_Start();
void Can_Recieve_Start();

#endif /* CAN_H_ */
