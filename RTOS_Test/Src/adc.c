/*
 * adc.c
 *
 *  Created on: 27Jul.,2017
 *      Author: Ovindu
 */
#include "adc.h"

extern ADC_HandleTypeDef hadc1;
uint16_t adcValues[2]; //ADC Readings
int Test_Count = 0;

void ADC_Read_Init() {
	// -- Enables ADC and starts conversion of the regular channels.
	if (HAL_ADC_Start(&hadc1) != HAL_OK)
		Error_Handler();

	// -- Enables ADC DMA request
	if (HAL_ADC_Start_DMA(&hadc1, (uint32_t*) adcValues, 2) != HAL_OK)
		Error_Handler();
}

void ADC_Read_Start() {
	HAL_ADC_Start(&hadc1);
	for (;;) {
//		if (HAL_ADC_PollForConversion(&hadc1, 10000) == HAL_OK) {
//			adcValue[0] = HAL_ADC_GetValue(&hadc1);
//		}
//		if (HAL_ADC_PollForConversion(&hadc1, 10000) == HAL_OK) {
//			adcValue[1] = HAL_ADC_GetValue(&hadc1);
//		}
//
//		Test_Count++;

		debug_log("ADC Values - 0:[%d] \t 1:[%d]", adcValues[0], adcValues[1]);
		osDelay(1000);
	}
}
