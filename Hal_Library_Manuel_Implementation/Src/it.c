/*
 * it.c
 *
 *  Created on: 12 Eki 2022
 *      Author: muhammetkocak
 */
//extern xxx_HandleTypeDef xxx_Handler;
#include "main.h"

extern ADC_HandleTypeDef adc1_Handler;

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
void ADC_IRQHandler(void)
{
	HAL_ADC_IRQHandler(&adc1_Handler);




}
