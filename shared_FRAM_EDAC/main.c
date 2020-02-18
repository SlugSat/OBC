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
	puts("========================\n====EDAC Test Harness===\n========================");
	puts("\nparity_generator() Tests:");
	puts("[test 1]: parity_generator(00000000)\n  Expected Result: 00000000");
	uint8_t pg_t1 = 0b00000000;
	if (parity_generator(&pg_t1) == 0) { puts("  SUCCESS!"); }
	else { puts("  FAILED!"); }



  return 0;
}
