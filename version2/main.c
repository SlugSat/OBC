#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "state.h"
#include "util.h"


int main(void){
	
	/* Objective of main is to run with all the 3 cores connected*/
	struct cores A, B, C;
	A.state = P_Core;
	B.state = S_Core;
	C.state = Sleep;
	/*Polled every time through interrupt*/
	A.power = Alive;
    B.power = Alive;
    C.power = Alive;
	/* trigger is the flag for misscalculation*/
	int trigger = 1;
	
	while(1){
		printf("A status: %d\n", A.state);
		printf("B status: %d\n", B.state);
		printf("C status: %d\n", C.state);
		puts(" ");
		run_A(&A,&B, &C, trigger);
		run_B(&A,&B, &C, trigger);
		run_C(&A,&B, &C, trigger);
		delay(100);
	}

}

