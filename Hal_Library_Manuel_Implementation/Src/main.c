#include "stm32f4xx_hal.h"
#include "main.h"
void System_Clock_Config(void);
void TIM4_Init(void);
TIM_HandleTypeDef tim4_set;
int main(void)
{

HAL_Init();
TIM4_Init();
HAL_TIM_Base_Start_IT(&tim4_set);
HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_14|GPIO_PIN_15);
HAL_Delay(300);
HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_14|GPIO_PIN_15);
HAL_Delay(300);
HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_14|GPIO_PIN_15);
HAL_Delay(300);
SCB->SCR |= (1<<1);

while(1)
{


}

}

void TIM4_Init()
{

	tim4_set.Instance = TIM4;
	tim4_set.Channel = TIM_CHANNEL_1;
	tim4_set.Init.AutoReloadPreload	= TIM_AUTORELOAD_PRELOAD_ENABLE;
	tim4_set.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
	tim4_set.Init.CounterMode = TIM_COUNTERMODE_UP;
	tim4_set.Init.Period = 40000;
	tim4_set.Init.Prescaler = 1000;
	HAL_TIM_Base_Init(&tim4_set);
}










