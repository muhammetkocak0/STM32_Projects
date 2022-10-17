/*
 * it.c
 *
 *  Created on: 12 Eki 2022
 *      Author: muhammetkocak
 */
//extern xxx_HandleTypeDef xxx_Handler;


#include "main.h"
extern TIM_HandleTypeDef tim4_set;
void TIM4_IRQHandler(void)
{

	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12|GPIO_PIN_13);
	__HAL_TIM_CLEAR_FLAG(&tim4_set,TIM_IT_UPDATE);

}


void SysTick_Handler (void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}








