#ifndef POWERMODES_H
#define POWERMODES_H

#include "main.h"
#include "SPI_FRAM.h"
#include "DateConversion.h"
#include "Current_Control_Functions.h"
#include "Fuel_Gauge_Functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include "Current_Control_Functions.h"

/* Define states and system function variables */
typedef enum States {Detumble, Kill, Normal, LowPower, UltraLowPower, Eclipse, ScienceOnly} States;

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


enum PowerLevel {Power, LimitedPower, NoPower};

typedef struct system_function 
{
	uint8_t MechanicalSys;
	uint8_t MechanicalMCU;
	uint8_t LinearTransponderSys;
	uint8_t LinearTransponderMCU;
	uint8_t TelemetrySys;
	uint8_t TelemetryMCU; 
	uint8_t SciencePayloadSys;
	uint8_t SciencePayloadMCU;
} system_function;

typedef struct events
{
	uint8_t die;
} events;


/* Define function prototypes */

void Power_Modes_State_Machine_Init(I2C_HandleTypeDef *hi2cTest, SPI_HandleTypeDef *hspi, UART_HandleTypeDef *huart, TIM_HandleTypeDef *htim);

uint8_t Power_Modes_State_Machine_Run(void);

void Output_Power_Pins(uint8_t currState);

/* Set the intial power modes of each system */
void Initialize_Functions(system_function *functions);

/* Sets the power mode of each of the systems */
void Set_PowerModes(system_function *function, uint8_t state);

/* Set the power mode for mechanical */
void Set_Mechanical(system_function *function, uint8_t state);

/* Set the power mode for linear transponder */
void Set_LinearTransponder(system_function *function, uint8_t state);

/* Set the power mode for telemery */
void Set_Telemetry(system_function *function, uint8_t state);

/* Set the power mode for science payload */
void Set_SciencePayload(system_function *function, uint8_t state);

/* Transition between the states in the state machine */
States Transition(uint8_t event, SPI_HandleTypeDef *hspi, UART_HandleTypeDef *huart);

/* Used for debugging and testing the system. Print out all of te current power modes. */
void Print_System_Settings(system_function *function);


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

/* Print each of the global variables */
void Print_Globals(void);

/* Set variables in transitions.c file */
uint8_t Set_Stable(uint8_t change);
uint8_t Set_Die(uint8_t change);
uint8_t Set_ScienceEvent(uint8_t change);
uint8_t Set_SolarVector(uint8_t change);
float Set_BatteryLevel(float change);

/* Thread calls which variables to change */
void *change_variables(uint8_t type, uint8_t solarStatus);

#endif
