/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "app.h"
#include "tim.h"

static uint8_t DIGIT_ARR[] = {0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F};
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED2_SER_Pin|LED2_RCLK_Pin|LED2_SCLK_Pin|DIG_SER_Pin
                          |DIG_RCLK_Pin|DIG_SCLK_Pin|LED1_RCLK_Pin|LED1_SCLK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED1_SER_GPIO_Port, LED1_SER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin
                           PAPin PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = LED2_SER_Pin|LED2_RCLK_Pin|LED2_SCLK_Pin|DIG_SER_Pin
                          |DIG_RCLK_Pin|DIG_SCLK_Pin|LED1_RCLK_Pin|LED1_SCLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PB7 */
  GPIO_InitStruct.Pin = LED1_SER_Pin|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 2 */

/* 64Mhz时钟时，当ulCount为1，函数耗时3个时钟，延时=3*1/64us */
/**
  * @brief  Delay function
	* @pram   ulCount : (ulCount * 3 / 64) us
  * @retval None
  */
__asm void SysCtlDelay(unsigned long ulCount)
{
	SUBS r0,#1;
	BNE SysCtlDelay;
	BX lr;
}

/**
  * @brief  Display digit
	* @pram   row  : Line number
	*         col  : Column number
	*         value: Display digit
  * @retval None
  */
void ShowDigit(uint8_t row, uint8_t col, uint8_t value)
{
	if (row > 1 || col > 2 || value > 9)
		return ;
	
	uint8_t num, select_value = 0;
	num = DIGIT_ARR[value];
	
	switch (col) {
		case 0:
			select_value = 0xFE;
			break;
		case 1:
			select_value = 0xFD;
			num |= 0x80;           // dot
			break;
		case 2:
			select_value = 0xFB;
			break;
		default:
			break;
	}
	
	if (row == 0) {
		SetDigitNixieTube(select_value);
		SetLED01NixieTube(num);
		SysCtlDelay(3000);
		SetLED01NixieTube(0x00);                // Prevent misalignment (防止错位)
	} else if (row == 1) {
		SetDigitNixieTube(select_value << 3);
		SetLED02NixieTube(num);
		SysCtlDelay(3000);
		SetLED02NixieTube(0x00);                // The same as before
	}
}

/**
  * @brief  SN74HC595 dirver
	* @pram   ser_port  : The port used of SER signal cable
	*         ser_pin   : The pin used of SER signal cable
	*         sclk_port : The port used of SRCLK signal cable
	*         sclk_pin  : The pin used of SRCLK signal cable
	*         rclk_port : The port used of RCLK signal cable
	*         rclk_pin  : The pin used of RCLK signal cable
	*         value     : The content you want to set
  * @retval None
  */
void SN74HC595SendData(GPIO_TypeDef *ser_port,  uint16_t ser_pin, 
									GPIO_TypeDef *sclk_port, uint16_t sclk_pin, 
									GPIO_TypeDef *rclk_port, uint16_t rclk_pin, 
									uint8_t value)
{
	uint8_t i;
	for (i = 0; i < 8; i++) {
		if ((value << i) & 0x80)
			HAL_GPIO_WritePin(ser_port, ser_pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(ser_port, ser_pin, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(sclk_port, sclk_pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(sclk_port, sclk_pin, GPIO_PIN_RESET);
	}
	HAL_GPIO_WritePin(rclk_port, rclk_pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(rclk_port, rclk_pin, GPIO_PIN_RESET);
}

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_5) {
		SysCtlDelay(40000);
		if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(GPIOB , GPIO_PIN_5)) {
			//while (GPIO_PIN_RESET == HAL_GPIO_ReadPin(GPIOB , GPIO_Pin));
			exist.update = 1;
			if (exist.key_state > 1)
				exist.key_state = 0;
			else
				exist.key_state ++;
			if (exist.sleep_state == 0) {
				HAL_ResumeTick();
				__HAL_TIM_SET_COUNTER(&htim14, 0);
				HAL_TIM_Base_Start_IT(&htim14);
				exist.key_state = 0;
			}
		}
	}
}

/* USER CODE END 2 */
