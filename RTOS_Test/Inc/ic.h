/*
 * ic.h
 *
 *  Created on: 3Aug.,2017
 *      Author: Ovindu
 */

#ifndef IC_H_
#define IC_H_

#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "debug.h"

void IC_Init();
void IC_Report_Start();
//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

#endif /* IC_H_ */
