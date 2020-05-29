#include "SatelliteControl.h"
#include "Fuel_Gauge_Functions.h"
#include "SPI_FRAM.h"
#include "Current_Control_Functions.h"
#include <stdlib.h>
#include <stdint.h>

/* Initialize Variables */
//static uint8_t firstTransition = 0;
static uint8_t shortCheck = 0;

/* Setup the communication handlers */
static I2C_HandleTypeDef *i2c;
static SPI_HandleTypeDef *framSPI;
static UART_HandleTypeDef *uartDebug;


void Sat_Run_Init(I2C_HandleTypeDef *hi2cTest, SPI_HandleTypeDef *hspi, UART_HandleTypeDef *huart)
{
	i2c = hi2cTest;
	framSPI = hspi;
	uartDebug = huart;
	
	/* Initialize pins for the shared memory */
	SPI_FRAM_Init(framSPI);
	
	/* Initialize the current controllers */
	Initialize_All_Current_Sensors(i2c);
	
	/* Initialize the fuel gauge */
	Fuel_Gauge_Init(i2c);
}

uint8_t Sat_Run(uint8_t state){
	
		switch (state) {
		case (Detumble): 
			Output_Power_Pins(state);
			state = Transition(Detumble, framSPI, uartDebug);
			break;
			
		case (Kill): 
			Output_Power_Pins(state);
			state = Transition(Kill, framSPI, uartDebug);
			return Kill;

		case (Normal): 
			Output_Power_Pins(state);
			state = Transition(Normal, framSPI, uartDebug);
			break;

		case (UltraLowPower): 
			Output_Power_Pins(state);
			state = Transition(UltraLowPower, framSPI, uartDebug);
			break;

		case (LowPower): 
			Output_Power_Pins(state);
			state = Transition(LowPower, framSPI, uartDebug);
			break;
			
		case (Eclipse): 
			Output_Power_Pins(state);
			state = Transition(Eclipse, framSPI, uartDebug);
			break;

		case (ScienceOnly): 
			Output_Power_Pins(state);
			state = Transition(ScienceOnly, framSPI, uartDebug);
			break;			
	}
	return state;
}




void Output_Power_Pins(uint8_t currState)
{	
	// Set the MechanicalSys power mode
	if (currState == Detumble || currState == Normal || currState == LowPower || currState == UltraLowPower || currState == Eclipse)
	{
		if ((shortCheck & 0x16) == 0) // Check if there was a short in the rail
		{
			//HAL_GPIO_WritePin(Mech_Rail_GPIO_Port, Mech_Rail_Pin, GPIO_PIN_SET);
		}
		else
		{
			//HAL_GPIO_WritePin(Mech_Rail_GPIO_Port, Mech_Rail_Pin, GPIO_PIN_RESET);
		}
	}
	else
	{
		//HAL_GPIO_WritePin(Mech_Rail_GPIO_Port, Mech_Rail_Pin, GPIO_PIN_RESET);
	}
	
	// Set the power for CC and Telemetry systems
	if (currState == Detumble || currState == Normal || currState == LowPower || currState == UltraLowPower || currState == Eclipse || currState == ScienceOnly)
	{
		if ((shortCheck & 0x14) == 0) // Check if there was a short in the rail
		{
			//HAL_GPIO_WritePin(Memory_Rail_GPIO_Port, Memory_Rail_Pin, GPIO_PIN_SET);
			if (currState != Detumble)
			{
				//HAL_GPIO_WritePin(Telemetry_Rail_GPIO_Port, Telemetry_Rail_Pin, GPIO_PIN_SET);
			}
		}
		else
		{
			//HAL_GPIO_WritePin(Telemetry_Rail_GPIO_Port, Telemetry_Rail_Pin, GPIO_PIN_RESET);
			//HAL_GPIO_WritePin(Memory_Rail_GPIO_Port, Memory_Rail_Pin, GPIO_PIN_RESET);
		}
	}
	else
	{
		//HAL_GPIO_WritePin(Telemetry_Rail_GPIO_Port, Telemetry_Rail_Pin, GPIO_PIN_RESET);
		//HAL_GPIO_WritePin(Memory_Rail_GPIO_Port, Memory_Rail_Pin, GPIO_PIN_RESET);
	}
	
	// Set the power for the Science payload systems
	if (currState == ScienceOnly)
	{
		if ((shortCheck & 0x4C) == 0) // Check if there was a short in the rail
		{
			//HAL_GPIO_WritePin(Scie_Rail_GPIO_Port, Scie_Rail_Pin, GPIO_PIN_SET);
		}
		else
		{
			//HAL_GPIO_WritePin(Scie_Rail_GPIO_Port, Scie_Rail_Pin, GPIO_PIN_RESET);
		}
	}
	else 
	{
		//HAL_GPIO_WritePin(Scie_Rail_GPIO_Port, Scie_Rail_Pin, GPIO_PIN_RESET);
	}
	
	// Set the LT power rail
	if (currState == Normal)
	{
		if ((shortCheck & 0x3F) == 0) // Check if there was a short in the rail
		{
			HAL_GPIO_WritePin(LT_Rail_GPIO_Port, LT_Rail_Pin, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(LT_Rail_GPIO_Port, LT_Rail_Pin, GPIO_PIN_RESET);
		}
	}
	else
	{
		HAL_GPIO_WritePin(LT_Rail_GPIO_Port, LT_Rail_Pin, GPIO_PIN_RESET);
	}
	
	// Set a pin when Kill mode is entered, used for debugging or shutting off all rails
	if (currState == Kill)
	{
		/*
		HAL_GPIO_WritePin(DEAD_GPIO_Port, DEAD_Pin, GPIO_PIN_SET);
		
		HAL_GPIO_WritePin(LT_Rail_GPIO_Port, LT_Rail_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Scie_Rail_GPIO_Port, Scie_Rail_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Telemetry_Rail_GPIO_Port, Telemetry_Rail_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Mech_Rail_GPIO_Port, Mech_Rail_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Memory_Rail_GPIO_Port, Memory_Rail_Pin, GPIO_PIN_RESET);
		*/
	}
	else
	{
		/*
		HAL_GPIO_WritePin(DEAD_GPIO_Port, DEAD_Pin, GPIO_PIN_RESET);
		*/
	}
}

States Transition(uint8_t event, SPI_HandleTypeDef *hspi, UART_HandleTypeDef *huart)
{
	// Not sure what types of input lead to a transition
	// Create a function once this is known
	
	// Delay the program for awhile to test they are correct
//	for (int i = 0; i < 100000000; i++);
	
	States ret = (States) event;
	
	if (event == Detumble)
	{
		ret = (States) Detumble_Transition();
	}
	else if (event == Kill)
	{
		ret = (States) Kill;
	}
	else if (event == Normal)
	{
		ret = (States) Normal_Transition();
	}
	else if (event == UltraLowPower)
	{
		ret = (States) UltraLowPower_Transition();
	}
	else if (event == LowPower)
	{
		ret = (States) LowPower_Transition();
	}
	else if (event == Eclipse)
	{
		ret = (States) Eclipse_Transition();
	}
	else if (event == ScienceOnly)
	{
		ret = (States) ScienceOnly_Transition(); 
	}
	return ret;
}






