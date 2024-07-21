/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app.c
  * @brief   Application code
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app.h"
#include "i2c.h"
#include "adc.h"
#include "gpio.h"
#include "tim.h"

ST_EXEC exist;

/**
  * @brief  Light LED
  * @retval None
  */
void UserDemo01(void)
{
	HAL_Delay(1000);
	LED_OFF();
	HAL_Delay(1000);
	LED_ON();
}

/**
  * @brief  Light LED by switch
  * @retval None
  */
void UserDemo02(void)
{
//	static uint8_t state;
//	
//	switch(state) {
//		case 0:
//			if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET)
//				state = 1;
//			break;
//		case 1:
//			HAL_Delay(20);
//			if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET)
//				state ++;
//			else
//				state = 0;
//			break;
//		case 2:
//			LED_TOGGLE();
//			state = 0;
//			break;
//		default:
//			state = 0;
//			break;
//	}
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET) {
		HAL_Delay(20);
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET)
			while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET);
			LED_TOGGLE();
	}
}

/**
  * @brief  Light nixie tube
  * @retval None
  */
void UserDemo03(void)
{
	ShowDigit(0, 0, 1);
	ShowDigit(0, 1, 2);
	ShowDigit(0, 2, 3);
	ShowDigit(1, 0, 5);
	ShowDigit(1, 1, 6);
	ShowDigit(1, 2, 7);
		//ShowDigit(0, 1, 2);
}

/**
  * @brief  Obtain and display the temperature and humidity
  * @retval None
  */
void UserDemo04(void)
{
	uint16_t temper = 0, humid = 0;
	float temperature, humidity;
	
	SHT40SendRecvData(&temperature, &humidity);
	temper = (uint16_t)(temperature * 10);
	humid = (uint16_t)(humidity * 10);
	
	ShowDigit(0, 0, (uint8_t)(temper / 100));
	ShowDigit(0, 1, (uint8_t)(temper / 10 % 10));
	ShowDigit(0, 2, (uint8_t)(temper % 10));
	ShowDigit(1, 0, (uint8_t)(humid / 100));
	ShowDigit(1, 1, (uint8_t)(humid / 10 % 10));
	ShowDigit(1, 2, (uint8_t)(humid % 10));
}

/**
  * @brief  Display current battery level
  * @retval None
  */
void UserDemo05(void)
{
	uint16_t temp;
	temp = (uint16_t)(GetBatteryLevel() * 10);
	
	ShowDigit(1, 0, (uint8_t)(temp / 100));
	ShowDigit(1, 1, (uint8_t)(temp / 10 % 10));
	ShowDigit(1, 2, (uint8_t)(temp % 10));
}

/** 
  * @brief  Unit test for function UserDemoxx
  * @retval None
  */
void UserDemo(void)
{
	ShowDigit(0, 0, (uint8_t)(exist.rc_msg[0] / 100));
	ShowDigit(0, 1, (uint8_t)(exist.rc_msg[1] / 10 % 10));
	ShowDigit(0, 2, (uint8_t)(exist.rc_msg[2] % 10));
	ShowDigit(1, 0, (uint8_t)(exist.rc_msg[3] / 100));
	ShowDigit(1, 1, (uint8_t)(exist.rc_msg[4] / 10 % 10));
	ShowDigit(1, 2, (uint8_t)(exist.rc_msg[5] % 10));
}

/** 
  * @brief  Unit test for function UserDemoxx
  * @retval None
  */
void UnitTest(void)
{
	UserDemo05();
}

