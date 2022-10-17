/*
 * msp.c
 *
 *  Created on: 12 Eki 2022
 *      Author: muhammetkocak
 */
#include "main.h"
extern TIM_HandleTypeDef tim4_set;
extern GPIO_InitTypeDef gpio_tim;
void HAL_MspInit(void)
{
	//1- set up the priority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	//2-enable the required system exceptions of the arm cortex mx processor
	SCB->SHCSR |= 7<<16; //usage fault, memory fault and bus fault system exception
	//3-set the priority of the exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);//Both sub and first priority is highest
	HAL_NVIC_SetPriority(BusFault_IRQn,0,0);//Both sub and first priority is highest
	HAL_NVIC_SetPriority(UsageFault_IRQn,0,0);//Both sub and first priority is highes
}













/*
void HAL_XXX_MspInit(UART_HandleTypeDef *hxxx) This definition is in the stm32f4xx_hal_xxx.c peripheral file
{
	__HAL_RCC_XXX_CLK_ENABLE();

	__HAL_RCC_GPIOx_CLK_ENABLE();
	GPIO_InitTypeDef gpio_xxx;
	gpio_xxx.Mode = ............ ;
	gpio_xxx.Pin =  ............ ;
	gpio_xxx.Pull =  ............ ;
	gpio_xxx.Speed =  ............ ;
	gpio_xxx.Alternate =  ............ ;
	HAL_GPIO_Init(GPIOx,&gpio_XXX);

	HAL_NVIC_EnableIRQ(XXX_IRQn);
	HAL_NVIC_SetPriority(XXX,15,0);
}
*/
