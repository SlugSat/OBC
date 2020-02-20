//Main file to show case hamming code

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define HAMMING_TEST 0
#define EDAC_TEST 1 
#define NUM_TESTS 10

#if (HAMMING_TEST)
#include "edac.h"
#endif

#if (EDAC_TEST)
#include "hamming.h"
#endif



int 
main (void) 
{
	#if (EDAC_TEST)
	time_t t;
	srand(time(&t));

	puts("========================\n====EDAC Test Harness===\n========================");
	
	uint8_t pg_t; //parity_generator_testValue
	uint8_t pg_e; //parity_generator_expectedValue
	uint8_t pg_a; //parity_generator_actualValue

	uint16_t sg_t; //syndrome_generator_testValue
	uint8_t sg_d; //syndrome_generator_dataValue
	uint8_t sg_p; //syndrome_generator_parityValue
	uint8_t sg_e; //syndrome_generator_expectedValue
	uint8_t sg_a; //syndrome_generator_actualValue
	
	//===============================

	puts("\n>>>>\n>>>>parity_generator() Tests\n<<<<");

	pg_t = 0x00; pg_e = 0x00; 
	pg_a = parity_generator(&pg_t);
	if (pg_a == pg_e) { puts("[PAR_GEN test 1]: SUCCESS!"); }
	else { puts("[PAR_GEN test 1]: FAILED!\nTest: parity_generator(b00000000)");
		   printf("    Expected Result: b00000000    Actual Result: b%d%d%d%d%d%d%d%d\n", 
		          EIG(pg_a), SEV(pg_a), SIX(pg_a), FIV(pg_a), FOU(pg_a), THR(pg_a), TWO(pg_a), ONE(pg_a));}

	pg_t = 0xFF; pg_e = 0x03; 
	pg_a = parity_generator(&pg_t);
	if (pg_a == pg_e) { puts("[PAR_GEN test 2]: SUCCESS!"); }
	else { puts("[PAR_GEN test 2]: FAILE!\nTest: parity_generator(b11111111)");
		   printf("    Expected Result: b00000011    Actual Result: b%d%d%d%d%d%d%d%d\n", 
		          EIG(pg_a), SEV(pg_a), SIX(pg_a), FIV(pg_a), FOU(pg_a), THR(pg_a), TWO(pg_a), ONE(pg_a));}

	pg_t = 0x0F; pg_e = 0x07; 
	pg_a = parity_generator(&pg_t);
	if (pg_a == pg_e) { puts("[PAR_GEN test 3]: SUCCESS!"); }
	else { puts("[PAR_GEN test 3]: FAILED!\nTest: parity_generator(b00001111)");
		   printf("    Expected Result: b00000111    Actual Result: b%d%d%d%d%d%d%d%d\n", 
		          EIG(pg_a), SEV(pg_a), SIX(pg_a), FIV(pg_a), FOU(pg_a), THR(pg_a), TWO(pg_a), ONE(pg_a));}

	pg_t = 0xF0; pg_e = 0x04; 
	pg_a = parity_generator(&pg_t);
	if (pg_a == pg_e) { puts("[PAR_GEN test 4]: SUCCESS!"); }
	else { puts("[PAR_GEN test 4]: FAILED!\nTest: parity_generator(b11110000)");
		   printf("    Expected Result: b00000100    Actual Result: b%d%d%d%d%d%d%d%d\n", 
		          EIG(pg_a), SEV(pg_a), SIX(pg_a), FIV(pg_a), FOU(pg_a), THR(pg_a), TWO(pg_a), ONE(pg_a));}

	pg_t = 0xAA; pg_e = 0x04; 
	pg_a = parity_generator(&pg_t);
	if (pg_a == pg_e) { puts("[PAR_GEN test 5]: SUCCESS!"); }
	else { puts("[PAR_GEN test 5]: FAILED!\nTest: parity_generator(b10101010)");
		   printf("    Expected Result: b00000100    Actual Result: b%d%d%d%d%d%d%d%d\n", 
		          EIG(pg_a), SEV(pg_a), SIX(pg_a), FIV(pg_a), FOU(pg_a), THR(pg_a), TWO(pg_a), ONE(pg_a));}

	pg_t = 0x55; pg_e = 0x07; 
	pg_a = parity_generator(&pg_t);
	if (pg_a == pg_e) { puts("[PAR_GEN test 6]: SUCCESS!"); }
	else { puts("[PAR_GEN test 6]: FAILED!\nTest: parity_generator(b01010101)");
		   printf("    Expected Result: b00000111    Actual Result: b%d%d%d%d%d%d%d%d\n", 
		          EIG(pg_a), SEV(pg_a), SIX(pg_a), FIV(pg_a), FOU(pg_a), THR(pg_a), TWO(pg_a), ONE(pg_a));}

	pg_t = 0xE7; pg_e = 0x0D; 
	pg_a = parity_generator(&pg_t);
	if (pg_a == pg_e) { puts("[PAR_GEN test 7]: SUCCESS!"); }
	else { puts("[PAR_GEN test 7]: FAILED!\nTest: parity_generator(b11100111)");
		   printf("    Expected Result: b00001101    Actual Result: b%d%d%d%d%d%d%d%d\n", 
		          EIG(pg_a), SEV(pg_a), SIX(pg_a), FIV(pg_a), FOU(pg_a), THR(pg_a), TWO(pg_a), ONE(pg_a));}

	pg_t = 0x18; pg_e = 0x0E; 
	pg_a = parity_generator(&pg_t);
	if (pg_a == pg_e) { puts("[PAR_GEN test 8]: SUCCESS!"); }
	else { puts("[PAR_GEN test 8]: FAILED!\nTest: parity_generator(b00011000)");
		   printf("    Expected Result: b00001110    Actual Result: b%d%d%d%d%d%d%d%d\n", 
		          EIG(pg_a), SEV(pg_a), SIX(pg_a), FIV(pg_a), FOU(pg_a), THR(pg_a), TWO(pg_a), ONE(pg_a));}

	pg_t = 0x81; pg_e = 0x0F; 
	pg_a = parity_generator(&pg_t);
	if (pg_a == pg_e) { puts("[PAR_GEN test 9]: SUCCESS!"); }
	else { puts("[PAR_GEN test 9]: FAILED!\nTest: parity_generator(b10000001)");
		   printf("    Expected Result: b00001111    Actual Result: b%d%d%d%d%d%d%d%d\n", 
		          EIG(pg_a), SEV(pg_a), SIX(pg_a), FIV(pg_a), FOU(pg_a), THR(pg_a), TWO(pg_a), ONE(pg_a));}

	pg_t = 0x2C; pg_e = 0x0B; 
	pg_a = parity_generator(&pg_t);
	if (pg_a == pg_e) { puts("[PAR_GEN test 10]: SUCCESS!"); }
	else { puts("[PAR_GEN test 10]: FAILED!\nTest: parity_generator(b00101100)");
		   printf("    Expected Result: b00001011    Actual Result: b%d%d%d%d%d%d%d%d\n", 
		          EIG(pg_a), SEV(pg_a), SIX(pg_a), FIV(pg_a), FOU(pg_a), THR(pg_a), TWO(pg_a), ONE(pg_a));}


	for (int i = 0; i < NUM_TESTS; i++) {
		uint8_t rd = (uint8_t) rand() % 255;
		printf("[PAR_GEN rand %d]: parity_generator(b%d%d%d%d%d%d%d%d)\n", i + 1,
								EIG(rd), SEV(rd), SIX(rd), FIV(rd), FOU(rd), THR(rd), TWO(rd), ONE(rd));
		uint8_t rr = parity_generator(&rd);
		printf("    Generated parity bits = b%d%d%d%d\n", FOU(rr), THR(rr),TWO(rr), ONE(rr));
	}

	//=============================== 
	puts("\n>>>>\n>>>>syndrome_generator() Tests\n<<<<");

	sg_d = 0x00; sg_p = 0x00; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[CORR_PAR_SYN_GEN test 1]: SUCCESS!"); }
	else { puts("[CORR_PAR_SYN_GEN test 1]: FAILED!\nTest: syndrome_generator(0x0000)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_a), THR(sg_a), TWO(sg_a), ONE(sg_a));}
	sg_d = 0x00; sg_p = 0x00; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[CORR_PAR_SYN_GEN test 1]: SUCCESS!"); }
	else { puts("[ERR_PAR_SYN_GEN test 1]: FAILED!\nTest: syndrome_generator(0x0000)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_a), THR(sg_a), TWO(sg_a), ONE(sg_a));}
	

	sg_d = 0xFF; sg_p = 0x03; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[CORR_PAR_SYN_GEN test 2]: SUCCESS!"); }
	else { puts("[CORR_PAR_SYN_GEN test 2]: FAILED!\nTest: syndrome_generator(0x03FF)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_d), THR(sg_d), TWO(sg_d), ONE(sg_d));}
	sg_d = 0x00; sg_p = 0x00; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[ERR_PAR_SYN_GEN test 2]: SUCCESS!"); }
	else { puts("[ERR_PAR_SYN_GEN test 2]: FAILED!\nTest: syndrome_generator(0x0000)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_a), THR(sg_a), TWO(sg_a), ONE(sg_a));}


	sg_d = 0x0F; sg_p = 0x07; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[CORR_PAR_SYN_GEN test 3]: SUCCESS!"); }
	else { puts("[CORR_PAR_SYN_GEN test 3]: FAILED!\nTest: syndrome_generator(0x070F)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_d), THR(sg_d), TWO(sg_d), ONE(sg_d));}
	sg_d = 0x00; sg_p = 0x00; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[ERR_PAR_SYN_GEN test 3]: SUCCESS!"); }
	else { puts("[ERR_PAR_SYN_GEN test 3]: FAILED!\nTest: syndrome_generator(0x0000)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_a), THR(sg_a), TWO(sg_a), ONE(sg_a));}


	sg_d = 0xF0; sg_p = 0x04; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[CORR_PAR_SYN_GEN test 4]: SUCCESS!"); }
	else { puts("[CORR_PAR_SYN_GEN test 4]: FAILED!\nTest: syndrome_generator(0x04F0)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_d), THR(sg_d), TWO(sg_d), ONE(sg_d));}
	sg_d = 0x00; sg_p = 0x00; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[ERR_PAR_SYN_GEN test 4]: SUCCESS!"); }
	else { puts("[ERR_PAR_SYN_GEN test 4]: FAILED!\nTest: syndrome_generator(0x0000)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_a), THR(sg_a), TWO(sg_a), ONE(sg_a));}
	
	
	sg_d = 0xAA; sg_p = 0x04; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[CORR_PAR_SYN_GEN test 5]: SUCCESS!"); }
	else { puts("[CORR_PAR_SYN_GEN test 5]: FAILED!\nTest: syndrome_generator(0x04AA)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_d), THR(sg_d), TWO(sg_d), ONE(sg_d));}
	sg_d = 0x00; sg_p = 0x00; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[ERR_PAR_SYN_GEN test 5]: SUCCESS!"); }
	else { puts("[ERR_PAR_SYN_GEN test 5]: FAILED!\nTest: syndrome_generator(0x0000)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_a), THR(sg_a), TWO(sg_a), ONE(sg_a));}
	
	
	sg_d = 0x55; sg_p = 0x07; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[CORR_PAR_SYN_GEN test 6]: SUCCESS!"); }
	else { puts("[CORR_PAR_SYN_GEN test 6]: FAILED!\nTest: syndrome_generator(0x0755)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_d), THR(sg_d), TWO(sg_d), ONE(sg_d));}
	sg_d = 0x00; sg_p = 0x00; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[ERR_PAR_SYN_GEN test 6]: SUCCESS!"); }
	else { puts("[ERR_PAR_SYN_GEN test 6]: FAILED!\nTest: syndrome_generator(0x0000)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_a), THR(sg_a), TWO(sg_a), ONE(sg_a));}
	
	
	sg_d = 0xE7; sg_p = 0x0D; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[CORR_PAR_SYN_GEN test 7]: SUCCESS!"); }
	else { puts("[CORR_PAR_SYN_GEN test 7]: FAILED!\nTest: syndrome_generator(0x0DE7)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_d), THR(sg_d), TWO(sg_d), ONE(sg_d));}
	sg_d = 0x00; sg_p = 0x00; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[ERR_PAR_SYN_GEN test 7]: SUCCESS!"); }
	else { puts("[ERR_PAR_SYN_GEN test 7]: FAILED!\nTest: syndrome_generator(0x0000)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_a), THR(sg_a), TWO(sg_a), ONE(sg_a));}


	sg_d = 0x18; sg_p = 0x0E; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[CORR_PAR_SYN_GEN test 8]: SUCCESS!"); }
	else { puts("[CORR_PAR_SYN_GEN test 8]: FAILED!\nTest: syndrome_generator(0x0E18)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_d), THR(sg_d), TWO(sg_d), ONE(sg_d));}	
	sg_d = 0x00; sg_p = 0x00; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[ERR_PAR_SYN_GEN test 8]: SUCCESS!"); }
	else { puts("[ERR_PAR_SYN_GEN test 8]: FAILED!\nTest: syndrome_generator(0x0000)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_a), THR(sg_a), TWO(sg_a), ONE(sg_a));}


	sg_d = 0x81; sg_p = 0x0F; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[CORR_PAR_SYN_GEN test 9]: SUCCESS!"); }
	else { puts("[CORR_PAR_SYN_GEN test 9]: FAILED!\nTest: syndrome_generator(0x0F81)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_d), THR(sg_d), TWO(sg_d), ONE(sg_d));}
	sg_d = 0x00; sg_p = 0x00; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[ERR_PAR_SYN_GEN test 9]: SUCCESS!"); }
	else { puts("[ERR_PAR_SYN_GEN test 9]: FAILED!\nTest: syndrome_generator(0x0000)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_a), THR(sg_a), TWO(sg_a), ONE(sg_a));}


	sg_d = 0x2C; sg_p = 0x0B; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[CORR_PAR_SYN_GEN test 10]: SUCCESS!"); }
	else { puts("[CORR_PAR_SYN_GEN test 10]: FAILED!\nTest: syndrome_generator(0x0B2C)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_d), THR(sg_d), TWO(sg_d), ONE(sg_d));}
	sg_d = 0x00; sg_p = 0x00; sg_t = sg_d | (sg_p << 8); sg_e = 0x00;
	sg_a = syndrome_generator(&sg_t);
	if (sg_a == sg_e) { puts("[ERR_PAR_SYN_GEN test 10]: SUCCESS!"); }
	else { puts("[ERR_PAR_SYN_GEN test 10]: FAILED!\nTest: syndrome_generator(0x0000)");
		   printf("    Expected Result: 0x00    Actual Result: b%d%d%d%d\n", FOU(sg_a), THR(sg_a), TWO(sg_a), ONE(sg_a));}
	//

	//

/*
	for (int i = 0; i < NUM_TESTS; i++) {
		uint8_t rd = (uint8_t) rand() % 255;
		uint8_t rp = (uint8_t) rand() % 15;
		uint16_t rc = rd | (rp << 8);
		printf("[SYN_GEN rand %d]: syndrome_generator([p]:b%d%d%d%d [d]:b%d%d%d%d%d%d%d%d)\n", i + 1,
								EIG(rp), SEV(rp), SIX(rp), FIV(rp), FOU(rp), THR(rp), TWO(rp), ONE(rp),
								EIG(rd), SEV(rd), SIX(rd), FIV(rd), FOU(rd), THR(rd), TWO(rd), ONE(rd));
		uint8_t rs = syndrome_generator(&rc);
		printf("    Generated syndrome bits = b%d%d%d%d\n", FOU(rs), THR(rs),TWO(rs), ONE(rs));
	}
*/
	//===============================
/*
	puts("\n>>>>\n>>>>syndrome_decoder() Tests\n<<<<");

	puts("\n[test 1]: syndrome_decoder(0x0000)\n  Expected Result: 0x0");
	uint16_t sg_t1 = (pg_t1) | (pg_r1 << 8);
	if (syndrome_generator(&sg_t1) == 0) { puts("  SUCCESS!"); }
	else { puts("    FAILED!"); }

	puts("[test 2]: syndrome_decoder(0x03FF)\n    Expected Result: 0x0");
	uint16_t sg_t2 = (pg_t2) | (pg_r2 << 8);
	if (syndrome_generator(&sg_t2) == 0) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }

	puts("[test 3]: syndrome_decoder(0x070F)\n    Expected Result: 0x0");
	uint16_t sg_t3 = (pg_t3) | (pg_r3 << 8);
	if (syndrome_generator(&sg_t3) == 0) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); } 
	
	puts("[test 4]: syndrome_decoder(0x04F0)\n    Expected Result: 0x0");
	uint16_t sg_t4 = (pg_t4) | (pg_r4 << 8);
	if (syndrome_generator(&sg_t4) == 0) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }

	puts("[test 5]: syndrome_decoder(0x04AA)\n    Expected Result: 0x0");
	uint16_t sg_t5 = (pg_t5) | (pg_r5 << 8);
	if (syndrome_generator(&sg_t5) == 0) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }
	
	puts("[test 6]: syndrome_decoder(0x0755)\n    Expected Result: 0x0");
	uint16_t sg_t6 = (pg_t6) | (pg_r6 << 8);
	if (syndrome_generator(&sg_t6) == 0) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }
	
	puts("[test 7]: syndrome_decoder(0x0DE7)\n    Expected Result: 0x0");
	uint16_t sg_t7 = (pg_t7) | (pg_r7 << 8);
	if (syndrome_generator(&sg_t7) == 0) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }
	
	puts("[test 8]: syndrome_decoder(0x0E18)\n    Expected Result: 0x0");
	uint16_t sg_t8 = (pg_t8) | (pg_r8 << 8);
	if (syndrome_generator(&sg_t8) == 0) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }
	
	puts("[test 9]: syndrome_decoder(0x0F81)\n    Expected Result: 0x0");
	uint16_t sg_t9 = (pg_t9) | (pg_r9 << 8);
	if (syndrome_generator(&sg_t9) == 0) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }
	
	puts("[test 10]: syndrome_decoder(0x0B2C)\n    Expected Result: 0x0");
	uint16_t sg_t10 = (pg_t10) | (pg_r10 << 8);
	if (syndrome_generator(&sg_t10) == 0) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }

	for (int i = 0; i < NUM_TESTS; i++) {
		uint8_t rd = (uint8_t) rand() % 255;
		uint8_t rp = (uint8_t) rand() % 15;
		uint16_t rc = rd | (rp << 8);
		printf("[rand %d]: parity_generator([parity]:b%d%d%d%d%d%d%d%d [data]:b%d%d%d%d%d%d%d%d)\n", i + 1,
								EIG(rp), SEV(rp), SIX(rp), FIV(rp), FOU(rp), THR(rp), TWO(rp), ONE(rp),
								EIG(rd), SEV(rd), SIX(rd), FIV(rd), FOU(rd), THR(rd), TWO(rd), ONE(rd));
		uint8_t rs = syndrome_generator(&rc);
		printf("    Generated syndrome bits = b%d%d%d%d\n", FOU(rs), THR(rs),TWO(rs), ONE(rs));
	}
*/

	#endif

	#if (HAMMING_TEST)

	#endif

  return 0;
}
