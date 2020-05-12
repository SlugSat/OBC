#ifndef SPI_FRAM_LIB
#define SPI_FRAM_LIB
//This is the library that lets you use the SPI FRAM.
//please make sure that you have designated GPIO A9 as the chip select
//you are only allowed to use macros for adresses in both functions

#include "main.h"
#include <string.h>

// Used for debugging
#define DEBUG (0)

// Constants
#define WRITE_CMD_LEN	(4)
#define READ_CMD_LEN	(3) 

//opcodes
#define WRITE_OP        (2)
#define READ_OP         (3)
#define WRDI_OP         (4)
#define WREN_OP         (6)

//adresses
#define SPI_FRAM_LATITUDE_ADDR						(0)   // Latitude
#define SPI_FRAM_LONGITUDE_ADDR						(4)   // Longitude
#define SPI_FRAM_ALTITUDE_ADDR						(8)   // Altitude
#define SPI_FRAM_TIME_ADDR								(100) // Time 
#define SPI_FRAM_BATT_LEVEL_ADDR					(200) // Battery Level
#define SPI_FRAM_PM_STATE_ADDR						(300) // Power modes state
#define SPI_FRAM_LOG_DATA_TIME_ADDR				(400) // Log data at a certain time
#define SPI_FRAM_NUM_DATA_ADDR 						(500) 
#define SPI_FRAM_SOLAR_VECTOR_ADDR				(600)
#define SPI_FRAM_LT_STAT_ADDR							(700)
#define SPI_FRAM_LT_DAILY_USERS_ADDR 			(800)
#define SPI_FRAM_POWER_STAT_ADDR     			(900) 
#define SPI_FRAM_MECH_STATE_ADDR					(1000)

void SPI_FRAM_Init(SPI_HandleTypeDef *hspi);

void SPI_FRAM_Read(SPI_HandleTypeDef *hspi, uint16_t address, uint8_t *pRxData,uint8_t size, UART_HandleTypeDef *huart, uint8_t timeoutThreshold);

void SPI_FRAM_Write(SPI_HandleTypeDef *hspi, uint16_t address, uint8_t *pTxData,uint8_t size, UART_HandleTypeDef *huart, uint8_t timeoutThreshold);

void Get_Lock(SPI_HandleTypeDef *hspi, UART_HandleTypeDef *huart, uint8_t timeoutThreshold);

void Free_Lock(SPI_HandleTypeDef *hspi, UART_HandleTypeDef *huart);
#endif // SPI_FRAM_LIB
