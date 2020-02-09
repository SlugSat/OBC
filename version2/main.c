#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "state.h"
#include "util.h"

	int single_core = 0;
	int dual_core = 0;
	int tri_core = 0;

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
	int iteration =0;
	
	A.error = 0;
	B.error = 0;
	C.error = 0;
	
	while(1){
		
		
		printf("Iteration: %d\n", iteration);
		/*
		A.power = event_gent();
		B.power = event_gent();
		C.power = event_gent();
		*/
		A.power = 1;
		B.power = 1;
		C.power = 1;
		
		printf("A Power: %d\n", A.power);
		printf("B Power: %d\n", B.power);
		printf("C Power: %d\n", C.power);
		puts(" ");
		
		if((A.power & B.power & C.power) == 1){
			tri_core = 1;
			dual_core = 0;
			single_core = 0;
		}
		else if((A.power ^ B.power ^ C.power) == 0){
			tri_core = 0;
			dual_core = 1;
			single_core =0;
		}
		else{
			tri_core = 0;
			dual_core = 0;
			single_core = 1;
		}
		run_A(&A,&B, &C, trigger);
		run_B(&A,&B, &C, trigger);
		run_C(&A,&B, &C, trigger);
		
		printf("A State: %d\n", A.state);
		printf("B State: %d\n", B.state);
		printf("C State: %d\n", C.state);
		puts(" ");
		iteration++;
		
		delay(100);
	}

}

