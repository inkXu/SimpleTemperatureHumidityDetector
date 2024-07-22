/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app.h
  * @brief   The header file for app.c file
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_H
#define __APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
	
/* Defines -------------------------------------------------------------------*/
#define LED_ON()     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET)
#define LED_OFF()    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET)
#define LED_TOGGLE() HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7)

/* Typedef -------------------------------------------------------------------*/
typedef struct {
	uint8_t key_state;
	uint8_t update;
	uint16_t sleep_state;
	uint8_t rc_msg[6];
} ST_EXEC;

/* Exported types ------------------------------------------------------------*/
extern ST_EXEC exist;

/* Prototypes ----------------------------------------------------------------*/
void UnitTest(void);

#ifdef __cplusplus
}
#endif

#endif /* __APP_H */

