/*
 * counter_timer.h
 *
 *  Created on: Sep 11, 2025
 *      Author: hoang
 */

#ifndef TIMER_COUNTER_TIMER_H_
#define TIMER_COUNTER_TIMER_H_

#include <stdint.h>

uint32_t Timer_Get_Counter(void);
uint32_t Timer_Start_Counter(void);
uint32_t Timer_End_Counter(void);
uint32_t Timer_Get_Duration(void);


#endif /* TIMER_COUNTER_TIMER_H_ */
