#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "state.h"

int main(void){
	
	/* Objective of main is to run with all the 3 cores connected*/
	struct cores A, B, C;
	A.state = P_Core;
	B.state = S_Core;
	C.state = Sleep;
	
	
	printf("A_Core: %d, B_Core: %d, C_Core: %d\n", A.state, 
													B.state,
													C.state);
													
	run_A(&A,&B, &C);
}
