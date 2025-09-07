/*
 * usb_receive.h - Modified for single file transfer
 *
 * Created on: Aug 5, 2025
 * Author: hoang
 */

#ifndef INC_USB_RECEIVE_H_
#define INC_USB_RECEIVE_H_

#include "file_chunk_tranfer.h"
#include "stm32f7xx_hal.h"
#include <stdint.h>
#include <string.h>


// Trạng thái nhận file - đổi tên từ chunk
typedef enum
{
    FILE_STATE_GET_SIZE,
//    FILE_STATE_GET_DATA,
    FILE_STATE_GET_CRC,
	FILE_STATE_CHECK_CRC
} FileState_t;

// Cấu trúc thông tin file - đổi tên từ chunk
typedef struct
{
    uint32_t size;
    uint32_t received_crc;
    uint32_t calculated_crc;
    uint32_t size_received;
    uint32_t start_file_index;
    uint32_t end_file_index;
    uint8_t is_valid;
    uint8_t *data;
} FileInfoStruct_t;



#endif /* INC_USB_RECEIVE_H_ */
