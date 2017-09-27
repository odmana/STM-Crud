/*
 * adc.h
 *
 *  Created on: 27Jul.,2017
 *      Author: Ovindu
 */

#ifndef ADC_H_
#define ADC_H_

#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "main.h"
#include "debug.h"

extern int Test_Count;

void ADC_Read_Init();
void ADC_Read_Start();

#endif /* ADC_H_ */
