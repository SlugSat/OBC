#include "PowerModes.h"

/* Initialize Variables */
static uint8_t firstTransition = 0;
static uint8_t shortCheck = 0;
static uint8_t checkBatt = FALSE;
/* Set Initial state */
static States state = Detumble;
static States prevState = Detumble;

/* Setup the communication handlers */
static I2C_HandleTypeDef *i2c;
static SPI_HandleTypeDef *framSPI;
static UART_HandleTypeDef *uartDebug;
static TIM_HandleTypeDef *timer;

void Power_Modes_State_Machine_Init(I2C_HandleTypeDef *hi2cTest, SPI_HandleTypeDef *hspi, UART_HandleTypeDef *huart, TIM_HandleTypeDef *htim)
{
	i2c = hi2cTest;
	framSPI = hspi;
	timer = htim;
	uartDebug = huart;
	
	/* Initialize pins for the shared memory */
	SPI_FRAM_Init(framSPI);
	
	/* Initialize the current controllers */
	Initialize_All_Current_Sensors(i2c);
	
	/* Initialize the fuel gauge */
	Fuel_Gauge_Init(i2c);
	
	/* Start Timer for interrupt drive fuel gauge check */
	HAL_TIM_Base_Start(timer);
	
	/* Start Timer Interrupt Handler */
	HAL_TIM_Base_Start_IT(timer);
}




uint8_t Power_Modes_State_Machine_Run(void)
{
	char msg[200] = {0};
	
	if (checkBatt)
	{
		// Check battery level
		float battPercentage = Get_Voltage(i2c, 0); // Currently returns a value in volts
		// Write the battery level to the fram
		uint8_t battBytes[4] = {0};
		float_to_bytes(battPercentage, battBytes);
		SPI_FRAM_Write(framSPI, SPI_FRAM_BATT_LEVEL_ADDR, battBytes, 4, uartDebug, 0);
		Set_BatteryLevel(battPercentage);
		
		// Check the science event pin
		uint8_t scienceStatus = 0;
		if (HAL_GPIO_ReadPin(SCIENCE_EVENT_GPIO_Port, SCIENCE_EVENT_Pin) == GPIO_PIN_SET)
		{
			scienceStatus = Set_ScienceEvent(TRUE);
		}
		else
		{
			scienceStatus = Set_ScienceEvent(FALSE);
		}
		
		// Check if there is a short in any of the rails
//		Check_for_Shorts(i2c, &shortCheck);
		
		// Get whether the craft is detumbling or not
		uint8_t stable[1] = {0};
		SPI_FRAM_Read(framSPI, SPI_FRAM_MECH_STATE_ADDR, stable, 1, uartDebug, 0);
		if (stable[0] != 0x2) // Detumble
		{
			change_variables(STABLE, 0);
		}
		
		// Get the solar vector status
		uint8_t currentSensor[1] = {0};
		SPI_FRAM_Read(framSPI, SPI_FRAM_SOLAR_VECTOR_ADDR, currentSensor, 1, uartDebug, 0);
		change_variables(SOLAR, currentSensor[0]);
		
		
		checkBatt = FALSE;
		snprintf(msg, 200, "\nState: %u    Batt: %f     Shorts: 0x%02X     ScienceStatus: 0x%02x    SolarVector: 0x%02x\n\n", state, battPercentage, shortCheck, scienceStatus, currentSensor[0]);
		HAL_UART_Transmit(uartDebug, (uint8_t *)msg, strlen(msg), 100);
	}
	
	if (state != prevState)
	{
		firstTransition = 0;
		SPI_FRAM_Write(framSPI, SPI_FRAM_PM_STATE_ADDR, (uint8_t *) &state, 1, uartDebug, 0);
	}
	prevState = state;
	switch (state)
	{
		/* In Detumble mode */
		case (Detumble): 
			// Set rails high for this state
			if (firstTransition == 0)
			{
				Output_Power_Pins(state);
				firstTransition = 1;
			}
			state = Transition(Detumble, framSPI, uartDebug);
			break;
		/* In Kill mode */
		case (Kill): 
			// Set rails high for this state
			if (firstTransition == 0)
			{
				Output_Power_Pins(state);
				firstTransition = 1;
			}
			state = Transition(Kill, framSPI, uartDebug);
			return Kill;
		/* In Normal mode */
		case (Normal): 
			// Set rails high for this state
			if (firstTransition == 0)
			{
				Output_Power_Pins(state);
				firstTransition = 1;
			}
			state = Transition(Normal, framSPI, uartDebug);
			break;
		/* In UltraLowPower mode */	
		case (UltraLowPower): 
			// Set rails high for this state
			if (firstTransition == 0)
			{
				Output_Power_Pins(state);
				firstTransition = 1;
			}
			state = Transition(UltraLowPower, framSPI, uartDebug);
			break;
		/* In LowPower mode */
		case (LowPower): 
			// Set rails high for this state
			if (firstTransition == 0)
			{
				Output_Power_Pins(state);
				firstTransition = 1;
			}
			state = Transition(LowPower, framSPI, uartDebug);
			break;
		/* In Eclipse mode */
		case (Eclipse): 
			// Set rails high for this state
			if (firstTransition == 0)
			{
				Output_Power_Pins(state);
				firstTransition = 1;
			}
			state = Transition(Eclipse, framSPI, uartDebug);
			break;
		/* In ScienceOnly mode */
		case (ScienceOnly): 
			// Set rails high for this state
			if (firstTransition == 0)
			{
				Output_Power_Pins(state);
				firstTransition = 1;
			}
			state = Transition(ScienceOnly, framSPI, uartDebug);
			break;			
	}
	return state;
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
  if (GPIO_PIN == DIE_INT_Pin)
	{
		change_variables(DIE, 0);
		HAL_GPIO_TogglePin(GPIOA , GPIO_PIN_5);
	}
	else 
	{
		__NOP();
	}
}

void Output_Power_Pins(uint8_t currState)
{	
	// Set the MechanicalSys power mode
	if (currState == Detumble || currState == Normal || currState == LowPower || currState == UltraLowPower || currState == Eclipse)
	{
		if ((shortCheck & 0x16) == 0) // Check if there was a short in the rail
		{
			HAL_GPIO_WritePin(Mech_Rail_GPIO_Port, Mech_Rail_Pin, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(Mech_Rail_GPIO_Port, Mech_Rail_Pin, GPIO_PIN_RESET);
		}
	}
	else
	{
		HAL_GPIO_WritePin(Mech_Rail_GPIO_Port, Mech_Rail_Pin, GPIO_PIN_RESET);
	}
	
	// Set the power for CC and Telemetry systems
	if (currState == Detumble || currState == Normal || currState == LowPower || currState == UltraLowPower || currState == Eclipse || currState == ScienceOnly)
	{
		if ((shortCheck & 0x14) == 0) // Check if there was a short in the rail
		{
			HAL_GPIO_WritePin(Memory_Rail_GPIO_Port, Memory_Rail_Pin, GPIO_PIN_SET);
			if (currState != Detumble)
			{
				HAL_GPIO_WritePin(Telemetry_Rail_GPIO_Port, Telemetry_Rail_Pin, GPIO_PIN_SET);
			}
		}
		else
		{
			HAL_GPIO_WritePin(Telemetry_Rail_GPIO_Port, Telemetry_Rail_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(Memory_Rail_GPIO_Port, Memory_Rail_Pin, GPIO_PIN_RESET);
		}
	}
	else
	{
		HAL_GPIO_WritePin(Telemetry_Rail_GPIO_Port, Telemetry_Rail_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Memory_Rail_GPIO_Port, Memory_Rail_Pin, GPIO_PIN_RESET);
	}
	
	// Set the power for the Science payload systems
	if (currState == ScienceOnly)
	{
		if ((shortCheck & 0x4C) == 0) // Check if there was a short in the rail
		{
			HAL_GPIO_WritePin(Scie_Rail_GPIO_Port, Scie_Rail_Pin, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(Scie_Rail_GPIO_Port, Scie_Rail_Pin, GPIO_PIN_RESET);
		}
	}
	else 
	{
		HAL_GPIO_WritePin(Scie_Rail_GPIO_Port, Scie_Rail_Pin, GPIO_PIN_RESET);
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
		HAL_GPIO_WritePin(DEAD_GPIO_Port, DEAD_Pin, GPIO_PIN_SET);
		
		HAL_GPIO_WritePin(LT_Rail_GPIO_Port, LT_Rail_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Scie_Rail_GPIO_Port, Scie_Rail_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Telemetry_Rail_GPIO_Port, Telemetry_Rail_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Mech_Rail_GPIO_Port, Mech_Rail_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Memory_Rail_GPIO_Port, Memory_Rail_Pin, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(DEAD_GPIO_Port, DEAD_Pin, GPIO_PIN_RESET);
	}
}

/* TIMER INTERRUPT SERVICE ROUTINE */
/**
  * @brief This function handles TIM6 update event interrupt.
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		checkBatt = TRUE;
}

void *change_variables(uint8_t type, uint8_t solarStatus)
{
	uint8_t temp = 0;
	
	switch(type)
	{
		case (STABLE):
			temp = TRUE;
			Set_Stable(temp);
			break;
		case (DIE):
			temp = TRUE;
			Set_Die(temp);
			break;
		case (SOLAR):
			temp = solarStatus;
			Set_SolarVector(temp);
	}
	return NULL;	
}

/* Set the intial power modes of each system */
void Initialize_Functions(system_function *functions)
{
	// Initialize everything as off except what will always be on
	functions->MechanicalSys = NoPower;
	functions->MechanicalMCU = Power; // Always On
	functions->LinearTransponderSys = NoPower;
	functions->LinearTransponderMCU = NoPower;
	functions->TelemetrySys = NoPower;
	functions->TelemetryMCU = NoPower; 
	functions->SciencePayloadSys = NoPower;
	functions->SciencePayloadMCU = NoPower;	
	return;
}

/* Sets the power mode of each of the systems */
void Set_PowerModes(system_function *function, uint8_t state)
{
	Set_Mechanical(function, state);
	Set_LinearTransponder(function, state);
	Set_Telemetry(function, state);
	Set_SciencePayload(function, state);
	return;
}

/* Set the power mode for mechanical */
void Set_Mechanical(system_function *function, uint8_t state)
{
	// Set the MechanicalSys power mode
	if (state == Detumble || state == Normal || state == LowPower)
	{
		function->MechanicalSys = Power;
	}
	else if (state == UltraLowPower || state == Eclipse)
	{
		function->MechanicalSys = LimitedPower;
	}
	else // if (state == Kill || state == ScienceOnly)
	{
		function->MechanicalSys = NoPower;
	}
	return;
}

/* Set the power mode for linear transponder */
void Set_LinearTransponder(system_function *function, uint8_t state)
{
	// Set the LinearTransponderSys power mode
	if (state == Normal)
	{
		function->LinearTransponderSys = Power;
	}
	else if (state == Eclipse)
	{
		function->LinearTransponderSys = LimitedPower;
	}
	else // if (state == Detumble || state == Kill || state == UltraLowPower || state == LowPower || state == ScienceOnly)
	{
		function->LinearTransponderSys = NoPower;
	}
	
	// Set the LinearTransponderMCU power mode
	if (state == Detumble || state == Normal || state == UltraLowPower || state == LowPower || state == Eclipse || state == ScienceOnly)
	{
		function->LinearTransponderMCU = Power;
	}
	else if (OFF)
	{
		function->LinearTransponderMCU = LimitedPower;
	}
	else // if (state == Kill)
	{
		function->LinearTransponderMCU = NoPower;
	}
	
	
	return;
}

/* Set the power mode for telemery */
void Set_Telemetry(system_function *function, uint8_t state)
{
	// Set TelemetrySys power mode
	if (state == Normal || state == LowPower)
	{
		function->TelemetrySys = Power;
	}
	else if (state == UltraLowPower || state == Eclipse)
	{
		function->TelemetrySys = LimitedPower;
	}
	else // if (state == Detumble || state == Kill || state == ScienceOnly)
	{
		function->TelemetrySys = NoPower;
	}
	
	// Set TelemetryMCU power mode
	if (state == Detumble || state == Normal || state == UltraLowPower || state == LowPower || state == Eclipse || state == ScienceOnly)
	{
		function->TelemetryMCU = Power;
	}
	else if (OFF)
	{
		function->TelemetryMCU = LimitedPower;
	}
	else // if (state == Kill)
	{
		function->TelemetryMCU = NoPower;
	}
	return;
}

/* Set the power mode for science payload */
void Set_SciencePayload(system_function *function, uint8_t state)
{
	// Set SciencePayloadSys power mode
	if (state == Normal || state == ScienceOnly)
	{
		function->SciencePayloadSys = Power;
	}
	else if (state == Eclipse)
	{
		function->SciencePayloadSys = LimitedPower;
	}
	else // if (state == Detumble || state == Kill || state == UltraLowPower || state == LowPower)
	{
		function->SciencePayloadSys = NoPower;
	}
	
	// Set SciencePayloadMCU power mode
	if (state == Detumble || state == Normal || state == Eclipse || state == ScienceOnly)
	{
		function->SciencePayloadMCU = Power;
	}
	else if (OFF)
	{
		function->SciencePayloadMCU = LimitedPower;
	}
	else // if (state == Kill || state == UltraLowPower || state == LowPower)
	{
		function->SciencePayloadMCU = NoPower;
	}
	return;
}

/* Transition between the states in the state machine */
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



