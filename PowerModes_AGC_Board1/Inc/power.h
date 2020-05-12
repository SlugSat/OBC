/**
 * Power modes state machine code 
 */

#ifndef _POWER_H_
#define _POWER_H_

#include <stdint.h>

#include "PowerModes.h"

/**
 * Do init work for the power state machine.
 */
void Power_Init(void);

/**
 * Handle any state transitions needed.
 */
void Power_DoEvent(void);

/**
 * Set pins associated with the current state
 *
 * \param currState		The current state to set pins for
 */
void Output_Power_Pins(uint8_t currState);

/**
 * ISR for power state machine
 *
 * \param GPIO_PIN		Which pin was interrupted
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN);

#endif