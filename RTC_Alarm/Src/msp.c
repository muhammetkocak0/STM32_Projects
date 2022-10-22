/*
 * msp.c
 *
 *  Created on: 12 Eki 2022
 *      Author: muhammetkocak
 */
#include "main.h"

extern RTC_HandleTypeDef realTclock;

void HAL_MspInit(void)
{
	//1- set up the priority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	//2-enable the required system exceptions of the arm cortex mx processor
	SCB->SHCSR |= 7<<16; //usage fault, memory fault and bus fault system exception
	//3-set the priority of the exceptions
	  __HAL_RCC_SYSCFG_CLK_ENABLE();
	  __HAL_RCC_PWR_CLK_ENABLE();
	HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);//Both sub and first priority is highest
	HAL_NVIC_SetPriority(BusFault_IRQn,0,0);//Both sub and first priority is highest
	HAL_NVIC_SetPriority(UsageFault_IRQn,0,0);//Both sub and first priority is highes

}

void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{
/*
	RCC_OscInitTypeDef        RCC_OscInitStruct;
		  RCC_PeriphCLKInitTypeDef RCC_RTCPeriClkInit;
		  //1. Turn on the LSE
		  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
		  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
		  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
		  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
		  {

		  }

		  //2. select LSE as RTCCLK
		  RCC_RTCPeriClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
		  RCC_RTCPeriClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
		  if( HAL_RCCEx_PeriphCLKConfig(&RCC_RTCPeriClkInit)!= HAL_OK)
		  {

		  }
*/
		  //3. Enable the RTC Clock
		  __HAL_RCC_RTC_ENABLE();

		  //4. Enable the RTC Alarm IRQ in the NVIC
		  HAL_NVIC_SetPriority(RTC_Alarm_IRQn,15,0);
		  HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
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
