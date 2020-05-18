/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#define SPI_FRAM_CLK_Pin GPIO_PIN_5
#define SPI_FRAM_CLK_GPIO_Port GPIOA
#define SPI_FRAM_MISO_Pin GPIO_PIN_6
#define SPI_FRAM_MISO_GPIO_Port GPIOA
#define SPI_FRAM_MOSI_Pin GPIO_PIN_7
#define SPI_FRAM_MOSI_GPIO_Port GPIOA
#define Trigger_Pin GPIO_PIN_4
#define Trigger_GPIO_Port GPIOC
#define Trigger_EXTI_IRQn EXTI4_IRQn
#define SPI_FRAM_IN2_Pin GPIO_PIN_10
#define SPI_FRAM_IN2_GPIO_Port GPIOB
#define C3_S1_IN_Pin GPIO_PIN_12
#define C3_S1_IN_GPIO_Port GPIOB
#define C2_S1_IN_Pin GPIO_PIN_13
#define C2_S1_IN_GPIO_Port GPIOB
#define C2_S0_IN_Pin GPIO_PIN_14
#define C2_S0_IN_GPIO_Port GPIOB
#define C2_Power_IN_Pin GPIO_PIN_15
#define C2_Power_IN_GPIO_Port GPIOB
#define SPI_FRAM_IN1_Pin GPIO_PIN_8
#define SPI_FRAM_IN1_GPIO_Port GPIOA
#define SPI_FRAM_LOCK_Pin GPIO_PIN_9
#define SPI_FRAM_LOCK_GPIO_Port GPIOA
#define C3_S0_IN_Pin GPIO_PIN_11
#define C3_S0_IN_GPIO_Port GPIOA
#define C3_Power_IN_Pin GPIO_PIN_12
#define C3_Power_IN_GPIO_Port GPIOA
#define C1_Power_Pin GPIO_PIN_13
#define C1_Power_GPIO_Port GPIOA
#define C1_S0_Pin GPIO_PIN_14
#define C1_S0_GPIO_Port GPIOA
#define C1_S1_Pin GPIO_PIN_15
#define C1_S1_GPIO_Port GPIOA
#define Seventh_Pin GPIO_PIN_10
#define Seventh_GPIO_Port GPIOC
#define Sixth_Pin GPIO_PIN_11
#define Sixth_GPIO_Port GPIOC
#define Fifth_Pin GPIO_PIN_12
#define Fifth_GPIO_Port GPIOC
#define Fourth_Pin GPIO_PIN_2
#define Fourth_GPIO_Port GPIOD
#define Thrid_Pin GPIO_PIN_3
#define Thrid_GPIO_Port GPIOB
#define Second_Pin GPIO_PIN_4
#define Second_GPIO_Port GPIOB
#define First_Pin GPIO_PIN_5
#define First_GPIO_Port GPIOB
#define SPI_FRAM_CS_Pin GPIO_PIN_6
#define SPI_FRAM_CS_GPIO_Port GPIOB
#define Zero_Pin GPIO_PIN_7
#define Zero_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
