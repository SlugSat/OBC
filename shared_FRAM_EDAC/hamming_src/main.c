/* Author: Sloan Liu
 * Project: SlugSat Year 4
 * SubTeam: On-Baord Computer
 * 
 * Rights to the code go to the SlugSat Year 4 team 
 * to use/modify as desired
 */

//Main file to show case hamming code

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define HAMMING_TEST 1
#define EDAC_TEST 1 
#define NUM_TESTS 10
#define U16T(x, y) (x | (y << 8))

#include "edac.h"
#include "hamming.h"

static int pg_test_num;
static int sg_test_num;
static int sd_test_num;
void par_gen_test (uint8_t *data, uint8_t *exp);
void syn_gen_test (uint16_t *data, uint8_t *exp);
void syn_dec_test (uint8_t *syn, uint8_t *exp);

static int ec_test_num;
static int dc_test_num;
void ecnode_test (uint8_t *raw, uint16_t *exp);
void decode_test (uint16_t *enc, uint8_t *corr);


/*
 *
 */
void
par_gen_test (uint8_t *data, uint8_t *exp)
{
	pg_test_num += 1;
	uint8_t my_val = parity_generator(data);
	if (my_val == *exp) { printf("PAR_GEN test %d: SUCCESS!\n", pg_test_num); }
	else { printf("PAR_GEN test %d: FAILED!\nTest: parity_generator(b%d%d%d%d%d%d%d%d)", pg_test_num,
	              EIG(*data), SEV(*data), SIX(*data), FIV(*data), FOU(*data), THR(*data), TWO(*data), ONE(*data));
		   printf("                 Expected Result: b%d%d%d%d%d%d%d%d    Your Result: b%d%d%d%d%d%d%d%d\n", 
		          EIG(*exp), SEV(*exp), SIX(*exp), FIV(*exp), FOU(*exp), THR(*exp), TWO(*exp), ONE(*exp), 
				  EIG(my_val), SEV(my_val), SIX(my_val), FIV(my_val), FOU(my_val), THR(my_val), TWO(my_val), ONE(my_val));}
}

/*
 *
 */
void
syn_gen_test (uint16_t *data, uint8_t *exp)
{	
	sg_test_num += 1;
	uint8_t my_val = syndrome_generator(data);
	if (my_val == *exp) { printf("SYN_GEN test %d: SUCCESS!\n", sg_test_num); }
	else {
		uint8_t top = (*data) >> 8;
		uint8_t bot = (*data) & 0xFF;
		printf("SYN_GEN test %d: FAILED!\nTest: syndrome_generator(b)%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n", sg_test_num,
		       EIG(top), SEV(top), SIX(top), FIV(top), FOU(top), THR(top), TWO(top), ONE(top), 
			   EIG(bot), SEV(bot), SIX(bot), FIV(bot), FOU(bot), THR(bot), TWO(bot), ONE(bot));
		printf("                  Expected Result: b%d%d%d%d    Actual Result: b%d%d%d%d\n",
		        FOU(*exp), THR(*exp), TWO(*exp), ONE(*exp),
		        FOU(my_val), THR(my_val), TWO(my_val), ONE(my_val));}
}

/*
 *
 */
void
syn_dec_test (uint8_t *syn, uint8_t *exp)
{
	sd_test_num += 1;
	uint8_t my_val = syndrome_decoder(syn);
	if (my_val == *exp) { printf("SYN_DEC test %d: SUCCESS!\n", sd_test_num); }
	else { printf("SYN_DEC test %d: FAILED!\nTest: syndrome_decoder(b%d%d%d%d%d%d%d%d)\n", sd_test_num,
		          EIG(*syn), SEV(*syn), SIX(*syn), FIV(*syn), FOU(*syn), THR(*syn), TWO(*syn), ONE(*syn));
		   printf("                  Expected Result: b%d%d%d%d    Actual Result: b%d%d%d%d\n",
		          FOU(*exp), THR(*exp), TWO(*exp), ONE(*exp),
		          FOU(my_val), THR(my_val), TWO(my_val), ONE(my_val));}
}


/*
 *
 */
void
encode_test (uint8_t *raw, uint16_t *exp) 
{
	ec_test_num += 1;
	uint16_t my_val = parity_encode(raw);
	if (my_val == *exp) { printf("PAR_ENC test %d: SUCCESS!\n", ec_test_num); }
	else {
		uint8_t etop = (*exp) >> 8;
		uint8_t ebot = (*exp) & 0xFF;
		uint8_t atop = my_val >> 8;
		uint8_t abot = my_val & 0xFF;
		printf("PAR_ENC test %d: FAILED!\nTest: parity_encode(b%d%d%d%d%d%d%d%d)\n", ec_test_num,
		        EIG(*raw), SEV(*raw), SIX(*raw), FIV(*raw), FOU(*raw), THR(*raw), TWO(*raw), ONE(*raw));
		printf("                  Expected Result: b%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n",
		          EIG(etop), SEV(etop), SIX(etop), FIV(etop), FOU(etop), THR(etop), TWO(etop), ONE(etop),
		          EIG(ebot), SEV(ebot), SIX(ebot), FIV(ebot), FOU(ebot), THR(ebot), TWO(ebot), ONE(ebot));
		printf("                  Actual Result: b%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n",
		          EIG(atop), SEV(atop), SIX(atop), FIV(atop), FOU(atop), THR(atop), TWO(atop), ONE(atop),
		          EIG(abot), SEV(abot), SIX(abot), FIV(abot), FOU(abot), THR(abot), TWO(abot), ONE(abot)); }
}


/*
 *
 */
void
decode_test (uint16_t *enc, uint8_t *corr)
{
	dc_test_num += 1;
	uint8_t my_val = parity_decode(enc);
	if (my_val == *corr) { printf("PAR_DEC test %d: SUCCESS!\n", dc_test_num); }
	else {
		uint8_t etop = (*enc) >> 8;
		uint8_t ebot = (*enc) & 0xFF;
		printf("PAR_DEC test %d: FAILED!\nTest: parity_decode(b%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d)\n",
		        dc_test_num,
		        EIG(etop), SEV(etop), SIX(etop), FIV(etop), FOU(etop), THR(etop), TWO(etop), ONE(etop),
		        EIG(ebot), SEV(ebot), SIX(ebot), FIV(ebot), FOU(ebot), THR(ebot), TWO(ebot), ONE(ebot));
		printf("                  Expected Result: b%d%d%d%d%d%d%d%d\n",
		          EIG(*corr), SEV(*corr), SIX(*corr), FIV(*corr), FOU(*corr), THR(*corr), TWO(*corr), ONE(*corr));
		printf("                  Actual Result: b%d%d%d%d%d%d%d%d\n",
		          EIG(my_val), SEV(my_val), SIX(my_val), FIV(my_val), FOU(my_val), THR(my_val), TWO(my_val), ONE(my_val)); }
}



int 
main (void) 
{
	puts("- - - - - - - - - - - - \n- - EDAC Test Harness- -\n- - - - - - - - - - - - ");	
	time_t t;
	srand(time(&t));

	#if (HAMMING_TEST)
	//parity_generator_testValue
	uint8_t pg_t[10] = {0x00, 0xFF, 0x0F, 0xF0, 0xAA, 0x55, 0xE7, 0x18, 0x81, 0x2C}; 	
	//parity_generator_expectedValue
	uint8_t pg_e[10] = {0x00, 0x03, 0x07, 0x04, 0x04, 0x07, 0x0D, 0x0E, 0x0F, 0x0B}; 

	//syndrome_generator_dataValue
	uint8_t sg_d[15] = {0x00, 0xFF, 0x0F, 0xF0, 0xAA, 0x55, 0xE7, 0x18, 0x81, 0x2C, 0x22, 0xDF, 0x07, 0xE0, 0x2A}; 
	//syndrome_generator_parityValue
	uint8_t sg_p[15] = {0x00, 0x03, 0x07, 0x04, 0x04, 0x07, 0x0D, 0x0E, 0x0F, 0x0B, 0x00, 0x03, 0x07, 0x04, 0x04}; 
	//syndrome_generator_testValue
	uint16_t sg_t[15] = {U16T(sg_d[0], sg_p[0]), U16T(sg_d[1], sg_p[1]),
	                     U16T(sg_d[2], sg_p[2]), U16T(sg_d[3], sg_p[3]),
						 U16T(sg_d[4], sg_p[4]), U16T(sg_d[5], sg_p[5]),
						 U16T(sg_d[6], sg_p[6]), U16T(sg_d[7], sg_p[7]),
						 U16T(sg_d[8], sg_p[8]), U16T(sg_d[9], sg_p[9]),
						 U16T(sg_d[10], sg_p[10]), U16T(sg_d[11], sg_p[11]),
						 U16T(sg_d[12], sg_p[12]), U16T(sg_d[13], sg_p[13]),
						 U16T(sg_d[14], sg_p[14])}; 
	//syndrome_generator_expectedValue
	uint8_t sg_e[15] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0A, 0x07, 0x09, 0x0C}; 

	//syndrome_decoder_testValue
	uint8_t sd_t[8] = {0x03, 0x05, 0x06, 0x07, 0x09, 0x0A, 0x0B, 0x0C};
	//syndrome_decoder_expetedValue
	uint8_t sd_e[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};


	//===============================
	puts("\n--------parity_generator() Tests--------");

	for (int y = 0; y < 10; y++) {
		par_gen_test(&(pg_t[y]), &(pg_e[y]));
	}
	
	puts(" ");
	for (int i = 0; i < NUM_TESTS; i++) {
		uint8_t rd = (uint8_t) rand() % 255;
		printf("[PAR_GEN rand %d]: parity_generator(b%d%d%d%d%d%d%d%d)\n", i + 1,
								EIG(rd), SEV(rd), SIX(rd), FIV(rd), FOU(rd), THR(rd), TWO(rd), ONE(rd));
		uint8_t rr = parity_generator(&rd);
		printf("                  Generated parity bits = b%d%d%d%d\n", FOU(rr), THR(rr),TWO(rr), ONE(rr));
	}

	//=============================== 
	puts("\n--------syndrome_generator() Tests--------");

	for (int y = 0; y < 15; y++) {
		syn_gen_test(&(sg_t[y]), &(sg_e[y]));
	}

	puts(" ");
	for (int i = 0; i < NUM_TESTS; i++) {
		uint8_t rd = (uint8_t) rand() % 255;
		uint8_t rp = (uint8_t) rand() % 15;
		uint16_t rc = rd | (rp << 8);
		printf("[SYN_GEN rand %d]: syndrome_generator([p]:b%d%d%d%d [d]:b%d%d%d%d%d%d%d%d)\n", i + 1,
								FOU(rp), THR(rp), TWO(rp), ONE(rp),
								EIG(rd), SEV(rd), SIX(rd), FIV(rd), FOU(rd), THR(rd), TWO(rd), ONE(rd));
		uint8_t rs = syndrome_generator(&rc);
		printf("                  Generated syndrome bits = b%d%d%d%d\n", FOU(rs), THR(rs),TWO(rs), ONE(rs));
	}

	//===============================
	puts("\n--------syndrome_decoder() Tests--------");

	for (int q = 0; q < 8; q++) {
		syn_dec_test(&(sd_t[q]), &(sd_e[q]));
	}
	#endif

	#if (EDAC_TEST)	
	//rawValues
	uint8_t pe_r[10] = {0x00, 0xFF, 0x0F, 0xF0, 0xAA, 0x55, 0xE7, 0x18, 0x81, 0x2C};
	//parityValues
	uint8_t pe_p[10] = {0x00, 0x03, 0x07, 0x04, 0x04, 0x07, 0x0D, 0x0E, 0x0F, 0x0B};
	//encodedValues
	uint16_t pe_e[10] = {U16T(pe_r[0], pe_p[0]), U16T(pe_r[1], pe_p[1]),
	                     U16T(pe_r[2], pe_p[2]), U16T(pe_r[3], pe_p[3]),
						 U16T(pe_r[4], pe_p[4]), U16T(pe_r[5], pe_p[5]),
						 U16T(pe_r[6], pe_p[6]), U16T(pe_r[7], pe_p[7]),
						 U16T(pe_r[8], pe_p[8]), U16T(pe_r[9], pe_p[9])};

	//===============================
	puts("\n--------parity_encode() Tests--------");

	for (int h = 0; h < 10; h++) {
		encode_test(&(pe_r[h]), &(pe_e[h]));
	}

	//===============================
	puts("\n--------parity_decode() Tests--------");

	for (int h = 0; h < 10; h++) {
		decode_test(&(pe_e[h]), &(pe_r[h]));
	}
	
	#endif

    return 0;
}
