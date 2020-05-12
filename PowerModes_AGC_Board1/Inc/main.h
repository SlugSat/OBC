/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
#define DAC_VGA_Pin GPIO_PIN_4
#define DAC_VGA_GPIO_Port GPIOA
#define DAC_VA_Pin GPIO_PIN_5
#define DAC_VA_GPIO_Port GPIOA
#define Scie_Rail_Pin GPIO_PIN_6
#define Scie_Rail_GPIO_Port GPIOA
#define Mech_Rail_Pin GPIO_PIN_7
#define Mech_Rail_GPIO_Port GPIOA
#define SPI_FRAM_LOCK_Pin GPIO_PIN_5
#define SPI_FRAM_LOCK_GPIO_Port GPIOC
#define SPI_FRAM_CS_Pin GPIO_PIN_1
#define SPI_FRAM_CS_GPIO_Port GPIOB
#define DIE_INT_Pin GPIO_PIN_10
#define DIE_INT_GPIO_Port GPIOB
#define DIE_INT_EXTI_IRQn EXTI15_10_IRQn
#define Memory_Rail_Pin GPIO_PIN_11
#define Memory_Rail_GPIO_Port GPIOB
#define LT_Rail_Pin GPIO_PIN_12
#define LT_Rail_GPIO_Port GPIOB
#define SPI_FRAM_CLK_Pin GPIO_PIN_13
#define SPI_FRAM_CLK_GPIO_Port GPIOB
#define SPI_FRAM_MISO_Pin GPIO_PIN_14
#define SPI_FRAM_MISO_GPIO_Port GPIOB
#define SPI_FRAM_MOSI_Pin GPIO_PIN_15
#define SPI_FRAM_MOSI_GPIO_Port GPIOB
#define SPI_FRAM_IN2_Pin GPIO_PIN_6
#define SPI_FRAM_IN2_GPIO_Port GPIOC
#define Misc_Rail_Pin GPIO_PIN_7
#define Misc_Rail_GPIO_Port GPIOC
#define SPI_FRAM_IN1_Pin GPIO_PIN_8
#define SPI_FRAM_IN1_GPIO_Port GPIOC
#define SCIENCE_EVENT_Pin GPIO_PIN_8
#define SCIENCE_EVENT_GPIO_Port GPIOA
#define Telemetry_Rail_Pin GPIO_PIN_11
#define Telemetry_Rail_GPIO_Port GPIOA
#define DEAD_Pin GPIO_PIN_12
#define DEAD_GPIO_Port GPIOA
#define FUEL_GAUGE_SCL_Pin GPIO_PIN_8
#define FUEL_GAUGE_SCL_GPIO_Port GPIOB
#define FUEL_GAUGE_SDA_Pin GPIO_PIN_9
#define FUEL_GAUGE_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
