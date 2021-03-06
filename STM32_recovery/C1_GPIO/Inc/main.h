/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GreenLED_Pin GPIO_PIN_5
#define GreenLED_GPIO_Port GPIOA
#define C1_S1_Pin GPIO_PIN_6
#define C1_S1_GPIO_Port GPIOA
#define C1_S2_Pin GPIO_PIN_7
#define C1_S2_GPIO_Port GPIOA
#define TriggerIn_Pin GPIO_PIN_4
#define TriggerIn_GPIO_Port GPIOC
#define TriggerIn_EXTI_IRQn EXTI4_IRQn
#define C3_S2In_Pin GPIO_PIN_5
#define C3_S2In_GPIO_Port GPIOC
#define C2_S2In_Pin GPIO_PIN_12
#define C2_S2In_GPIO_Port GPIOB
#define C3_S1In_Pin GPIO_PIN_6
#define C3_S1In_GPIO_Port GPIOC
#define C1_Power_Pin GPIO_PIN_7
#define C1_Power_GPIO_Port GPIOC
#define C3_PowerIn_Pin GPIO_PIN_8
#define C3_PowerIn_GPIO_Port GPIOC
#define C2_S1In_Pin GPIO_PIN_11
#define C2_S1In_GPIO_Port GPIOA
#define C2_PowerIn_Pin GPIO_PIN_12
#define C2_PowerIn_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
