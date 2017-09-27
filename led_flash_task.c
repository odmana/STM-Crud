/*
 * led_flash_task.c
 *
 *  Created on: 24Jul.,2017
 *      Author: Ovindu
 */
#include "main.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

void LED_Flash_Init()
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pins */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  //GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

void LED_Flash_Start()
{
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	osDelay(1000);
}
