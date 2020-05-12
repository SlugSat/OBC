#include "Fuel_Gauge_Functions.h"

/* Multiplier constants used to multiply register value in order to get final result */
float capacity_multiplier_mAH = (0.005)/resistSensor; //refer to row "Capacity"
float current_multiplier_mV = (.0015625)/resistSensor; //refer to row "Current"
float voltage_multiplier_V = .000078125; //refer to row "Voltage"
float time_multiplier_Min = 5.625 / 3600; // 
float percentage_multiplier = 1.0 / 256.0; // Multiply the capacity percentage sensor reading by this
float temperature_multiplier = 1.0 / 256.0; // Multiply the temperature sensor  by this

void Fuel_Gauge_Read(I2C_HandleTypeDef *hi2c, uint8_t reg, uint16_t *recv)
{
	// Values are ent as bytes so make a buffer to get the bytes and then reassemble
	uint8_t recv_buff[2] = {0};
	
	// I2C Read
	HAL_I2C_Master_Transmit(hi2c, FG_SLAVE_ADDR, &reg, 1, 10);
	HAL_I2C_Master_Receive(hi2c, FG_SLAVE_ADDR, recv_buff, 2, 10);
	
	// Reassemble the bytes into the unsigned integer output
	*recv |= recv_buff[1];
	*recv <<= 8;
	*recv |= recv_buff[0];
}

void Fuel_Gauge_Write(I2C_HandleTypeDef *hi2c, uint8_t reg, uint16_t *send)
{
	// Write the value to the register
	uint8_t send_buff[3] = {reg, (uint8_t)(*send & 0x00FF), (uint8_t)((*send >> 8) & 0x00FF)};
	HAL_I2C_Master_Transmit(hi2c, FG_SLAVE_ADDR, send_buff, 3, 10);
}

void Fuel_Gauge_Init(I2C_HandleTypeDef *hi2c)
{
	// Used for configuring the fuel gauge
	static fg_config_t conf = {	6700, 		// design capacity of 3350mAh
														0x7D61, 	// empty voltage target = 2.5V, recovery voltage = 3.88V
														0x8020, 	// model cfg set for lithium NCR/NCA cell
														0x01A0, 	// charge termination current = 0.3A
														0x0000,
														6700/32,
														(6700/32)*44138/6700,
														0x8214,	 	// config1
														0x3658};	// config2		
	
	
	/**** Check chip status ****/
	uint16_t status = 0;
	Fuel_Gauge_Read(hi2c, STAT_REG, &status);
	
	// if POR (Power On Reset) bit is set we need to configure registers
	if (status & POR) 
	{	
		// Wait until FSTAT.DNR bit is unset indicating completion
		// of startup operations
		do {Fuel_Gauge_Read(hi2c, FSTAT_REG, &status);}
		while (status & FSTAT_DNR);
		
		/**** Initialize configuration ****/
		
		// store HiBCFG value
		Fuel_Gauge_Read(hi2c, HIBCFG_REG, &conf.hibcfg);
		
		// soft wake up command (step 1 of exiting hibernate mode)
		uint16_t cmd = SOFT_WAKE;
		Fuel_Gauge_Write(hi2c, SOFT_WAKEUP_REG, &cmd);
		
		// Clear HiBCFG and Soft WakeUp Registers
		// (step 2 of exiting hibernate mode)
		cmd = CLEAR;
		Fuel_Gauge_Write(hi2c, HIBCFG_REG, &cmd);
		Fuel_Gauge_Write(hi2c, SOFT_WAKEUP_REG, &cmd);
		
		// Configure OPTION 1 EZ Config
		Fuel_Gauge_Write(hi2c, DESIGN_CAP_REG, &conf.design_cap);
		Fuel_Gauge_Write(hi2c, V_EMPTY_REG, &conf.v_empty);
		Fuel_Gauge_Write(hi2c, I_CHG_REG, &conf.current_chg);
		Fuel_Gauge_Write(hi2c, CONF_REG, &conf.config1);
		Fuel_Gauge_Write(hi2c, CONF2_REG, &conf.config2);
		Fuel_Gauge_Write(hi2c, DQACC_REG, &conf.dQAcc);
		Fuel_Gauge_Write(hi2c, DPACC_REG, &conf.dPAcc);
		Fuel_Gauge_Write(hi2c, MODEL_CFG_REG, &conf.model_cfg);
		
		// Poll modelCFG refresh bit (MSb) until it is unset
		do {Fuel_Gauge_Read(hi2c, MODEL_CFG_REG, &status);}
		while (status & MODEL_CFG_REFRESH);
		
		// Write previously stored hibcfg value
		Fuel_Gauge_Write(hi2c, HIBCFG_REG, &conf.hibcfg);
		
		/**** Initialization is complete so we need to clear the POR bit ****/

		// Store the current status value
		Fuel_Gauge_Read(hi2c, STAT_REG, &status);
		
		// loop until POR bit has been successfully cleared
		while (status & POR) 
		{ 
			status &= 0xFFFD;
			Fuel_Gauge_Write(hi2c, STAT_REG, &status);
			HAL_Delay(1);
			Fuel_Gauge_Read(hi2c, STAT_REG, &status);
		}
	}
	
	// SUCCESS!!!!
	
}


/* Functions to get specific data from certain registers */
// Remaining capacity register
float Get_Remaining_Capacity(I2C_HandleTypeDef *hi2c)
{
	uint16_t recv = 0;
	Fuel_Gauge_Read(hi2c, REP_CAP_REG, &recv);
	float output = recv * capacity_multiplier_mAH; // State-of-charge percentage
	return output;
}

// State-of-charge percentage
float Get_Charge_Percentage(I2C_HandleTypeDef *hi2c) 
{
	uint16_t recv = 0;
	Fuel_Gauge_Read(hi2c, REP_SOC_REG, &recv);
	float output = recv * percentage_multiplier; 
	return output;
}

// Reports the maximum capacity of the battery
float Get_Max_Capacity(I2C_HandleTypeDef *hi2c) 
{
	uint16_t recv = 0;
	Fuel_Gauge_Read(hi2c, FULL_CAP_REG, &recv);
	float output = recv * capacity_multiplier_mAH; // Output in mAh
	return output;
}

// Time to empty
float Get_TTE(I2C_HandleTypeDef *hi2c) 
{
	uint16_t recv = 0;
	Fuel_Gauge_Read(hi2c, TTE_REG, &recv);
	float output = recv * time_multiplier_Min; // Output in minutes
	return output;
}

// Time to full
float Get_TTF(I2C_HandleTypeDef *hi2c) 
{
	uint16_t recv = 0;
	Fuel_Gauge_Read(hi2c, TTF_REG, &recv);
	float output = recv * time_multiplier_Min; // Output in minutes
	return output;
}

// Status of the fuel gauge
uint16_t Get_Status(I2C_HandleTypeDef *hi2c) 
{
	uint16_t recv = 0;
	Fuel_Gauge_Read(hi2c, STAT_REG, &recv);
	return recv;
}

// Voltage measured between BATT and CSP
float Get_Voltage(I2C_HandleTypeDef *hi2c, uint8_t average) 
{
	uint16_t recv = 0;
	if (average)
	{
		Fuel_Gauge_Read(hi2c, AVG_VOLTAGE_REG, &recv);
	}
	else
	{
		Fuel_Gauge_Read(hi2c, VOLTAGE_REG, &recv);
	}
	float output = recv * voltage_multiplier_V; // Output in volts
	return output;
}

float Get_FG_Current(I2C_HandleTypeDef *hi2c, uint8_t average)
{
	uint16_t recv = 0;
	if (average)
	{
		Fuel_Gauge_Read(hi2c, AVG_CURRENT_REG, &recv);
	}
	else
	{
		Fuel_Gauge_Read(hi2c, CURRENT_REG, &recv);
	}
	float output = (int16_t) recv * current_multiplier_mV;
	return output;
}

float Get_Temp(I2C_HandleTypeDef *hi2c)
{
	uint16_t recv = 0;
	Fuel_Gauge_Read(hi2c, TEMP_REG, &recv);
	float output = (int16_t) recv * temperature_multiplier;
	return output;
}
