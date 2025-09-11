/*
 * counter_timer.c
 *
 *  Created on: Sep 11, 2025
 *      Author: hoang
 */

#include "counter_timer.h"
#include "stm32f7xx_hal.h"

volatile uint32_t start = 0, end = 0, duration = 0;

extern TIM_HandleTypeDef htim3;

//void MX_TIM3_Init(void)
//{
//    __HAL_RCC_TIM3_CLK_ENABLE();
//
//    htim3.Instance = TIM3;
//    htim3.Init.Prescaler = (SystemCoreClock / 1000000 - 1); // 1 tick = 1 µs
//    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
//    htim3.Init.Period = 0xFFFF;  // tối đa 65535 µs trước khi tràn
//    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//    HAL_TIM_Base_Init(&htim3);
//
//    HAL_TIM_Base_Start(&htim3);  // chỉ chạy timer, không enable interrupt
//}

// Lấy giá trị hiện tại của timer (0.1ms)
uint32_t Timer_Get_Counter(void)
{
    return __HAL_TIM_GET_COUNTER(&htim3);
}

uint32_t Timer_Start_Counter(void)
{
	start = Timer_Get_Counter();
	return start;
}

uint32_t Timer_End_Counter(void)
{
	end = Timer_Get_Counter();
	return end;
}


// Tính thời gian giữa 2 lần đọc đơn vị milis
uint32_t Timer_Get_Duration(void)
{
    if (end >= start)
        return duration = (end - start)/10;
    else
        return duration = ((0xFFFF - start + 1) + end)/10;  // xử lý khi timer bị tràn
}

//// Tính thời gian giữa 2 lần đọc
//uint32_t Timer_Get_Duration(uint32_t start, uint32_t end)
//{
//    if (end >= start)
//        return end - start;
//    else
//        return (0xFFFF - start + 1) + end;  // xử lý khi timer bị tràn
//}

