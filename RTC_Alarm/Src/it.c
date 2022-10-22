/*
 * it.c
 *
 *  Created on: 12 Eki 2022
 *      Author: muhammetkocak
 */
//extern xxx_HandleTypeDef xxx_Handler;


#include "main.h"

extern RTC_HandleTypeDef realTclock;




void SysTick_Handler (void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


void RTC_Alarm_IRQHandler(void)
{
	HAL_RTC_AlarmIRQHandler(&realTclock);


}







