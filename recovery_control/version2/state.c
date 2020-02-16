#include "state.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
#define upper 1
#define lower 0

void run_A(struct cores *A, struct cores *B, struct cores *C, int trigger){
	puts("run_A");
	
	//if cubesat started
	if(A->power == 0){
		//kill the satellite upon launch
		A->state = Killed;
	}
	else{
		switch(A->state){
        case P_Core:
			if(A->power == 0 && B->power == 0 && C->power == 0){
				//Ultimate kill
				A->state = Killed;
				B->state = Killed;
				C->state = Killed;
			}
			/*Primary core has died
			  Sleep and Secondary core needs to reset regardless of trigger
			*/
			else if(A->power == 0){
				if(B->power && C->power){
					B->state = S_Core;
					C->state = P_Core;
				}
				else if(B->power && !(C->power)){
					B->state = P_Core;
					C->state = Killed;
				}
				else if(!(B->power) && C->power){
					C->state = P_Core;
					B->state = Killed;
				}
			}
			else{
				puts("A has power");
				if(trigger){
					A->state = S_Core;
				}
			}
            break;
        case S_Core:
			if(trigger){
				A->state = Reboot;
			}
            break;
		//Reboot is test stage
		//In stm32 this will go to sleep state automatically
		//after reboot
        case Reboot:
			puts("Rebooting Core A");
			//delay(100);
			A->error++;
			printf("A.error: %d\n", A->error);
			if(A->error == 4) A->state = Killed;
			else A->state = Sleep;
            break;
        case Sleep:
			if(trigger){
				A->state = P_Core;
			}
            break;
        case Killed:
			puts("A core is killed");
			A->power = 0;
            break;
		}
	}
    
}

void run_B(struct cores *A, struct cores *B, struct cores *C, int trigger){
		puts("run_B");
		if(B->power == 0){
			B->state = Killed;
		}
		else{
			switch(B->state){
				case P_Core:
					if(A->power == 0 && B->power == 0 && C->power == 0){
						//Ultimate kill
						A->state = Killed;
						B->state = Killed;
						C->state = Killed;
					}
					/*Primary core has died
					  Sleep and Secondary core needs to reset regardless of trigger
					*/
					else if(B->power == 0){
						puts("B is turned off");
						if(A->power && C->power){
							A->state = S_Core;
							C->state = P_Core;
						}
						else if(A->power && !(C->power)){
							A->state = P_Core;
							C->state = Killed;
						}
						else if(!(A->power) && C->power){
							C->state = P_Core;
							A->state = Killed;
						}
					}
					else{
						puts("B has power");
						if(trigger){
							B->state = S_Core;
						}
					}
					break;
				case S_Core:
					if(trigger){
						//B->state = Sleep;
						B->state = Reboot;
					}
					break;
				case Reboot:
					puts("Rebooting Core B");
					//delay(100);
					B->error++;
					printf("B.error: %d\n", B->error);
					if(B->error == 4) B->state = Killed;
					else B->state = Sleep;
					break;
				case Sleep:
					if(trigger){
						B->state = P_Core;
					}
					break;
				case Killed:
					puts("B core is killed");
					B->power = 0;
					break;
			}	
		}
}

void run_C(struct cores *A, struct cores *B, struct cores *C, int trigger){
	puts("run_C");
	if(C->power == 0){
		C->state = Killed;
	}
	else{
		switch(C->state){
        case P_Core:
            if(A->power == 0 && B->power == 0 && C->power == 0){
				//Ultimate kill
				A->state = Killed;
				B->state = Killed;
				C->state = Killed;
			}
			/*Primary core has died
			  Sleep and Secondary core needs to reset regardless of trigger
			*/
			else if(C->power == 0){
				if(A->power && B->power){
					A->state = S_Core;
					B->state = P_Core;
				}
				else if(A->power && !(B->power)){
					A->state = P_Core;
					B->state = Killed;
				}
				else if(!(A->power) && B->power){
					B->state = P_Core;
					A->state = Killed;
				}
			}
			/*Primary core is still alive*/
			else{
				puts("C has power");
				if(trigger){
					C->state = S_Core;
				}
			}
            break;
        case S_Core:
			if(trigger){
				//C->state = Sleep;
				C->state = Reboot;
			}
            break;
        case Reboot:
			puts("Rebooting Core C");
			//delay(100);
			C->error++;
			printf("C.error: %d\n", C->error);
			if(C->error == 4) C->state = Killed;
			else C->state = Sleep;
            break;
        case Sleep:
			if(trigger){
				C->state = P_Core;
			}
            break;
        case Killed:
			puts("C core is killed");
			B->power = 0;
            break;
		}
	}
	    
}