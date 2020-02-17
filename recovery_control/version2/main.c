
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "state.h"
#include "util.h"

#define BUFSIZE 60000
	int single_core = 0;
	int dual_core = 0;
	int tri_core = 0;

int main(void){
	
	/*Types to use for sim*/
	FILE * fp;
	char str[BUFSIZE];
	
	fp = fopen("/afs/cats.ucsc.edu/users/z/mykang/OBC_Test/OBC/recovery_control/version2/sim.txt", "r");
	
	if(fp == NULL){
		puts("failed to get file");
		exit(EXIT_FAILURE);
	}
	struct cores A, B, C;
	A.state = P_Core;
	B.state = S_Core;
	C.state = Sleep;
	
	A.power = Dead;
    B.power = Dead;
    C.power = Dead;
	int iteration =0;
	int trigger = 1;
    while( fgets (str, BUFSIZE, fp)!=NULL ) {
      /* writing content to stdout */
	  //puts("print");
		printf("str[0] %c\n", str[0]);
		printf("str[1] %c\n", str[1]);
		printf("str[2] %c\n", str[2]);
	  
		if(str[0] == 'A' || str[1] == 'A' || str[2] == 'A') A.power = Alive;
		if(str[0] == 'B' || str[1] == 'B' || str[2] == 'B') B.power = Alive;
		if(str[0] == 'C' || str[1] == 'C' || str[2] == 'C') C.power = Alive;
	  
		printf("Iteration: %d\n", iteration);
		++iteration;
		trigger = 1;
		run_A(&A,&B, &C, trigger);
		//printf("State: %d\n", A.state);
        printf("Error Count: %d\n", A.error);
        puts(" ");
		delay(1000);
	  
   }
   fclose(fp);
	//puts("closed");
	
	#if 0
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
        ++iteration;
		trigger = 1;
		run_A(&A,&B, &C, trigger);
		//printf("State: %d\n", A.state);
        printf("Error Count: %d\n", A.error);
        puts(" ");
		delay(1000);
	}
	#endif
	#if 0
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
		
		delay(1000);
	}
	#endif

}

