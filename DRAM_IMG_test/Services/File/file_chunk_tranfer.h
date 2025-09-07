/*
 * file_chunk_tranfer.h - Modified for single file transfer
 *
 * Created on: Aug 28, 2025
 * Author: hoang
 */

#ifndef FILE_CHUNKER_FILE_CHUNK_TRANFER_H_
#define FILE_CHUNKER_FILE_CHUNK_TRANFER_H_

#include "stdint.h"


#define SDRAM_START_ADDR 			0xC0000000				// Địa chỉ và kích thước bộ đệm SDRAM
#define SIZE_FILE_MAX				8 * 1024 * 1024 - 16	// 8MB - 16 kí tự (SEND + SIZE + FINISH)

#endif /* FILE_CHUNKER_FILE_CHUNK_TRANFER_H_ */
