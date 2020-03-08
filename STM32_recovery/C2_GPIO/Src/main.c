/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
typedef enum{
	P_Core = 0x7, S_Core = 0x5, Reboot = 0x1, Sleep = 0x6, Killed = 0x0
}States;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define Power 1
#define NoPower 0

#define Read(gpio, pin) HAL_GPIO_ReadPin(gpio, pin)
#define Combine(pin1, pin2, pin3) (pin1 << 2) | (pin2 << 1) | pin1
	
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
	int trigger = 0;
	int transitionComplete = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void display_LED(States *state);
States state_checker(States my_state);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
	char Msg1[100] = {0};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	States state;
	state = S_Core;
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		if(trigger == 1){
			switch(state){
				case P_Core:
					state = S_Core;
					state = state_checker(state);
					break;
				case S_Core:
					state = Reboot;
					break;
				case Reboot:
					state = Sleep;
					break;
				case Sleep:
					state = P_Core;
				  state = state_checker(state);
					break;
				case Killed:
					break;
			}
			snprintf((char *)Msg1, sizeof(Msg1), "\r\nState: %d\r\n",  state);
			HAL_UART_Transmit(&huart2, (uint8_t *) Msg1, sizeof(Msg1), 1);
			trigger = 0;
		}
		display_LED(&state);
		HAL_Delay(500);

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}


States state_checker(States my_state){
	uint8_t complete = 0;
	States curr_state;
	uint8_t C1_state = Combine(Read(GPIOA, C1_PowerIn_Pin), Read(GPIOA, C1_S1In_Pin), Read(GPIOB, C1_S2In_Pin));
	uint8_t C2_state = Combine(Read(GPIOC, C2_Power_Pin), Read(GPIOA, C2_S1_Pin), Read(GPIOA, C2_S2_Pin));

	if(C1_state == C2_state){
		snprintf((char *)Msg1, sizeof(Msg1), "\r\nBOUNCE\r\n");
	  HAL_UART_Transmit(&huart2, (uint8_t *) Msg1, sizeof(Msg1), 1);
		switch(C1_state) {
			case P_Core:
				curr_state = S_Core;
				break;
			case S_Core:
				curr_state = P_Core;
				break;
			case Reboot:
				break;
			case Sleep:
				curr_state = P_Core;
				break;
			case Killed:
				break;
			default:
				break;
		}
		return curr_state;
	} else {
		return C2_state;
	}
}



void display_LED(States *state){
		switch(*state){
			case P_Core:
				HAL_GPIO_WritePin(GPIOC, C2_Power_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, C2_S1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, C2_S2_Pin, GPIO_PIN_SET);
				break;
			case S_Core:
				HAL_GPIO_WritePin(GPIOC, C2_Power_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, C2_S1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, C2_S2_Pin, GPIO_PIN_SET);					
				break;
			case Reboot:
				HAL_GPIO_WritePin(GPIOC, C2_Power_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, C2_S1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, C2_S2_Pin, GPIO_PIN_SET);
				break;
			case Sleep:
				HAL_GPIO_WritePin(GPIOC, C2_Power_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, C2_S1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, C2_S2_Pin, GPIO_PIN_RESET);
				break;
			case Killed:
				HAL_GPIO_WritePin(GPIOC, C2_Power_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, C2_S1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, C2_S2_Pin, GPIO_PIN_RESET);
				break;
		}
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5|C2_S1_Pin|C2_S2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(C2_Power_GPIO_Port, C2_Power_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : Trigger_Pin TriggerIn_Pin */
  GPIO_InitStruct.Pin = Trigger_Pin|TriggerIn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA5 C2_S1_Pin C2_S2_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_5|C2_S1_Pin|C2_S2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : C3_s2In_Pin C3_S1In_Pin C3_PowerIn_Pin */
  GPIO_InitStruct.Pin = C3_s2In_Pin|C3_S1In_Pin|C3_PowerIn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : C1_S2In_Pin */
  GPIO_InitStruct.Pin = C1_S2In_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(C1_S2In_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : C2_Power_Pin */
  GPIO_InitStruct.Pin = C2_Power_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(C2_Power_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : C1_S1In_Pin C1_PowerIn_Pin */
  GPIO_InitStruct.Pin = C1_S1In_Pin|C1_PowerIn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
	void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
	{
		if(trigger == 0){
			if(GPIO_Pin == TriggerIn_Pin){
				//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_4);
				//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
				trigger = 1;
			}
		}
		else{
			__NOP();
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
