/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
void ShowDigit(uint8_t row, uint8_t col, uint8_t value);
void SN74HC595SendData(GPIO_TypeDef *ser_port,  uint16_t ser_pin, 
								GPIO_TypeDef *sclk_port, uint16_t sclk_pin, 
								GPIO_TypeDef *rclk_port, uint16_t rclk_pin, 
								uint8_t value);

#define SetDigitNixieTube(value) SN74HC595SendData( DIG_SER_GPIO_Port, DIG_SER_Pin, \
		DIG_SCLK_GPIO_Port, DIG_SCLK_Pin, DIG_RCLK_GPIO_Port, DIG_RCLK_Pin, (value))
#define SetLED01NixieTube(value) SN74HC595SendData( LED1_SER_GPIO_Port, LED1_SER_Pin, \
		LED1_SCLK_GPIO_Port, LED1_SCLK_Pin, LED1_RCLK_GPIO_Port, LED1_RCLK_Pin, (value))
#define SetLED02NixieTube(value) SN74HC595SendData( LED2_SER_GPIO_Port, LED2_SER_Pin, \
		LED2_SCLK_GPIO_Port, LED2_SCLK_Pin, LED2_RCLK_GPIO_Port, LED2_RCLK_Pin, (value))
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

