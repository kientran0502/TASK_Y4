/*
 * test_usb_transfer_file.h
 *
 *  Created on: Aug 14, 2025
 *      Author: hoang
 */

#ifndef TEST_USB_TRANSFER_FILE_H_
#define TEST_USB_TRANSFER_FILE_H_

#include "FreeRTOS.h"
#include "task.h"
#include "queuex.h"

#define MAX_COMMAND_SIZE 32
#define FINISH_PATTERN "DONE"

typedef enum {
    STATE_WAIT_COMMAND,
    STATE_RECEIVE_IMAGE,
	STATE_SEND_IMAGE
} State_t;

extern TaskHandle_t hTaskCommand;
extern TaskHandle_t hTaskReceive;
extern TaskHandle_t hTaskSend;

void Task_Command(void *pvParameters);
void Task_Receive(void *pvParameters);
void TaskSendImage(void *pvParameters);


#endif /* TEST_USB_TRANSFER_FILE_H_ */
