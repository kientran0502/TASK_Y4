/*
 * crc.c
 *
 *  Created on: Aug 28, 2025
 *      Author: hoang
 */

#include "crc.h"
#include "stm32f7xx_hal.h"

extern CRC_HandleTypeDef hcrc;

void CRC_HW_Reset(void)
{
	CRC->CR = CRC_CR_RESET;
}


uint32_t CRC_HW_Calculate_Byte(uint8_t data)
{
	CRC->CR = data;
	return CRC->CR;
}


uint32_t CRC_HW_Calculation(uint8_t *data_buffer, uint32_t length)
{
    if (length == 0) return 0;
    uint8_t* p_data = data_buffer;

    CRC->CR = CRC_CR_RESET;

    for (uint32_t i = 0; i < length; i ++)
    {
    	CRC->DR = *p_data;
    	p_data ++ ;
    }
    return CRC->DR;
}
