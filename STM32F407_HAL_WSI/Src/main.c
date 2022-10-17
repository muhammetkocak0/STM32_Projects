#include "stm32f4xx_hal.h"
#include "main.h"
void System_Clock_Config(void);
void GPIO_Init(void);
GPIO_InitTypeDef gpio_tim;
int main(void)
{

HAL_Init();
GPIO_Init();

// Dont forget to suspendtick because WFI works depends on Interrupt and HAL generates tick interrupt thus WFI doesnt work. 
HAL_SuspendTick();
while(1)
{
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON,PWR_SLEEPENTRY_WFI);
	HAL_Delay(500);

	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |GPIO_PIN_15);
}

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0))
	{
		HAL_ResumeTick();//When it is in interrupt we must activate 
		while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0));
		HAL_Delay(50);

		HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |GPIO_PIN_15);

	}

}

void GPIO_Init()
{

	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	gpio_tim.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |GPIO_PIN_15;
	gpio_tim.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_tim.Pull = GPIO_PULLDOWN;
	gpio_tim.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOD,&gpio_tim);
	gpio_tim.Pin = GPIO_PIN_0;
	gpio_tim.Mode = GPIO_MODE_IT_RISING;
	gpio_tim.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOA,&gpio_tim);
	HAL_NVIC_SetPriority(EXTI0_IRQn,15,0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}




