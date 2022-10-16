#include "stm32f4xx_hal.h"
#include "main.h"
void System_Clock_Config(void);

uint16_t adc_value;
ADC_HandleTypeDef adc1_Handler;

int main(void)
{
HAL_Init();
System_Clock_Config();
ADC1_Init();
HAL_ADC_Start_IT(&adc1_Handler);
while(1)
{


}

}

void ADC1_Init(void)//High Level Initialization
{
	adc1_Handler.Instance =ADC1;
	adc1_Handler.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	adc1_Handler.Init.ContinuousConvMode = ENABLE;
	adc1_Handler.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	adc1_Handler.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	adc1_Handler.Init.NbrOfConversion = 1;
	adc1_Handler.Init.Resolution = ADC_RESOLUTION_8B;
	HAL_ADC_Init(&adc1_Handler);

	ADC_ChannelConfTypeDef adc1_channel0_cfg;
	adc1_channel0_cfg.Channel = ADC_CHANNEL_0;
	adc1_channel0_cfg.Rank = 1;
	adc1_channel0_cfg.SamplingTime = ADC_SAMPLETIME_56CYCLES;
	HAL_ADC_ConfigChannel(&adc1_Handler,&adc1_channel0_cfg);

}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	adc_value = HAL_ADC_GetValue(&adc1_Handler);
	__HAL_ADC_CLEAR_FLAG(&adc1_Handler,ADC_FLAG_EOC);
}



void System_Clock_Config(void)
{




}
