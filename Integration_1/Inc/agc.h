/*
 * agc.h
 *
 *  Created on: Mar 17, 2019
 *      Author: thomas
 */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef AGC_H_
#define AGC_H_

#define DAC_CH_VA DAC_CHANNEL_2
#define DAC_CH_VGA DAC_CHANNEL_1

void AGC_Init(void);
uint8_t AGC_DoEvent(void);


#endif /* AGC_H_ */
