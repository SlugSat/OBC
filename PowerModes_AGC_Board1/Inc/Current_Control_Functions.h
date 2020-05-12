#include "string.h"
#include <math.h> 
#include "main.h"

/* I2C slave address */
//Default Slave Address = 01000000
#define SLAVE_ADDRESS (0x80)
#define CURR_SENSE_ADDRESS_1 (0x40 << 1) // 1.8 V
#define CURR_SENSE_ADDRESS_2 (0x00 << 1) // 3.3 V
#define CURR_SENSE_ADDRESS_3 (0x00 << 1) // 5 V
#define CURR_SENSE_ADDRESS_4 (0x00 << 1) // + 5, -5
#define CURR_SENSE_ADDRESS_5 (0x00 << 1) // 8 V
#define CURR_SENSE_ADDRESS_6 (0x00 << 1) // 15 V
#define CURR_SENSE_ADDRESS_7 (0x00 << 1) // 32 V


/* Configuration Registers */
#define CONFIG_REG (0x00)

/* Calibration Registers */
#define CALIB_REG (0x05)

/* Output registers */
#define Shunt_Volt_REG (0x01)
#define Bus_Volt_REG (0x02)
#define Power_REG (0x03)
#define Current_REG (0x04)
	
/* Values for init function */	
#define CONFIG_REG_value (0x4F3F)
#define CALIB_REG_value (0x0521)	

#define FAIL (0)
#define SUCCESS (1)

#define SHORT_DETECT_5_LESS (500.0000) // In mA
#define SHORT_DETECT_8_MORE (1000.0000) // In mA

/* Function Prototypes */															
void CurrentSensorRead(I2C_HandleTypeDef *hi2c, uint8_t reg, uint16_t *recv, uint8_t slaveAddress);
void CurrentSensorWrite(I2C_HandleTypeDef *hi2c, uint8_t reg, uint16_t *send, uint8_t slaveAddress);
int  CurrentSensorInit(I2C_HandleTypeDef *hi2c, uint8_t slaveAddress);													
void Initialize_All_Current_Sensors(I2C_HandleTypeDef *hi2c);
void Check_for_Shorts(I2C_HandleTypeDef *hi2c1, uint8_t *shortCheck);

//The output will be in VOLTS													
float Get_Shunt_Voltage(I2C_HandleTypeDef *hi2c, uint8_t slaveAddress); //The output will be in VOLTS
float Get_Bus_Voltage(I2C_HandleTypeDef *hi2c, uint8_t slaveAddress); //The output will be in VOLTS
float Get_power(I2C_HandleTypeDef *hi2c, uint8_t slaveAddress); //The output will be in MILLI_WATTS
float Get_Current(I2C_HandleTypeDef *hi2c, uint8_t slaveAddress); //The output will be in MILLI_AMPS


