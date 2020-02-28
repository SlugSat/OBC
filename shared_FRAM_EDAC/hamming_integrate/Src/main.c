/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SPI_FRAM.h"
#include "DateConversion.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	SPI_FRAM_Init(&hspi1);
	char msg[200] = {0};
	char msgClear[200] = {0};
	
	
	uint8_t battLevel, pmState, numdataPoints, solarVector, ltStatus, mechState, numUsers, powerStatus;
	double logTime, julianTime;
	float longitude, latitude, altitude;
	uint8_t longU[4] = {0};
	uint8_t longD[8] = {0};
	
//	longitude = 234.54;
//	float_to_bytes(longitude, longU);
//	SPI_FRAM_Write(&hspi1, SPI_FRAM_LONGITUDE_ADDR, longU, 4);
//	HAL_Delay(1);
//	
//	memcpy(msg, msgClear, 200);
//	snprintf(msg, 200, "\nLongitude: %f\n", longitude); 
//	HAL_UART_Transmit(&huart2, (uint8_t *) msg, 200*sizeof(uint8_t), 5);
	
	#if 1// Write to FRAM Test
	//uint8_t longU[4] = {0};
	//uint8_t longD[8] = {0};
	
	longitude = 555.5;//234.3;
	float_to_bytes(longitude, longU);
	SPI_FRAM_Write(&hspi1, SPI_FRAM_LONGITUDE_ADDR, longU, 4, &huart2, 5);
	HAL_Delay(1);
	
	latitude = 444.4;//123.45;	
	float_to_bytes(latitude, longU);
	SPI_FRAM_Write(&hspi1, SPI_FRAM_LATITUDE_ADDR, longU, 4, &huart2, 5);
	HAL_Delay(1);
	
	altitude = 333.3;//432.1;	
	float_to_bytes(altitude, longU);
	SPI_FRAM_Write(&hspi1, SPI_FRAM_ALTITUDE_ADDR, longU, 4, &huart2, 5);
	HAL_Delay(1);
	
	julianTime = 2458616.719144;
	double_to_bytes(julianTime, longD);
	SPI_FRAM_Write(&hspi1, SPI_FRAM_TIME_ADDR, longD, 8, &huart2, 5);
	HAL_Delay(1);
	
	battLevel = 0x33;
	SPI_FRAM_Write(&hspi1, SPI_FRAM_BATT_LEVEL_ADDR, &battLevel, 1, &huart2, 5);
	HAL_Delay(1);
	
	pmState = 0x02;
	SPI_FRAM_Write(&hspi1, SPI_FRAM_PM_STATE_ADDR, &pmState, 1, &huart2, 5);
	HAL_Delay(1);
	
	logTime = 2458616.760810;
	double_to_bytes(logTime, longD);
	SPI_FRAM_Write(&hspi1, SPI_FRAM_LOG_DATA_TIME_ADDR, longD, 8, &huart2, 5);
	HAL_Delay(1);
	
	numdataPoints = 0xD3;
	SPI_FRAM_Write(&hspi1, SPI_FRAM_NUM_DATA_ADDR, &numdataPoints, 1, &huart2, 5);
	HAL_Delay(1);
	
	solarVector = 0xD3;
	SPI_FRAM_Write(&hspi1, SPI_FRAM_SOLAR_VECTOR_ADDR, &solarVector, 1, &huart2, 5);
	HAL_Delay(1);
	
	ltStatus = 0x01;
	SPI_FRAM_Write(&hspi1, SPI_FRAM_LT_STAT_ADDR, &ltStatus, 1, &huart2, 5);
	HAL_Delay(1);
	
	numUsers = 0xA9;
	SPI_FRAM_Write(&hspi1, SPI_FRAM_LT_DAILY_USERS_ADDR, &numUsers, 1, &huart2, 5);
	HAL_Delay(1);
	
	powerStatus = 0x01;
	SPI_FRAM_Write(&hspi1, SPI_FRAM_POWER_STAT_ADDR, &powerStatus, 1, &huart2, 5);
	HAL_Delay(1);
	
	mechState = 0x03;
	SPI_FRAM_Write(&hspi1, SPI_FRAM_MECH_STATE_ADDR, &mechState, 1, &huart2, 5);
	#endif
	
	#if 0
	HAL_Delay(10);
	uint8_t readVal[4] = {1, 2, 3, 4};
	uint8_t readDouble[8] = {0};
	
	// Latitude
	SPI_FRAM_Read(&hspi1, SPI_FRAM_LATITUDE_ADDR, readVal, 4, &huart2, 5);
	latitude = bytes_to_float(readVal);
	memcpy(msg, msgClear, 200);
	snprintf(msg, 200, "\nLatitude: %f\n", latitude); 
	HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), 5);
	
	// Longitude
	SPI_FRAM_Read(&hspi1, SPI_FRAM_LONGITUDE_ADDR, readVal, 4, &huart2, 5);
	longitude = bytes_to_float(readVal);
	memcpy(msg, msgClear, 200);
	snprintf(msg, 200, "\nLongitude: %f\n", longitude); 
	HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), 5);
	
	// Altitude
	SPI_FRAM_Read(&hspi1, SPI_FRAM_ALTITUDE_ADDR, readVal, 4, &huart2, 5);
	altitude = bytes_to_float(readVal);
	memcpy(msg, msgClear, 200);
	snprintf(msg, 200, "\nAltitude: %f\n", altitude); 
	HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), 5);
	
	// Time
	SPI_FRAM_Read(&hspi1, SPI_FRAM_TIME_ADDR, readDouble, 8, &huart2, 5);
	julianTime = bytes_to_double(readDouble);
	memcpy(msg, msgClear, 200);
	snprintf(msg, 200, "\nTime: %lf\n", julianTime); 
	HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), 5);
	
	// Battery
	SPI_FRAM_Read(&hspi1, SPI_FRAM_BATT_LEVEL_ADDR, &battLevel, 1, &huart2, 5);
	memcpy(msg, msgClear, 200);
	snprintf(msg, 200, "\nBattery Level: 0x%02x\n", battLevel); 
	HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), 5);
	
	// Power modes state
	SPI_FRAM_Read(&hspi1, SPI_FRAM_PM_STATE_ADDR, &pmState, 1, &huart2, 5);
	memcpy(msg, msgClear, 200);
	snprintf(msg, 200, "\nPModes State: 0x%02X\n", pmState); 
	HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), 5);
	
	// Log data at a certain time
	SPI_FRAM_Read(&hspi1, SPI_FRAM_LOG_DATA_TIME_ADDR, readDouble, 8, &huart2, 5);
	logTime = bytes_to_double(readDouble);
	memcpy(msg, msgClear, 200);
	snprintf(msg, 200, "\nLog data time: %lf\n", logTime); 
	HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), 5);
	
	// num data points logged
	SPI_FRAM_Read(&hspi1, SPI_FRAM_NUM_DATA_ADDR, &numdataPoints, 1, &huart2, 5);
	memcpy(msg, msgClear, 200);
	snprintf(msg, 200, "\nNum data points: 0x%02X\n", numdataPoints); 
	HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), 5);
	
	// solar vector
	SPI_FRAM_Read(&hspi1, SPI_FRAM_SOLAR_VECTOR_ADDR, &solarVector, 1, &huart2, 5);
	memcpy(msg, msgClear, 200);
	snprintf(msg, 200, "\nSolar Vector: 0x%02X\n", solarVector); 
	HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), 5);
	
	// LT status
	SPI_FRAM_Read(&hspi1, SPI_FRAM_LT_STAT_ADDR, &ltStatus, 1, &huart2, 5);
	memcpy(msg, msgClear, 200);
	snprintf(msg, 200, "\nLT Status: 0x%02X\n", ltStatus); 
	HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), 5);
	
	// Daily users
	SPI_FRAM_Read(&hspi1, SPI_FRAM_LT_DAILY_USERS_ADDR, &numUsers, 1, &huart2, 5);
	memcpy(msg, msgClear, 200);
	snprintf(msg, 200, "\nDaily Users: 0x%02X\n", numUsers); 
	HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), 5);
	
	// Power status
	SPI_FRAM_Read(&hspi1, SPI_FRAM_POWER_STAT_ADDR, &powerStatus, 1, &huart2, 5);
	memcpy(msg, msgClear, 200);
	snprintf(msg, 200, "\nPower status: 0x%02X\n", powerStatus); 
	HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), 5);
	
	// Mech state
	SPI_FRAM_Read(&hspi1, SPI_FRAM_MECH_STATE_ADDR, &mechState, 1, &huart2, 5);
	memcpy(msg, msgClear, 200);
	snprintf(msg, 200, "\nMech state: 0x%02X\n", mechState); 
	HAL_UART_Transmit(&huart2, (uint8_t *) msg, strlen(msg), 5);
	
	HAL_GPIO_WritePin(GPIOA, SPI_FRAM_LOCK_Pin, GPIO_PIN_SET);
	#endif
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI_FRAM_LOCK_GPIO_Port, SPI_FRAM_LOCK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI_FRAM_CS_GPIO_Port, SPI_FRAM_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : SPI_FRAM_IN2_Pin */
  GPIO_InitStruct.Pin = SPI_FRAM_IN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SPI_FRAM_IN2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI_FRAM_IN1_Pin */
  GPIO_InitStruct.Pin = SPI_FRAM_IN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SPI_FRAM_IN1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI_FRAM_LOCK_Pin */
  GPIO_InitStruct.Pin = SPI_FRAM_LOCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPI_FRAM_LOCK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI_FRAM_CS_Pin */
  GPIO_InitStruct.Pin = SPI_FRAM_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPI_FRAM_CS_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
