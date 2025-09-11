/*
 * test_usb_transfer_file.c - Fixed Version
 *
 *  Created on: Aug 14, 2025
 *      Author: hoang
 */

#include "test_usb_transfer_file.h"
#include <stdint.h>
#include <string.h>
#include "usbd_cdc_if.h"
#include "queuex.h"
#include "usb_receive.h"
#include "crc.h"

// Global state variables
extern Queuex_t usb_rx_cmd_queue;
extern Queuex_t usb_rx_file_queue;

extern uint8_t command_buffer[64];

TaskHandle_t hTaskCommand;
TaskHandle_t hTaskReceive;
TaskHandle_t hTaskSend;

volatile State_t current_device_state = STATE_WAIT_COMMAND;
FileState_t current_file_state = FILE_STATE_GET_SIZE;
volatile FileInfoStruct_t current_file;


void File_Init(void)
{
	current_file.size = 0;
	current_file.received_crc = 0;
	current_file.calculated_crc = 0;
	current_file.size_received = 0;
	current_file.start_file_index = 0;
	current_file.end_file_index = 0;
	current_file.is_valid = 0;
	current_file.data = NULL;
	current_file_state = FILE_STATE_GET_SIZE;
}




//// Utility function to send response safely
static void Send_Response(const char* response) {
   CDC_Transmit_HS((uint8_t*)response, strlen(response));
}



/**
 * @brief Main USB data processing task - ONLY this task processes USB queue
 * This task has exclusive access to USB_Queue_Pop to prevent race conditions
 */
void Task_Command(void *pvParameters)
{
    uint8_t byte;
    static uint8_t cmd_buf[32];
    static uint8_t cmd_index = 0;

    for (;;)
    {
    	if(uxTaskPriorityGet(hTaskCommand) == 2)
    	{
    		vTaskPrioritySet(hTaskCommand, 4);
    	}

		if (current_device_state == STATE_WAIT_COMMAND)
		{
			if (Queue_Pop(&usb_rx_cmd_queue, &byte))
			{
				if (byte == '\n')
				{
					cmd_buf[cmd_index] = '\0';
					cmd_index = 0;

					if (strcmp((char*)cmd_buf, "SEND") == 0)
					{
						current_device_state = STATE_RECEIVE_IMAGE;
						Send_Response("READY\n");
						vTaskPrioritySet(hTaskReceive, 5);
					}
					else if (strcmp((char*)cmd_buf, "GET") == 0)   // Xử lý gửi file ở đây
					{
						current_device_state = STATE_SEND_IMAGE;
						vTaskPrioritySet(hTaskSend, 5);
					}
					else
					{
						Send_Response("ERR:UNKNOWN_CMD\n");
					}
				}
				else
				{
					if (cmd_index < sizeof(cmd_buf) - 1)
					{
						cmd_buf[cmd_index++] = byte;
					}
				}
			}
		}

		vTaskDelay(pdMS_TO_TICKS(1));
    }
}

uint8_t file_size_bytes[4] = {0};
uint8_t file_size_index = 0;
uint8_t file_crc_bytes[4] = {0};
uint8_t file_crc_index = 0;

void Task_Receive(void *pvParameters)
{
    uint8_t byte;
    for (;;)
    {
        if(current_device_state == STATE_RECEIVE_IMAGE)
        {
        	if(Queue_Pop(&usb_rx_file_queue, &byte))
        	{
        		switch(current_file_state)
        		{
        			case FILE_STATE_GET_SIZE:
        	            file_size_bytes[file_size_index++] = byte;
        	            if (file_size_index >= 4)
        	            {
        	                current_file.size = file_size_bytes[0] |
        	                                   (file_size_bytes[1] << 8) |
        	                                   (file_size_bytes[2] << 16) |
        	                                   (file_size_bytes[3] << 24);
        	                if (current_file.size > SIZE_FILE_MAX)
        	                {
        	                	current_file.size = 0;
        	                	current_device_state = STATE_WAIT_COMMAND;
			                	vTaskPrioritySet(hTaskReceive, 3);
        	                }
							else
							{
								vTaskDelay(100); // đợi nhận đủ file tồi mới tính CRC
								current_file.start_file_index = Queue_Get_Tail_Index(&usb_rx_file_queue);
								current_file.calculated_crc = CRC_HW_Calculation(Queue_Get_Tail_Address(&usb_rx_file_queue), current_file.size);
								Queue_Set_Tail_Position(&usb_rx_file_queue, current_file.start_file_index + current_file.size);   // Bỏ qua dữ liệu đã tính CRC
								current_file.end_file_index = current_file.start_file_index + current_file.size;
		        				current_file_state = FILE_STATE_GET_CRC;
							}
        	            }

        				break;

        			case FILE_STATE_GET_CRC:
			            file_crc_bytes[file_crc_index++] = byte;
			            if (file_crc_index >= 4)
			            {
			                current_file.received_crc = file_crc_bytes[0] |
			                                             (file_crc_bytes[1] << 8) |
			                                             (file_crc_bytes[2] << 16) |
			                                             (file_crc_bytes[3] << 24);
//			                current_file_state = FILE_STATE_CHECK_CRC;
							if(current_file.calculated_crc == current_file.received_crc)
							{
								current_file.is_valid = 1;
								Send_Response("OK\n");
								current_file_state = FILE_STATE_GET_SIZE;
								current_device_state = STATE_WAIT_COMMAND;
								vTaskPrioritySet(hTaskReceive, 3);
							}
							else
							{
								File_Init();
								Send_Response("ERR:CRC_MISMATCH\n");
								current_device_state = STATE_WAIT_COMMAND;
								vTaskPrioritySet(hTaskReceive, 3);
							}
						}
			            break;

        			case FILE_STATE_CHECK_CRC:
//						if(current_file.calculated_crc == current_file.received_crc)
//						{
//							current_file.is_valid = 1;
//							Send_Response("OK\n");
//							current_file_state = FILE_STATE_GET_SIZE;
//							current_device_state = STATE_WAIT_COMMAND;
//							vTaskPrioritySet(hTaskReceive, 3);
//						}
//						else
//						{
//							File_Init();
//							Send_Response("ERR:CRC_MISMATCH\n");
//							current_device_state = STATE_WAIT_COMMAND;
//							vTaskPrioritySet(hTaskReceive, 3);
//						}
        				break;
        		}
        	}
        }
    }
}


/**
 * @brief Task for handling file transmission
 * This task monitors transmission state and calls Transmit_Task
 */


void TaskSendImage(void *pvParameters)
{

	for (;;)
	{
		if(current_device_state == STATE_SEND_IMAGE)
		{
			if (current_file.size == 0 && current_file.is_valid == 0)
			{
				Send_Response("ERR:NO_FILE\n");
				current_device_state = STATE_WAIT_COMMAND;
				vTaskPrioritySet(hTaskSend, 3);
			}
			else
			{
				// Gửi kích thước file
				uint8_t size_bytes[4];
				size_bytes[0] = (current_file.size >> 0) & 0xFF;
				size_bytes[1] = (current_file.size >> 8) & 0xFF;
				size_bytes[2] = (current_file.size >> 16) & 0xFF;
				size_bytes[3] = (current_file.size >> 24) & 0xFF;
				CDC_Transmit_HS(size_bytes, 4);

				// Gửi dữ liệu file
				Queue_Set_Tail_Position(&usb_rx_file_queue, current_file.start_file_index);
				Queue_Set_Header_Position(&usb_rx_file_queue, current_file.end_file_index);
//
//				for(uint32_t bytes_left = 0; bytes_left < (current_file.size + APP_TX_DATA_SIZE); bytes_left = bytes_left + APP_TX_DATA_SIZE)
//				{
//					uint32_t send_size = ((bytes_left + APP_TX_DATA_SIZE) > current_file.size) ? (current_file.size - bytes_left) : APP_TX_DATA_SIZE;
//			        while(Check_Flag_Complete_Transmit() != 0)
//			        {
//			            // Đợi transmission trước hoàn thành
//			        }
//					CDC_Transmit_HS(Queue_Get_Tail_Address(&usb_rx_file_queue), send_size);
//					Queue_Set_Tail_Position(&usb_rx_file_queue, Queue_Get_Tail_Index(&usb_rx_file_queue) + send_size);
//				}

				uint32_t offset = 0;

				while (offset < current_file.size)
				{
				    // Tính số byte cần gửi trong lần này
				    uint32_t send_size = (current_file.size - offset > APP_TX_DATA_SIZE) ?
				                         APP_TX_DATA_SIZE :
				                         (current_file.size - offset);

				    // Đợi cho tới khi truyền xong lần trước
				    while (Check_Flag_Complete_Transmit() != 0)
				    {
				        // chờ truyền xong
				    }

				    // Lấy địa chỉ dữ liệu ở tail của queue
				    uint8_t *data_ptr = Queue_Get_Tail_Address(&usb_rx_file_queue);

				    // Truyền dữ liệu qua USB CDC
				    CDC_Transmit_HS(data_ptr, send_size);

				    // Cập nhật vị trí tail
				    Queue_Set_Tail_Position(&usb_rx_file_queue, Queue_Get_Tail_Index(&usb_rx_file_queue) + send_size);

				    // Tăng offset lên
				    offset += send_size;
				    vTaskDelay(1);
				}
				Queue_Set_Tail_Position(&usb_rx_file_queue, current_file.start_file_index);
				current_file.calculated_crc = CRC_HW_Calculation(Queue_Get_Tail_Address(&usb_rx_file_queue), current_file.size);
				// Gửi CRC
				uint8_t crc_bytes[4] = {0};
				crc_bytes[0] = (current_file.calculated_crc >> 0) & 0xFF;
				crc_bytes[1] = (current_file.calculated_crc >> 8) & 0xFF;
				crc_bytes[2] = (current_file.calculated_crc >> 16) & 0xFF;
				crc_bytes[3] = (current_file.calculated_crc >> 24) & 0xFF;
				CDC_Transmit_HS(crc_bytes, 4);

				vTaskDelay(pdMS_TO_TICKS(10));  // Đợi đảm bảo dữ liệu được gửi hết

				current_device_state = STATE_WAIT_COMMAND;
				vTaskPrioritySet(hTaskSend, 3);
			}
		}
	}
}


