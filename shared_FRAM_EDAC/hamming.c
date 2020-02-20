//Hamming Source

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "hamming.h"


/* 
 * Generates the parity(k) for the data(n) and returns it
 * with the data (n+k)
 * 
 */
uint8_t
parity_generator (uint8_t *in_data) 
{
	uint8_t parity = 0;
	uint8_t data = *in_data;

	uint8_t p1 = ONE(data) ^ TWO(data) ^ FOU(data) ^ FIV(data) ^ SEV(data); 
	uint8_t p2 = ONE(data) ^ THR(data) ^ FOU(data) ^ SIX(data) ^ SEV(data);
	uint8_t p3 = TWO(data) ^ THR(data) ^ FOU(data) ^ EIG(data);
	uint8_t p4 = FIV(data) ^ SIX(data) ^ SEV(data) ^ EIG(data);

	parity = parity | p1 | (p2 << 1) | (p3 << 2) | (p4 << 3);
	return parity;	
}

/* 
 * Generates the syndrome(S) for the data(n+k) and returns it
 *
 */
uint8_t 
syndrome_generator (uint16_t *in_data)
{
	uint8_t syn = 0;
	uint8_t data = *in_data & 0x00FF;
	uint8_t p = *in_data >> 8;

	uint8_t s1 = ONE(data) ^ TWO(data) ^ FOU(data) ^ FIV(data) ^ SEV(data) ^ ONE(p); 
	uint8_t s2 = ONE(data) ^ THR(data) ^ FOU(data) ^ SIX(data) ^ SEV(data) ^ TWO(p);
	uint8_t s3 = TWO(data) ^ THR(data) ^ FOU(data) ^ EIG(data) ^ THR(p);
	uint8_t s4 = FIV(data) ^ SIX(data) ^ SEV(data) ^ EIG(data) ^ FOU(p);

	syn = syn | s1 | (s2 << 1) | (s3 << 2) | (s4 << 3);
	return syn;
}

/* 
 * Generates the parity(k) for the data(n) and returns it
 * with the data (n+k)
 *
 */
uint8_t
syndrome_decoder (uint8_t *syndrome)
{
	//Determine which bits are wrong based on the syndrome bits
		//What exactly do the syndrome bits represent?
		//Syndrome bits represent which parity bits are mismatched
		  //If any syndrome bit is 1, then that corresponding parity bit is
		  //different
	single_bit_errors syn = *syndrome;
	uint8_t correction_code = 0;

	switch (syn) 
	{
		case D1_DIFF:
		    correction_code |= 0x01; 
			break;
		case D2_DIFF:
			correction_code |= 0x02;
			break;
		case D3_DIFF:
			correction_code |= 0x04;
			break;
		case D4_DIFF:
			correction_code |= 0x08;
			break;
		case D5_DIFF:
			correction_code |= 0x10;
			break;
		case D6_DIFF:
			correction_code |= 0x20;
			break;
		case D7_DIFF:
			correction_code |= 0x40;
			break;
		case D8_DIFF:
			correction_code |= 0x80;
			break;
		case NO_DIFF:
			break;
		default:
			puts("syndrome out of range");
			exit(0);
			break;
	}

	//Returns an 8 bit value that can be used to correct the data
	return correction_code;
}

/* 
 * Takes in the data(n+k) and the syndrome(S) and corrects the
 * errors if there are any
 *
 */
uint8_t
error_corrector (uint8_t *out_data, uint8_t *corr_code)
{
	//Basically just XOR's syndrome_decoder's return with the data
	//and then returns the XOR's value as the "corrected" value
	return *out_data ^ *corr_code;
}


