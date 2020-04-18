#include "SPI_FRAM.h"

#define ST_DELAY 341 // Science and telemtry board delay
#define PM_DELAY 405 // Power modes and AGC board delay
#define ME_DELAY 111 // Mechanical board delay

/**
  * @brief  Initialize reading from the FRAM
  * @param  SPI peripheral connected to the SPI FRAM
  */
void SPI_FRAM_Init(SPI_HandleTypeDef *hspi)
{
	HAL_GPIO_WritePin(SPI_FRAM_LOCK_GPIO_Port, SPI_FRAM_LOCK_Pin, GPIO_PIN_SET);	
	// Chip select high
	HAL_GPIO_WritePin(SPI_FRAM_CS_GPIO_Port, SPI_FRAM_CS_Pin, GPIO_PIN_SET);
}

/**
  * @brief  Read from the FRAM
  * @param  address: 16 bit address
  * @param  pRxData: pointer to reception data buffer to be
  * @param  size: size of the data you are expecting (# of bytes)
  */
void SPI_FRAM_Read(SPI_HandleTypeDef *hspi,uint16_t address, uint8_t *pRxData, uint8_t size, UART_HandleTypeDef *huart, uint8_t timeoutThreshold)
{
	// Acquire the SPI FRAM lock
	Get_Lock(hspi, huart, timeoutThreshold);
	
	// Chip select low
	HAL_GPIO_WritePin(SPI_FRAM_CS_GPIO_Port, SPI_FRAM_CS_Pin, GPIO_PIN_RESET);

	// initialize read command
	uint8_t read_command[READ_CMD_LEN+1] = {READ_OP, 			// read operation code
										address>>8,			// MSB of address
										(uint8_t)address,  	// LSB of address
										0}; // garbage data value
	// initiate read operation
	while(HAL_SPI_Transmit(hspi, read_command, READ_CMD_LEN, 10) != HAL_OK){};

	// recieve data from appropriate register
	for(int i = size - 1; i >= 0; i--)
	{
		while(HAL_SPI_Receive(hspi, &pRxData[i], 1, 10)!= HAL_OK){};
	}

	// Read a last throwaway byte to account for errors
	while(HAL_SPI_Receive(hspi, &read_command[3], 1, 10)!= HAL_OK){};
		
	// Chip select high
	HAL_GPIO_WritePin(SPI_FRAM_CS_GPIO_Port, SPI_FRAM_CS_Pin, GPIO_PIN_SET);
		
	// Free the lock
	Free_Lock(hspi, huart);
}
/**
  * @brief  Write to the FRAM
  * @param  address: 16 bit address
  * @param  pTxData: pointer to reception data buffer to be
  * @param  size: size of the data you are Transmiting (# of bytes)
  */
void SPI_FRAM_Write(SPI_HandleTypeDef *hspi, uint16_t address, uint8_t *pTxData, uint8_t size, UART_HandleTypeDef *huart, uint8_t timeoutThreshold)
{
	// Acquire the SPI FRAM lock
	Get_Lock(hspi, huart, timeoutThreshold);
	
	// Chip select low
	HAL_GPIO_WritePin(SPI_FRAM_CS_GPIO_Port, SPI_FRAM_CS_Pin, GPIO_PIN_RESET);
	
	// initialize write command bytes
	uint8_t write_command[WRITE_CMD_LEN] = {WREN_OP, 			// enable write operation
											WRITE_OP,			// write operation code
											address>>8,			// MSB of address
											(uint8_t)address}; 	// LSB of address

	// initiate write operation
	HAL_SPI_Transmit(hspi, &write_command[0], 1, 10);

	// Chip select high
	HAL_GPIO_WritePin(SPI_FRAM_CS_GPIO_Port, SPI_FRAM_CS_Pin, GPIO_PIN_SET);
																					
	HAL_Delay(1);																				
	
	// Chip select low
	HAL_GPIO_WritePin(SPI_FRAM_CS_GPIO_Port, SPI_FRAM_CS_Pin, GPIO_PIN_RESET);
																					
	HAL_SPI_Transmit(hspi, &write_command[1], 3, 10);																					
																					
	for(int i = size - 1; i >= 0; i--)
	{
		HAL_SPI_Transmit(hspi, &pTxData[i], 1, 10);
	}

	// Chip select high
	HAL_GPIO_WritePin(SPI_FRAM_CS_GPIO_Port, SPI_FRAM_CS_Pin, GPIO_PIN_SET);																			
	HAL_Delay(1);																				
	// Chip select low
	HAL_GPIO_WritePin(SPI_FRAM_CS_GPIO_Port, SPI_FRAM_CS_Pin, GPIO_PIN_RESET);
	
	// terminate write operation
	uint8_t wrdi = WRDI_OP; 
	HAL_SPI_Transmit(hspi, &wrdi, 1, 10);

	// Chip select high
	HAL_GPIO_WritePin(SPI_FRAM_CS_GPIO_Port, SPI_FRAM_CS_Pin, GPIO_PIN_SET);
	
	// Free the lock
	Free_Lock(hspi, huart);
}

/**
  * @brief  Get the lock to reserve access to the FRAM, like mutex_lock
  * @param  The SPI connection to the FRAM
  * @param  The UART used for debugging, set the DEBUG macro in the SPI_FRAM.h file to 1
  */
void Get_Lock(SPI_HandleTypeDef *hspi, UART_HandleTypeDef *huart, uint8_t timeoutThreshold)
{
	#if (DEBUG) 
		char *msg1 = "\nWAITING FOR LOCK....."; 
		char msg2[100];
	#endif
	uint8_t timeout = 0;
	
	do
	{
		#if (DEBUG)
			HAL_UART_Transmit(huart, (uint8_t *)msg1, strlen(msg1), 1);
			sprintf(msg2, "IN1: %d     IN2: %d\n",
							 HAL_GPIO_ReadPin(SPI_FRAM_IN1_GPIO_Port, SPI_FRAM_IN1_Pin),
							 HAL_GPIO_ReadPin(SPI_FRAM_IN2_GPIO_Port, SPI_FRAM_IN2_Pin));
			HAL_UART_Transmit(huart, (uint8_t *)msg2, strlen(msg2), 1);
			HAL_Delay(500);
		#endif
		if (timeoutThreshold != 0 && timeout++ > timeoutThreshold) return;

		//If M1 & M2 are set
	} while (HAL_GPIO_ReadPin(SPI_FRAM_IN1_GPIO_Port, SPI_FRAM_IN1_Pin) == GPIO_PIN_RESET || 
				HAL_GPIO_ReadPin(SPI_FRAM_IN2_GPIO_Port, SPI_FRAM_IN2_Pin) == GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(SPI_FRAM_LOCK_GPIO_Port, SPI_FRAM_LOCK_Pin, GPIO_PIN_RESET);
	
	while(HAL_GPIO_ReadPin(SPI_FRAM_IN1_GPIO_Port, SPI_FRAM_IN1_Pin) == GPIO_PIN_RESET || 
					HAL_GPIO_ReadPin(SPI_FRAM_IN2_GPIO_Port, SPI_FRAM_IN2_Pin) == GPIO_PIN_RESET)
	{
		# if (DEBUG) 
			HAL_UART_Transmit(huart, (uint8_t *)msg1, strlen(msg1), 1); 
		#endif

		HAL_GPIO_WritePin(SPI_FRAM_LOCK_GPIO_Port, SPI_FRAM_LOCK_Pin, GPIO_PIN_SET); //let lock go
		for(int i = 0; i < 50; i++); // Delay for an arbitrary amount to avoid future collisions

		HAL_GPIO_WritePin(SPI_FRAM_LOCK_GPIO_Port, SPI_FRAM_LOCK_Pin, GPIO_PIN_RESET);
		if (timeoutThreshold != 0 && timeout++ > timeoutThreshold) return;
	}
}

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
	
	HAL_GPIO_WritePin(SPI_FRAM_LOCK_GPIO_Port, SPI_FRAM_LOCK_Pin, GPIO_PIN_SET);	
}
