#include "PowerModes.h"


#ifndef GLOBALS
#define GLOBALS
/* Global variables controlling events and signals */
uint8_t stable = 0;
uint8_t die = 0;
float batteryLevel = 100;
uint8_t scienceEvent = 0;
uint8_t solarVector = ON; 
#endif

/* Print out each global variable */
void Print_Globals(void)
{
	printf("Stable: %u\t", stable);
	printf("Die: %u\t", stable);
	printf("Solar Vector: %u\t", solarVector);
	printf("Science Event: %u\t", scienceEvent);
	printf("Battery level: %f\n", batteryLevel);
}

/* Set the stable global variable */
uint8_t Set_Stable(uint8_t change)
{
	stable = change;
	return change;
}
/* Set the die global variable */
uint8_t Set_Die(uint8_t change)
{
	die = change;
	return change;
}
/* Set the batteryLevel global variable */
uint8_t Set_ScienceEvent(uint8_t change)
{
	scienceEvent = change;
	return change;
}
/* Set the scienceEvent global variable */
uint8_t Set_SolarVector(uint8_t change)
{
	solarVector = change;
	return change;
}
/* Set the solarVector global variable */
float Set_BatteryLevel(float change)
{
	batteryLevel = change;
	return change;
}

/* State transition for Detumble */
uint8_t Detumble_Transition(void)
{

	if (die == FALSE)
	{
		if (stable == TRUE)
		{
			if ((solarVector == OFF) && (batteryLevel > ULTRA_LOW_BATT_IN))
			{
				return Eclipse;
			}
			else if ((solarVector == ON) && (batteryLevel > LOW_BATT_IN))
			{
				return Normal;
			}
			else if ((solarVector == ON) && (batteryLevel < LOW_BATT_IN) && (batteryLevel > ULTRA_LOW_BATT_IN))
			{
				return LowPower;
			}
			else if ((batteryLevel < ULTRA_LOW_BATT_IN))
			{
				return UltraLowPower;
			}
		}
	}
	else
	{
		return Kill;
	}
	return Detumble;
}

/* State transition for Eclipse */
uint8_t Eclipse_Transition(void)
{

	if (die == FALSE)
	{
		if (scienceEvent == FALSE)
		{
			if ((solarVector == OFF) && (batteryLevel > ULTRA_LOW_BATT_IN))
			{
				return Eclipse;
			}
			else if ((solarVector == ON) && (batteryLevel > LOW_BATT_IN))
			{
				return Normal;
			}
			else if ((solarVector == ON) && (batteryLevel < LOW_BATT_IN) && (batteryLevel > ULTRA_LOW_BATT_IN))
			{
				return LowPower;
			}
			else if ((batteryLevel < ULTRA_LOW_BATT_IN))
			{
				return UltraLowPower;
			}
		}
		else
		{
			return ScienceOnly;
		}
	}
	else
	{
		return Kill;
	}	
	return Eclipse;
}

/* State transition for Normal */
uint8_t Normal_Transition(void)
{

	if (die == FALSE)
	{
		if (scienceEvent == FALSE)
		{
			if ((solarVector == OFF) && (batteryLevel > ULTRA_LOW_BATT_IN))
			{
				return Eclipse;
			}
			else if ((solarVector == ON) && (batteryLevel > LOW_BATT_IN))
			{
				return Normal;
			}
			else if ((solarVector == ON) && (batteryLevel < LOW_BATT_IN) && (batteryLevel > ULTRA_LOW_BATT_IN))
			{
				return LowPower;
			}
			else if ((batteryLevel < ULTRA_LOW_BATT_IN))
			{
				return UltraLowPower;
			}
		}
		else
		{
			return ScienceOnly;
		}
	}
	else
	{
		return Kill;
	}
	return Normal;
}

/* State transition for LowPower */
uint8_t LowPower_Transition(void)
{
	if (die == FALSE)
	{
		if (scienceEvent == FALSE)
		{
			if ((solarVector == OFF) && (batteryLevel > ULTRA_LOW_BATT_IN))
			{
				return Eclipse;
			}
			else if ((solarVector == ON) && (batteryLevel > LOW_BATT_OUT))
			{
				return Normal;
			}
			else if ((solarVector == ON) && (batteryLevel < LOW_BATT_IN) && (batteryLevel > ULTRA_LOW_BATT_IN))
			{
				return LowPower;
			}
			else if ((batteryLevel < ULTRA_LOW_BATT_IN))
			{
				return UltraLowPower;
			}
		}
		else
		{
			return ScienceOnly;
		}
	}
	else
	{
		return Kill;
	}
	return LowPower;
}

/* State transition for UltraLowPower */
uint8_t UltraLowPower_Transition(void)
{
	if (die == FALSE)
	{
		if ((solarVector == OFF) && (batteryLevel > ULTRA_LOW_BATT_OUT))
		{
			return Eclipse;
		}
		else if ((solarVector == ON) && (batteryLevel > LOW_BATT_IN))
		{
			return Normal;
		}
		else if ((solarVector == ON) && (batteryLevel < LOW_BATT_IN) && (batteryLevel > ULTRA_LOW_BATT_OUT))
		{
			return LowPower;
		}
		else if ((batteryLevel < ULTRA_LOW_BATT_OUT))
		{
			return UltraLowPower;
		}
	}
	else
	{
		return Kill;
	}		
	return UltraLowPower;
}

/* State transition for ScienceOnly */
uint8_t ScienceOnly_Transition(void)
{
	if (die == FALSE)
	{
		if (batteryLevel < ULTRA_LOW_BATT_IN)
		{
			return UltraLowPower;
		}
		
		if (scienceEvent == FALSE)
		{
			if ((solarVector == OFF) && (batteryLevel > ULTRA_LOW_BATT_IN))
			{
				return Eclipse;
			}
			else if ((solarVector == ON) && (batteryLevel > LOW_BATT_IN))
			{
				return Normal;
			}
			else if ((solarVector == ON) && (batteryLevel < LOW_BATT_IN) && (batteryLevel > ULTRA_LOW_BATT_IN))
			{
				return LowPower;
			}
			else if ((batteryLevel < ULTRA_LOW_BATT_IN))
			{
				return UltraLowPower;
			}
		}
	}
	else
	{
		return Kill;
	}
	return ScienceOnly;
}

