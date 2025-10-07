/*
 * can_stm32.c
 *
 *  Created on: Sep 25, 2025
 *      Author: hoang
 */

//#include "can.h"
#include "stm32f4xx_hal.h"
#include "csp_error.h"
#include "debug_logger.h"

extern CAN_HandleTypeDef hcan1;

int can_init(uint32_t id, uint32_t mask, struct csp_can_config *conf)
{
    if (HAL_CAN_Start(&hcan1) != HAL_OK)
    {
        return CSP_ERR_DRIVER;
    }
    // Bật interrupt nếu muốn xử lý RX
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
    return CSP_ERR_NONE;
}


/**
 * Gửi frame CAN từ CSP ra STM32 CAN HAL
 */
int can_send(can_id_t id, uint8_t * data, uint8_t dlc)
{
    CAN_TxHeaderTypeDef txHeader;
    uint32_t txMailbox;

//    txHeader.StdId = frame->id;     // ID từ CSP
//    xHeader.ExtId = 0t;
//    txHeader.IDE   = CAN_ID_STD;    // Hoặc CAN_ID_EXT nếu dùng extended ID
//    txHeader.RTR   = CAN_RTR_DATA;
//    txHeader.DLC   = frame->dlc;
	txHeader.DLC = dlc;
	txHeader.IDE = CAN_ID_EXT;
	txHeader.RTR = CAN_RTR_DATA;
	txHeader.ExtId = id;
	txHeader.TransmitGlobalTime = DISABLE;
//
//    if (HAL_CAN_AddTxMessage(&hcan1, &txHeader,
//                             (uint8_t *)frame->data,
//                             &txMailbox) != HAL_OK) {
//        return CSP_ERR_DRIVER;
//    }

	HAL_CAN_AddTxMessage(&hcan1, &txHeader, data, &txMailbox);
//	uart_ring_buffer_put(data, dlc);

    return CSP_ERR_NONE;
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	uart_ring_buffer_put((uint8_t*)"CAN RX interrupt\n", 16);
	CAN_RxHeaderTypeDef RxHeader;
	CSP_BASE_TYPE xCspTaskWoken = pdFALSE;
	uint8_t RxData[8] = {0};
   if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK)
   {
       can_frame_t frame;
       frame.id  = (RxHeader.IDE == CAN_ID_EXT) ? RxHeader.ExtId : RxHeader.StdId;
       frame.dlc = RxHeader.DLC;
       memcpy(frame.data, RxData, frame.dlc);
	   csp_can_rx_frame(&frame, xCspTaskWoken);
//       // Ở đây bạn xử lý dữ liệu nhận được
//		csp_can_rx(&csp_if_can, RxHeader.StdId, RxData, RxHeader.DLC, &xCspTaskWoken);

       if(xCspTaskWoken) {
       		portYIELD_FROM_ISR(xCspTaskWoken);
       	}
   }
}
