/*
 * msp.c
 *
 *  Created on: 12 Eki 2022
 *      Author: muhammetkocak
 */
#include "main.h"
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

void HAL_CAN_MspInit(CAN_HandleTypeDef *hcan)
{
	__HAL_RCC_CAN1_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitTypeDef gpio_can;
	gpio_can.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	gpio_can.Mode = GPIO_MODE_AF_PP;
	gpio_can.Pull = GPIO_NOPULL;
	gpio_can.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	gpio_can.Alternate = GPIO_AF9_CAN1;
	HAL_GPIO_Init(GPIOB,&gpio_can);
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
