#include "state.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define upper 1
#define lower 0

void run_A(struct cores *A, struct cores *B, struct cores *C){
	printf("A status: %d\n", A->state);
    printf("B status: %d\n", B->state);
    printf("C status: %d\n", C->state);
    
    switch(A->state){
        case P_Core:
            puts("P_Core");
            break;
        case S_Core:
            break;
        case Reboot:
            break;
        case Sleep:
            break;
        case Killed:
            break;
        
    }
	
	
}

void run_B(){
	
}

void run_C(){
	
}