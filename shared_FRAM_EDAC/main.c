//Main file to show case hamming code

#include <stdio.h>
#include <stdint.h>

#define HAMMING_TEST 0
#define EDAC_TEST 1 

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
	puts("========================\n====EDAC Test Harness===\n========================");

	puts("\n>>parity_generator() Tests:");
	puts("\n[test 1]: parity_generator(b00000000)\n  Expected Result: b00000000");
	uint8_t pg_t1 = 0x00;
	if (parity_generator(&pg_t1) == 0) { puts("  SUCCESS!"); }
	else { puts("    FAILED!"); }

	puts("[test 2]: parity_generator(b11111111)\n    Expected Result: b00000011");
	uint8_t pg_t2 = 0xFF;
	if (parity_generator(&pg_t2) == 0x03) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }

	puts("[test 3]: parity_generator(b00001111)\n    Expected Result: b00000111");
	uint8_t pg_t3 = 0x0F;
	if (parity_generator(&pg_t3) == 0x07) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }
	
	puts("[test 4]: parity_generator(b11110000)\n    Expected Result: b00000100");
	uint8_t pg_t4 = 0xF0;
	if (parity_generator(&pg_t4) == 0x04) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }

	puts("[test 5]: parity_generator(b10101010)\n    Expected Result: b00000100");
	uint8_t pg_t5 = 0xAA;
	if (parity_generator(&pg_t5) == 0x04) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }
	
	puts("[test 6]: parity_generator(b01010101)\n    Expected Result: b00000111");
	uint8_t pg_t6 = 0x55;
	if (parity_generator(&pg_t6) == 0x07) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }
	
	puts("[test 7]: parity_generator(b11100111)\n    Expected Result: b00001101");
	uint8_t pg_t7 = 0xE7;  
	if (parity_generator(&pg_t7) == 0x0D) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }
	
	puts("[test 8]: parity_generator(b00011000)\n    Expected Result: b00001110");
	uint8_t pg_t8 = 0x18;
	if (parity_generator(&pg_t8) == 0x0E) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }
	
	puts("[test 9]: parity_generator(b100000001)\n    Expected Result: b00001111");
	uint8_t pg_t9 = 0x81;
	if (parity_generator(&pg_t9) == 0x0F) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }
	
	puts("[test 10]: parity_generator(b00101100)\n    Expected Result: b00001011");
	uint8_t pg_t10 = 0x2C;
	if (parity_generator(&pg_t10) == 0x0B) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }

	//===============================

	puts("\n>>syndrome_generator() Tests:");
	puts("\n[test 1]: syndrome_generator()\n  Expected Result: ");
	uint16_t sg_t1 = 0x0000;
	if (syndrome_generator(&sg_t1) == 0) { puts("  SUCCESS!"); }
	else { puts("    FAILED!"); }

	puts("[test 2]: syndrome_generator()\n    Expected Result: ");
	uint16_t sg_t2 = 0x0000;
	if (syndrome_generator(&sg_t2) == 0) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }

	puts("[test 3]: syndrome_generator()\n    Expected Result: ");
	uint16_t sg_t3 = 0x0000;
	if (syndrome_generator(&sg_t3) == 0) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); 
	
	puts("[test 4]: syndrome_generator()\n    Expected Result: ");
	uint16_t sg_t4 = 0x0000;
	if (syndrome_generator(&sg_t4) == 0) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }

	puts("[test 5]: syndrome_generator()\n    Expected Result: ");
	uint16_t sg_t5 = 0x0000;
	if (syndrome_generator(&sg_t5) == 0) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }
	
	puts("[test 6]: syndrome_generator()\n    Expected Result: ");
	uint16_t sg_t6 = 0x0000;
	if (syndrome_generator(&sg_t6) == 0) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }
	
	puts("[test 7]: syndrome_generator()\n    Expected Result: ");
	uint16_t sg_t7 = 0x0000;  
	if (syndrome_generator(&sg_t7) == 0) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }
	
	puts("[test 8]: syndrome_generator()\n    Expected Result: ");
	uint16_t sg_t8 = 0x0000;
	if (syndrome_generator(&sg_t8) == 0) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }
	
	puts("[test 9]: syndrome_generator()\n    Expected Result: ");
	uint16_t sg_t9 = 0x0000;
	if (syndrome_generator(&sg_t9) == 0) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }
	
	puts("[test 10]: syndrome_generator()\n    Expected Result: ");
	uint16_t sg_t10 = 0x0000;
	if (syndrome_generator(&sg_t10) == 0) { puts("    SUCCESS!"); }
	else { puts("    FAILED!"); }
	#endif


	#if (HAMMING_TEST)

	#endif

  return 0;
}
