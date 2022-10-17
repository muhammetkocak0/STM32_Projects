/*
 * it.c
 *
 *  Created on: 12 Eki 2022
 *      Author: muhammetkocak
 */
//extern xxx_HandleTypeDef xxx_Handler;


#include "main.h"
extern TIM_HandleTypeDef tim4_set;
extern GPIO_InitTypeDef gpio_tim;
int i = 4;



void SysTick_Handler (void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void EXTI0_IRQHandler(void)
{

	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);

}







