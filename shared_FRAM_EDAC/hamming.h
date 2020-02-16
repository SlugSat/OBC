//Hamming Header

#include <stdint.h>

#define ONE(x) (x & 1)
#define TWO(x) ((x & 2) >> 1)
#define THR(x) ((x & 4) >> 2)
#define FOU(x) ((x & 8) >> 3)
#define FIV(x) ((x & 16) >> 4)
#define SIX(x) ((x & 32) >> 5)
#define SEV(x) ((x & 64) >> 6)
#define EIG(x) ((x & 128) >> 7)

typedef enum single_bit_errors {
	D1_DIFF = 0x3,
	D2_DIFF = 0x5,
	D3_DIFF = 0x6,
	D4_DIFF = 0x7,
	D5_DIFF = 0x9,
	D6_DIFF = 0xA,
	D7_DIFF = 0xB,
	D8_DIFF = 0xC,
	NO_DIFF = 0x0
} single_bit_errors;


uint8_t parity_generator (uint8_t *in_data);

uint8_t syndrome_generator (uint8_t *in_data, uint8_t *parity);

uint8_t syndrome_decoder (uint8_t *syndrome);

uint8_t error_corrector (uint8_t *out_data, uint8_t *corr_code);




