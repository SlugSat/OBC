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
#include <stdio.h>
#include "SPI_FRAM.h"
#include "DateConversion.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum{
	P_Core = 0x1, S_Core = 0x2, Reboot = 0x3, Sleep = 0x4, Killed = 0x5 
}States;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define READ 1
#define WRITE 0
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
int trigger = 0;
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
void display_LED(States *state);
void Test_FRAM(int rw);
void SLEEP(void);
void SendToComp(uint8_t input);
void setPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int shift_amt, uint8_t input);
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
char Msg1[100] = {0};
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	
	//States state = S_Core;
	
	States state = P_Core;
	
	//States state = Sleep;
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

	uint8_t rd_flag = 0;
	uint8_t wr_flag = 0;
	
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		switch(state){
			case P_Core:
				SendToComp(state);
				snprintf((char *)Msg1, sizeof(Msg1), "\r\nP_Core\r\n");
				HAL_UART_Transmit(&huart2, (uint8_t *) Msg1, sizeof(Msg1), 1);
				//====
				wr_flag = 0;
				//====
				
				if (trigger == 1) { state = S_Core; }
				
				//====
				if (rd_flag == 0) {
					//Test_FRAM(READ);
					rd_flag = 1;
				}
				//====
				
				break;
			case S_Core:
				SendToComp(state);
				snprintf((char *)Msg1, sizeof(Msg1), "\r\nS_Core\r\n");
				HAL_UART_Transmit(&huart2, (uint8_t *) Msg1, sizeof(Msg1), 1);
			  //====
				rd_flag = 0;
			  //====
			
				if (trigger == 1) { state = Reboot; }
				
				//====
				if (wr_flag == 0) {
					//Test_FRAM(WRITE);
					wr_flag = 1;
				}
				break;
			case Reboot:
				SendToComp(state);
				//FLASH LEDS for REBOOT
				snprintf((char *)Msg1, sizeof(Msg1), "\r\nReboot\r\n");
				HAL_UART_Transmit(&huart2, (uint8_t *) Msg1, sizeof(Msg1), 1);
				if (trigger == 1) { state = Sleep; }
				break;
			case Sleep:
				SendToComp(state);
				snprintf((char *)Msg1, sizeof(Msg1), "\r\nSleep soon\r\n");
				HAL_UART_Transmit(&huart2, (uint8_t *) Msg1, sizeof(Msg1), 1);
				SLEEP();
				if (trigger == 1) { state = P_Core; }
				break;
			case Killed:
				state = Killed;
				HAL_GPIO_WritePin(GPIOC, C1_Power_Pin, GPIO_PIN_RESET);
				break;
		}
		//RESET TRIGGER
		trigger = 0;	
		//display_LED(&state);
		
		
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SPI_FRAM_LOCK_Pin|C1_Power_Pin|C1_S0_Pin|C1_S1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Seventh_Pin|Sixth_Pin|Fifth_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Fourth_GPIO_Port, Fourth_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Thrid_Pin|Second_Pin|First_Pin|Zero_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI_FRAM_CS_GPIO_Port, SPI_FRAM_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 Trigger_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_13|Trigger_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI_FRAM_IN2_Pin C3_S1_IN_Pin C2_S1_IN_Pin C2_S0_IN_Pin 
                           C2_Power_IN_Pin */
  GPIO_InitStruct.Pin = SPI_FRAM_IN2_Pin|C3_S1_IN_Pin|C2_S1_IN_Pin|C2_S0_IN_Pin 
                          |C2_Power_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI_FRAM_IN1_Pin C3_S0_IN_Pin C3_Power_IN_Pin */
  GPIO_InitStruct.Pin = SPI_FRAM_IN1_Pin|C3_S0_IN_Pin|C3_Power_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI_FRAM_LOCK_Pin C1_Power_Pin C1_S0_Pin C1_S1_Pin */
  GPIO_InitStruct.Pin = SPI_FRAM_LOCK_Pin|C1_Power_Pin|C1_S0_Pin|C1_S1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Seventh_Pin Sixth_Pin Fifth_Pin */
  GPIO_InitStruct.Pin = Seventh_Pin|Sixth_Pin|Fifth_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : Fourth_Pin */
  GPIO_InitStruct.Pin = Fourth_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Fourth_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Thrid_Pin Second_Pin First_Pin SPI_FRAM_CS_Pin 
                           Zero_Pin */
  GPIO_InitStruct.Pin = Thrid_Pin|Second_Pin|First_Pin|SPI_FRAM_CS_Pin 
                          |Zero_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

void SendToComp (uint8_t input){
	int shifter = 7;
	setPin(Seventh_GPIO_Port, Seventh_Pin, shifter--, input);
	setPin(Sixth_GPIO_Port, Sixth_Pin, shifter--, input);
	setPin(Fifth_GPIO_Port, Fifth_Pin, shifter--, input);
	setPin(Fourth_GPIO_Port, Fourth_Pin, shifter--, input);
	setPin(Thrid_GPIO_Port, Thrid_Pin, shifter--, input);
	setPin(Second_GPIO_Port, Second_Pin, shifter--, input);
	setPin(First_GPIO_Port, First_Pin, shifter--, input);
	setPin(Zero_GPIO_Port, Zero_Pin, shifter, input);
	
}
	
void setPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, int shift_amt, uint8_t input){
	if(input & (1 << shift_amt)){
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
	}
	
}

void SLEEP(void){
		HAL_SuspendTick();

		HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
		
		HAL_ResumeTick();
	
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	trigger = 1;
}		

void display_LED(States *state){
		switch(*state){
			case P_Core:
				HAL_GPIO_WritePin(GPIOA, C1_Power_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, C1_S0_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, C1_S1_Pin, GPIO_PIN_SET);
				break;
			case S_Core:
				HAL_GPIO_WritePin(GPIOA, C1_Power_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, C1_S0_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, C1_S1_Pin, GPIO_PIN_RESET);					
				break;
			case Reboot:
				HAL_GPIO_WritePin(GPIOA, C1_Power_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, C1_S0_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, C1_S1_Pin, GPIO_PIN_SET);
				break;
			case Sleep:
				HAL_GPIO_WritePin(GPIOA, C1_Power_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, C1_S0_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, C1_S1_Pin, GPIO_PIN_RESET);
				break;
			case Killed:
				HAL_GPIO_WritePin(GPIOA, C1_Power_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, C1_S0_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, C1_S1_Pin, GPIO_PIN_SET);
				break;
		}
}


void Test_FRAM(int rw) {
	char msg[200] = {0};
	char msgClear[200] = {0};
	
	uint8_t battLevel, pmState, numdataPoints, solarVector, ltStatus, mechState, numUsers, powerStatus;
	double logTime, julianTime;
	float longitude, latitude, altitude;
	
	if (rw) {
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
		
		HAL_GPIO_WritePin(GPIOA, SPI_FRAM_LOCK_Pin, GPIO_PIN_SET);
	} else {
		uint8_t longU[4] = {0};
		uint8_t longD[8] = {0};
		
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
		
		HAL_GPIO_WritePin(GPIOA, SPI_FRAM_LOCK_Pin, GPIO_PIN_SET);
	}
}

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
