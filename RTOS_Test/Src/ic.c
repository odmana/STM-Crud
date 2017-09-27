/* Includes ------------------------------------------------------------------*/

#include "ic.h"

extern TIM_HandleTypeDef htim1;

void IC_Init() {
	/*##-3- Start the Input Capture in interrupt mode ##########################*/
	if (HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1) != HAL_OK) {
		/* Starting Error */
		Error_Handler();
	}
	/*##-3- Start the Input Capture in interrupt mode ##########################*/
	if (HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2) != HAL_OK) {
		/* Starting Error */
		Error_Handler();
	}
}

/* Captured Values */
volatile uint32_t uwIC2Value1 = 0;
volatile uint32_t uwIC2Value2 = 0;
volatile uint32_t uwDiffCapture = 0;

/* Capture index */
volatile uint16_t uhCaptureIndex = 0;

/* Frequency Value */
volatile uint32_t uwFrequency = 0;

/**
 * @brief  Conversion complete callback in non blocking mode
 * @param  htim : hadc handle
 * @retval None
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	//uint32_t clockSpd = (SystemCoreClock/2) / htim->Init.Prescaler;

	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) {
		if (uhCaptureIndex == 0) {
			/* Get the 1st Input Capture value */
			uwIC2Value1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
			uhCaptureIndex = 1;
		} else if (uhCaptureIndex == 1) {
			/* Get the 2nd Input Capture value */
			uwIC2Value2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);

			/* Capture computation */
			if (uwIC2Value2 > uwIC2Value1) {
				uwDiffCapture = (uwIC2Value2 - uwIC2Value1);
			} else if (uwIC2Value2 < uwIC2Value1) {
				/* 0xFFFF is max TIM3_CCRx value */
				uwDiffCapture = ((0xFFFF - uwIC2Value1) + uwIC2Value2) + 1;
			} else {
				/* If capture values are equal, we have reached the limit of frequency
				 measures */
				// Error_Handler();
			}
			/* Frequency computation: for this example TIMx (TIM3) is clocked by
			 2xAPB1Clk */
			uwFrequency = 100000 / uwDiffCapture;

			uhCaptureIndex = 0;
		}
	}
}

void IC_Report_Start() {
	for (;;) {
		// debug_log("Freq: %d [%d]", uwFrequency, uwDiffCapture);
		osDelay(1000);
	}
}
