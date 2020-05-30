/*
* SatelliteControl.h
* Modified Year 3 PowerMode.h
* Author: Andy
*
*/

#ifndef SATELLITECONTROL_H
#define SATELLITECONTROL_H

#include "main.h"
#include <stdlib.h>
#include <stdint.h>

//Macros
#define OFF (0x02)
#define ON (0x00)

#define FALSE (0)
#define TRUE  (1)

// Have a different voltage for going into and out of the low power states to prevent thrashing
// Also known as a histeuresis shift
#define ULTRA_LOW_BATT_IN 	(3.4000)
#define ULTRA_LOW_BATT_OUT  (3.500)
#define LOW_BATT_IN	 				(3.6000)
#define LOW_BATT_OUT 				(3.7000)

#define STABLE (1)
#define DIE (2)
#define SCI_EVENT (3)
#define BATT (4)
#define SOLAR (5)

/* Define states and system function variables */
typedef enum States {Detumble, Kill, Normal, LowPower, 
											UltraLowPower, Eclipse, ScienceOnly} States;

void Sat_Run_Init(
	I2C_HandleTypeDef *hi2cTest, SPI_HandleTypeDef *hspi, 
  UART_HandleTypeDef *huart);

uint8_t Sat_Run(uint8_t state);

void Output_Power_Pins(uint8_t currState);

States Transition(uint8_t event, SPI_HandleTypeDef *hspi, 
									UART_HandleTypeDef *huart);
											
											

/* State transition for Detumble */
uint8_t Detumble_Transition(void);

/* State transition for Eclipse */
uint8_t Eclipse_Transition(void);


/* State transition for Normal */
uint8_t Normal_Transition(void);

/* State transition for LowPower */
uint8_t LowPower_Transition(void);


/* State transition for UltraLowPower */
uint8_t UltraLowPower_Transition(void);


/* State transition for ScienceOnly */
uint8_t ScienceOnly_Transition(void);
#endif
