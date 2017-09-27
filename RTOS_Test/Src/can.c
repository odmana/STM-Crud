#include "can.h"

extern CAN_HandleTypeDef hcan1;

osSemaphoreId osSemaphore;
osMessageQId osQueue;
// CanRxMsgTypeDef CanRxMessage;
CanQueue canQueue;


void Can_Send_Start() {
	CanTxMsgTypeDef TxMsg;
	HAL_StatusTypeDef status;

	for (;;) {
		/*##-3- Start the Transmission process #####################################*/
		hcan1.pTxMsg = &TxMsg;
		hcan1.pTxMsg->StdId = 0x500;
		hcan1.pTxMsg->RTR = CAN_RTR_DATA;
		hcan1.pTxMsg->IDE = CAN_ID_STD;
		hcan1.pTxMsg->DLC = 2;
		hcan1.pTxMsg->Data[0] = 0xCA;
		hcan1.pTxMsg->Data[1] = 0xFE;

		status = HAL_CAN_Transmit(&hcan1, 100);
		if (status != HAL_OK) {
			/* Transmition Error */
			// Error_Handler();
			debug_log("CAN transmit error");
		} else if (HAL_CAN_GetState(&hcan1) != HAL_CAN_STATE_READY) {
			// Error_Handler();
			debug_log("CAN ready error");
		} else {
			debug_log("CAN packet sent");
		}

		osDelay(1000);
	}

}

void Can_Recieve_Start() {
	osStatus status;
	osEvent event;
	CanRxMsgTypeDef *CanRxMessage;


//	/* Define used semaphore */
//	osSemaphoreDef(SEM);
//	/* Create the semaphore used by the two threads */
//	osSemaphore = osSemaphoreCreate(osSemaphore(SEM), 1);

	/* Create the queue used by the two tasks to pass the incrementing number.
	 Pass a pointer to the queue in the parameter structure */
	osMessageQDef(osqueue, CAN_QUEUE_SIZE, uint32_t);
	osQueue = osMessageCreate(osMessageQ(osqueue), NULL);

	Can_Recieve_Init();

	for (;;) {
		/* Get the message from the queue */
		event = osMessageGet(osQueue, 100);

	    if (event.status == osEventMessage)
	    {
	    	CanRxMessage = (CanRxMsgTypeDef*) event.value.v;
			debug_log("CAN packet received from %X. Data %X%X", CanRxMessage->StdId, CanRxMessage->Data[0], CanRxMessage->Data[1]);
	    }
	}

}

/**
 * @brief  Transmission complete callback in non blocking mode
 * @param  CanHandle: pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* CanHandle) {
//	debug_log("CAN packet received from %X. Data %X%X", CanHandle->pRxMsg->StdId, CanHandle->pRxMsg->Data[0], CanHandle->pRxMsg->Data[1]);

	canQueue.queue[canQueue.queuePosition] = *CanHandle->pRxMsg;
	uint32_t pointer = &canQueue.queue[canQueue.queuePosition];
    if (osMessagePut(osQueue, pointer, 0) != osOK)
    {
    	Error_Handler();
    }
    canQueue.queuePosition = (canQueue.queuePosition + 1) % CAN_QUEUE_SIZE;

	// osSemaphoreRelease(osSemaphore);

	/* Receive */
	if (HAL_CAN_Receive_IT(CanHandle, CAN_FIFO0) != HAL_OK) {
		/* Reception Error */
		Error_Handler();
	}
}

void Can_Recieve_Init() {
	CAN_FilterConfTypeDef sFilterConfig;
	static CanRxMsgTypeDef RxMessage;

	hcan1.pRxMsg = &RxMessage;

	/*##-2- Configure the CAN Filter ###########################################*/
	sFilterConfig.FilterNumber = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x500 << 5;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0xFFF << 5;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.BankNumber = 14;

	if(HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
	{
		/* Filter configuration Error */
		Error_Handler();
	}

	/*##-2- Configure the CAN Filter ###########################################*/
	sFilterConfig.FilterNumber = 1;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x501 << 5;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0xFFF << 5;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.BankNumber = 14;

	if(HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
	{
		/* Filter configuration Error */
		Error_Handler();
	}

	if (HAL_CAN_Receive_IT(&hcan1, CAN_FIFO0) != HAL_OK) {
		/* Reception Error */
		Error_Handler();
	}
}
