/* Author: Sloan Liu
 * Project: SlugSat Year 4
 * SubTeam: On-Baord Computer
 * 
 * Rights to the code go to the SlugSat Year 4 team 
 * to use/modify as desired
 */

//EDAC Source

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "hamming.h"
#include "edac.h"


uint16_t 
parity_encode (uint8_t *raw_data)
{
	uint8_t p_bits = parity_generator(raw_data);
	uint16_t rp_bits = (p_bits << 8) | *raw_data;
	return rp_bits;
}



uint8_t 
parity_decode (uint16_t *enc_data)
{
	uint8_t d_bits = *enc_data & 0xFF;
	uint8_t s_bits = syndrome_generator(enc_data);
	uint8_t ec_bits = syndrome_decoder(&s_bits);
	uint8_t corrected_data = error_corrector(&d_bits, &ec_bits);
	return corrected_data;	
}


