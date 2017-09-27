/*
 * led_flash_task.c
 *
 *  Created on: 24Jul.,2017
 *      Author: Ovindu
 */
#include "main.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "debug.h"
#include "adc.h"

void LED_Flash_Init()
{
//  GPIO_InitTypeDef GPIO_InitStruct;
//
//  /* GPIO Ports Clock Enable */
//  __HAL_RCC_GPIOA_CLK_ENABLE();
//
//  /*Configure GPIO pins */
//  GPIO_InitStruct.Pin = LD2_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  //GPIO_InitStruct.Pull = GPIO_NOPULL;
//  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

void LED_Flash_Start()
{
	static int seconds = 0;
	for (;;) {
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		//debug_log("Time till startup: %d (s)", seconds++);
		//debug_log("ADC read %d times", Test_Count);
		Test_Count = 0;
		osDelay(1000);
	}
}
