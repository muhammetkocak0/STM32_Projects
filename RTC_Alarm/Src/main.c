#include "stm32f4xx_hal.h"
#include "main.h"
#include "string.h"
void GPIO_Init(void);
void RTC_Init(void);
void RTC_CalendarConfig(void);
void  RTC_AlarmConfig(void);
void SystemClock_Config(void);


RTC_HandleTypeDef realTclock;

uint8_t Hours, Minutes, Seconds;

int main(void)
{

	HAL_Init();
	SystemClock_Config();
	GPIO_Init();
	RTC_Init();
	RTC_CalendarConfig();
	RTC_AlarmConfig();
	HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
	RTC_TimeTypeDef RTC_Timeread = {0};
    RTC_DateTypeDef RTC_Dateread = {0};






	while(1)
	{


		HAL_Delay(1000);

		HAL_RTC_GetTime(&realTclock,&RTC_Timeread,RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&realTclock,&RTC_Dateread,RTC_FORMAT_BIN);
		Hours = RTC_Timeread.Hours;
		Minutes = RTC_Timeread.Minutes;
		Seconds = RTC_Timeread.Seconds;



	}


	return 0;
}





void GPIO_Init()
{
	GPIO_InitTypeDef gpio_for_rtc;
	__HAL_RCC_GPIOD_CLK_ENABLE();
	gpio_for_rtc.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_for_rtc.Pull = GPIO_NOPULL;
	gpio_for_rtc.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	gpio_for_rtc.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOD,&gpio_for_rtc);
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {

  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {

  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {

  }
}
void RTC_Init()
{
	realTclock.Instance = RTC;
	realTclock.Init.HourFormat = RTC_HOURFORMAT_24;
	realTclock.Init.AsynchPrediv = 0x7F;
	realTclock.Init.SynchPrediv = 0xFF;
	realTclock.Init.OutPut = RTC_OUTPUT_DISABLE;
	realTclock.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	realTclock.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	HAL_RTC_Init(&realTclock);

}



void RTC_CalendarConfig(void)
{
	RTC_TimeTypeDef rtc_time= {0};
	rtc_time.Hours = 12;
	rtc_time.Minutes = 45;
	rtc_time.Seconds = 00;
	//rtc_time.TimeFormat = RTC_HOURFORMAT12_PM;
	HAL_RTC_SetTime(&realTclock,&rtc_time,RTC_FORMAT_BIN);


	RTC_DateTypeDef rtc_date= {0};
	rtc_date.Date = 12;
	rtc_date.Month = RTC_MONTH_JUNE;
	rtc_date.Year = 18;
	rtc_date.WeekDay = RTC_WEEKDAY_TUESDAY;
	HAL_RTC_SetDate(&realTclock,&rtc_date,RTC_FORMAT_BIN);





}

void RTC_AlarmConfig()
{



	RTC_AlarmTypeDef rtc_alarm= {0};
	memset(&rtc_alarm,0,sizeof(rtc_alarm));
	HAL_RTC_DeactivateAlarm(&realTclock,RTC_ALARM_A);
	rtc_alarm.Alarm = RTC_ALARM_A;
	rtc_alarm.AlarmTime.Minutes =45;
	rtc_alarm.AlarmTime.Seconds =9;
	rtc_alarm.AlarmMask = RTC_ALARMMASK_HOURS | RTC_ALARMMASK_DATEWEEKDAY |RTC_ALARMMASK_MINUTES ;
	rtc_alarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_NONE;
	HAL_RTC_SetAlarm_IT(&realTclock,&rtc_alarm,RTC_FORMAT_BIN);
}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
}

