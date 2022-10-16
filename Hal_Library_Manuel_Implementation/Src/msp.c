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

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
	__HAL_RCC_ADC1_CLK_ENABLE();

	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef gpio_adc;
	gpio_adc.Mode = GPIO_MODE_ANALOG;
	gpio_adc.Pin = GPIO_PIN_0;
	gpio_adc.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOA,&gpio_adc);

	HAL_NVIC_EnableIRQ(ADC_IRQn);
	HAL_NVIC_SetPriority(ADC_IRQn,15,0);
}



/*
void HAL_XXX_MspInit(UART_HandleTypeDef *hxxx)
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
