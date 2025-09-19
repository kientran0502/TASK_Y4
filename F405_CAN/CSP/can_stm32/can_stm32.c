/*
 * can_stm32.c
 *
 *  Created on: Sep 19, 2025
 *      Author: hoang
 */

#include "can_stm32.h"
#include "stm32f4xx_hal.h"
#include "csp_error.h"

extern CAN_HandleTypeDef hcan1;

int csp_can_tx_frame(void *driver_data, uint32_t id, const uint8_t *data, uint8_t dlc)
{
//	if (dlc > 8) {
//		return CSP_ERR_INVAL;
//	}

	CAN_TxHeaderTypeDef txHeader;
	txHeader.DLC = dlc;
	txHeader.IDE = CAN_ID_STD;
	txHeader.RTR = CAN_RTR_DATA;
	txHeader.StdId = 0x103;
	txHeader.TransmitGlobalTime = DISABLE;


	uint32_t canMailBox;
//	HAL_CAN_AddTxMessage((CAN_HandleTypeDef *)driver_data, &txHeader, data, &canMailBox);
	HAL_CAN_AddTxMessage(&hcan1, &txHeader, data, &canMailBox);
	uart_ring_buffer_put(data, dlc);
	return CSP_ERR_NONE;
}
