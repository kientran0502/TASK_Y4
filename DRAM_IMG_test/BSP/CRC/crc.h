/*
 * crc.h
 *
 *  Created on: Aug 28, 2025
 *      Author: hoang
 */

#ifndef CRC_CRC_H_
#define CRC_CRC_H_

#include "stdint.h"

uint32_t CRC_HW_Calculation(uint8_t *data_buffer, uint32_t length);

#endif /* CRC_CRC_H_ */
