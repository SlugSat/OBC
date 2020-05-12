#include "main.h"
#include "power.h"

/* Private variables */
static uint16_t globalInterrupt = 0;
static States globalState = Detumble;
static States state;

static system_function functions;
static uint8_t firstTransition = 0;

/* System handles - marked as extern to reference the ones in the main.c */
extern I2C_HandleTypeDef hi2c1;
extern SPI_HandleTypeDef hspi2;
extern UART_HandleTypeDef huart2;

void Power_Init()
{
    /* Initialize the starting state of each of the systems that need power */
    Initialize_Functions(&functions);
    /*initialize the current controller*/
    init(&hi2c1);
    /* Set Initial state */
    state = Detumble;
}

void Power_DoEvent()
{
    if (state != globalState)
    {
        firstTransition = 0;
    }
	
    globalState = state;
    int tmp;
    switch (state)
    {
    /* In Detumble mode */
    case (Detumble):
        Set_PowerModes(&functions, Detumble);
        // Set rails high for this state
        if (firstTransition == 0)
        {
            Output_Power_Pins(state);
            firstTransition = 1;
        }
        state = Transition(Detumble, &hspi2, &huart2);
        tmp = state == Detumble ? GPIO_PIN_SET : GPIO_PIN_RESET;
        break;
    /* In Kill mode */
    case (Kill):
        Set_PowerModes(&functions, Kill);
        // Set rails high for this state
        if (firstTransition == 0)
        {
            Output_Power_Pins(state);
            firstTransition = 1;
        }
        state = Transition(Kill, &hspi2, &huart2);
        tmp = state == Kill ? GPIO_PIN_SET : GPIO_PIN_RESET;
        break;
    /* In Normal mode */
    case (Normal):
        Set_PowerModes(&functions, Normal);
        // Set rails high for this state
        if (firstTransition == 0)
        {
            Output_Power_Pins(state);
            firstTransition = 1;
        }
        state = Transition(Normal, &hspi2, &huart2);
        tmp = state == Normal ? GPIO_PIN_SET : GPIO_PIN_RESET;
        break;
    /* In UltraLowPower mode */
    case (UltraLowPower):
        Set_PowerModes(&functions, UltraLowPower);
        // Set rails high for this state
        if (firstTransition == 0)
        {
            Output_Power_Pins(state);
            firstTransition = 1;
        }
        state = Transition(UltraLowPower, &hspi2, &huart2);
        tmp = state == UltraLowPower ? GPIO_PIN_SET : GPIO_PIN_RESET;
        break;
    /* In LowPower mode */
    case (LowPower):
        Set_PowerModes(&functions, LowPower);
        // Set rails high for this state
        if (firstTransition == 0)
        {
            Output_Power_Pins(state);
            firstTransition = 1;
        }
        state = Transition(LowPower, &hspi2, &huart2);
        tmp = state == LowPower ? GPIO_PIN_SET : GPIO_PIN_RESET;
        break;
    /* In Eclipse mode */
    case (Eclipse):
        Set_PowerModes(&functions, Eclipse);
        // Set rails high for this state
        if (firstTransition == 0)
        {
            Output_Power_Pins(state);
            firstTransition = 1;
        }
        state = Transition(Eclipse, &hspi2, &huart2);
        tmp = state == Eclipse ? GPIO_PIN_SET : GPIO_PIN_RESET;
        break;
    /* In ScienceOnly mode */
    case (ScienceOnly):
        Set_PowerModes(&functions, ScienceOnly);
        // Set rails high for this state
        if (firstTransition == 0)
        {
            Output_Power_Pins(state);
            firstTransition = 1;
        }
        state = Transition(ScienceOnly, &hspi2, &huart2);
        tmp = state == ScienceOnly ? GPIO_PIN_SET : GPIO_PIN_RESET;
        break;
    /* An error occurred */
    default:
        state = INVALID; // Error
        break;
    }

}


void Output_Power_Pins(uint8_t currState)
{
    HAL_GPIO_WritePin(GPIOA, Mech_Rail_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, Scie_Rail_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, Memory_Rail_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, LT_Rail_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, DEAD_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, Telemetry_Rail_Pin, GPIO_PIN_RESET);

    // Set the MechanicalSys power mode
    if (currState == Detumble || currState == Normal || currState == LowPower || currState == UltraLowPower || currState == Eclipse)
    {
        HAL_GPIO_WritePin(GPIOA, Mech_Rail_Pin, GPIO_PIN_SET);
    }

    // Set the power for CC and Telemetry systems
    if (currState == Detumble || currState == Normal || currState == LowPower || currState == UltraLowPower || currState == Eclipse || currState == ScienceOnly)
    {
        HAL_GPIO_WritePin(GPIOB, Memory_Rail_Pin, GPIO_PIN_SET);
        if (currState != Detumble)
        {
            HAL_GPIO_WritePin(GPIOB, Telemetry_Rail_Pin, GPIO_PIN_SET);
        }
    }

    // Set the power for the Science payload systems
    if (currState == ScienceOnly)
    {
        HAL_GPIO_WritePin(GPIOA, Scie_Rail_Pin, GPIO_PIN_SET);
    }

    // Set the LT power rail
    if (currState == Normal || currState == LowPower || currState == UltraLowPower || currState == Eclipse)
    {
        HAL_GPIO_WritePin(GPIOB, LT_Rail_Pin, GPIO_PIN_SET);
    }

    // Set a pin when Kill mode is entered, used for debugging
    if (currState == Kill)
    {
        HAL_GPIO_WritePin(GPIOB, DEAD_Pin, GPIO_PIN_SET);
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
    //HAL_GPIO_TogglePin(GPIOA , GPIO_PIN_5);
    if (GPIO_PIN == STABLE_INT_Pin)
    {
        change_variables(STABLE);
        globalInterrupt = STABLE_INT_Pin;
        //HAL_GPIO_TogglePin(GPIOA , GPIO_PIN_5);
    }
    else if (GPIO_PIN == SCI_INT_Pin)
    {
        change_variables(SCI_EVENT);
        globalInterrupt = SCI_INT_Pin;
        //HAL_GPIO_TogglePin(GPIOA , GPIO_PIN_5);
    }
    else if (GPIO_PIN == DIE_INT_Pin)
    {
        change_variables(DIE);
        globalInterrupt = DIE_INT_Pin;
        HAL_GPIO_TogglePin(GPIOA , GPIO_PIN_5);
    }
    else if (GPIO_PIN == BATT_INT_Pin)
    {
        change_variables(BATT);
        globalInterrupt = BATT_INT_Pin;
        //HAL_GPIO_TogglePin(GPIOA , GPIO_PIN_5);
    }
    else if (GPIO_PIN == SOLAR_INT_Pin)
    {
        change_variables(SOLAR);
        globalInterrupt = SOLAR_INT_Pin;
        //HAL_GPIO_TogglePin(GPIOA , GPIO_PIN_5);
    }
    else
    {
        __NOP();
    }
}