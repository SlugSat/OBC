#include "SPI_FRAM.h"
<<<<<<< HEAD

/**
  * @brief  Read from the FRAM
=======
//to read 

/**
>>>>>>> a58ad3d98ba432c8b55e2fb849f72bc8b7c865e4
  * @param  address: 16 bit address
  * @param  pRxData: pointer to reception data buffer to be
  * @param  size: size of the data you are expecting (# of bytes)
  */
void SPI_FRAM_Read( SPI_HandleTypeDef *hspi,uint16_t address, uint8_t *pRxData, uint8_t size, UART_HandleTypeDef *huart)
{
	// Acquire the SPI FRAM lock
	Get_Lock(hspi, huart);
	
	// Chip select low
	HAL_GPIO_WritePin(GPIOB, SPI_FRAM_CS_Pin, GPIO_PIN_RESET);

	// initialize read command
	uint8_t read_command[READ_CMD_LEN] = {READ_OP, 			// read operation code
<<<<<<< HEAD
										address>>8,			// MSB of address
										(uint8_t)address}; 	// LSB of address
=======
																				address>>8,			// MSB of address
																				(uint8_t)address}; 	// LSB of address
>>>>>>> a58ad3d98ba432c8b55e2fb849f72bc8b7c865e4

	// initiate read operation
	HAL_SPI_Transmit(hspi, read_command, READ_CMD_LEN, 10);	

	// recieve data from appropriate register
	for(int i = size - 1; i >= 0; i--)
	{
		HAL_SPI_Receive(hspi, &pRxData[i], 1, 10);
	}

	// Chip select high
	HAL_GPIO_WritePin(GPIOB, SPI_FRAM_CS_Pin, GPIO_PIN_SET);

	// Free the lock
	Free_Lock(hspi, huart);
}
<<<<<<< HEAD
/**
  * @brief  Write to the FRAM
=======
//to write
/**
>>>>>>> a58ad3d98ba432c8b55e2fb849f72bc8b7c865e4
  * @param  address: 16 bit address
  * @param  pTxData: pointer to reception data buffer to be
  * @param  size: size of the data you are Transmiting (# of bytes)
  */
void SPI_FRAM_Write(SPI_HandleTypeDef *hspi, uint16_t address, uint8_t *pTxData, uint8_t size, UART_HandleTypeDef *huart)
{
	// Acquire the SPI FRAM lock
	Get_Lock(hspi, huart);
	
	// Chip select low
	HAL_GPIO_WritePin(GPIOB, SPI_FRAM_CS_Pin, GPIO_PIN_RESET);
	
	// initialize write command bytes
	uint8_t write_command[WRITE_CMD_LEN] = {WREN_OP, 			// enable write operation
<<<<<<< HEAD
											WRITE_OP,			// write operation code
											address>>8,			// MSB of address
											(uint8_t)address}; 	// LSB of address
=======
																					WRITE_OP,									// write operation code
																					address>>8,								// MSB of address
																					(uint8_t)address}; 				// LSB of address
>>>>>>> a58ad3d98ba432c8b55e2fb849f72bc8b7c865e4

	// initiate write operation
	HAL_SPI_Transmit(hspi, &write_command[0], 1, 10);

	// Chip select high
	HAL_GPIO_WritePin(GPIOB, SPI_FRAM_CS_Pin, GPIO_PIN_SET);
																					
	HAL_Delay(1);																				
	
	// Chip select low
	HAL_GPIO_WritePin(GPIOB, SPI_FRAM_CS_Pin, GPIO_PIN_RESET);
																					
	HAL_SPI_Transmit(hspi, &write_command[1], 3, 10);																					
																					
	for(int i = size - 1; i >= 0; i--)
	{
		HAL_SPI_Transmit(hspi, &pTxData[i], 1, 10);
	}

	// Chip select high
	HAL_GPIO_WritePin(GPIOB, SPI_FRAM_CS_Pin, GPIO_PIN_SET);																			
	HAL_Delay(1);																				
	// Chip select low
	HAL_GPIO_WritePin(GPIOB, SPI_FRAM_CS_Pin, GPIO_PIN_RESET);
	
	// terminate write operation
	uint8_t wrdi = WRDI_OP; 
	HAL_SPI_Transmit(hspi, &wrdi, 1, 10);

	// Chip select high
	HAL_GPIO_WritePin(GPIOB, SPI_FRAM_CS_Pin, GPIO_PIN_SET);
	
	// Free the lock
	Free_Lock(hspi, huart);
}

<<<<<<< HEAD
/**
  * @brief  Get the lock to reserve access to the FRAM, like mutex_lock
  * @param  The SPI connection to the FRAM
  * @param  The UART used for debugging, set the DEBUG macro in the SPI_FRAM.h file to 1
  */
void Get_Lock(SPI_HandleTypeDef *hspi, UART_HandleTypeDef *huart)
{
	#if (DEBUG) 
		char *msg1 = "\nWAITING FOR LOCK.....\n"; 
	#endif
	
	do
	{
		#if (DEBUG) 
			HAL_UART_Transmit(huart, (uint8_t *)msg1, strlen(msg1), 1); 
		#endif
		HAL_Delay(600);
	} while (HAL_GPIO_ReadPin(GPIOA, SPI_FRAM_IN1_Pin) == GPIO_PIN_RESET || 
				HAL_GPIO_ReadPin(GPIOB, SPI_FRAM_IN2_Pin) == GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(GPIOA, SPI_FRAM_LOCK_Pin, GPIO_PIN_RESET);
	while(HAL_GPIO_ReadPin(GPIOA, SPI_FRAM_IN1_Pin) == GPIO_PIN_RESET || 
					HAL_GPIO_ReadPin(GPIOB, SPI_FRAM_IN2_Pin) == GPIO_PIN_RESET)
	{
		# if (DEBUG) 
			HAL_UART_Transmit(huart, (uint8_t *)msg1, strlen(msg1), 1); 
		#endif
=======

void Get_Lock(SPI_HandleTypeDef *hspi, UART_HandleTypeDef *huart)
{
	char *msg1 = "\nWAITING FOR LOCK.....\n";
	
	do
	{
		HAL_UART_Transmit(huart, (uint8_t *)msg1, strlen(msg1), 1);
		HAL_Delay(500);
	} while (HAL_GPIO_ReadPin(GPIOA, SPI_FRAM_IN1_Pin) == GPIO_PIN_RESET || 
														HAL_GPIO_ReadPin(GPIOB, SPI_FRAM_IN2_Pin) == GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(GPIOA, SPI_FRAM_LOCK_Pin, GPIO_PIN_RESET);
	while(HAL_GPIO_ReadPin(GPIOA, SPI_FRAM_IN1_Pin) == GPIO_PIN_RESET || 
														HAL_GPIO_ReadPin(GPIOB, SPI_FRAM_IN2_Pin) == GPIO_PIN_RESET)
	{
		HAL_UART_Transmit(huart, (uint8_t *)msg1, strlen(msg1), 1);
>>>>>>> a58ad3d98ba432c8b55e2fb849f72bc8b7c865e4
		HAL_GPIO_WritePin(GPIOA, SPI_FRAM_LOCK_Pin, GPIO_PIN_SET);
		for(int i = 0; i < 1000; i++);
		HAL_GPIO_WritePin(GPIOA, SPI_FRAM_LOCK_Pin, GPIO_PIN_RESET);
	}
}

<<<<<<< HEAD
/**
  * @brief  Free the lock that is being held to read or write, like mutex_unlock
  * @param  The SPI connection to the FRAM
  * @param  The UART used for debugging, set the DEBUG macro in the SPI_FRAM.h file to 1
  */
void Free_Lock(SPI_HandleTypeDef *hspi, UART_HandleTypeDef *huart)
{
	#if (DEBUG) 
		char *msg1 = "\nFreeing lock.....\n";
		HAL_UART_Transmit(huart, (uint8_t *)msg1, strlen(msg1), 1);
	#endif
=======
void Free_Lock(SPI_HandleTypeDef *hspi, UART_HandleTypeDef *huart)
{
	char *msg1 = "\nFreeing lock.....\n";

	HAL_UART_Transmit(huart, (uint8_t *)msg1, strlen(msg1), 1);
>>>>>>> a58ad3d98ba432c8b55e2fb849f72bc8b7c865e4
	
	HAL_GPIO_WritePin(GPIOA, SPI_FRAM_LOCK_Pin, GPIO_PIN_SET);	
}
