#include "state.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
#define upper 1
#define lower 0

void run_A(struct cores *A, struct cores *B, struct cores *C, int trigger){
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
				if(trigger){
					A->state = S_Core;
				}
			}
            break;
        case S_Core:
			if(trigger){
				A->state = Sleep;
			}
            break;
        case Reboot:
			puts("Rebooting Core A");
			//delay(100);
			A->state = Sleep;
            break;
        case Sleep:
			if(trigger){
				A->state = P_Core;
			}
            break;
        case Killed:
			A->power = 0;
            break;
    }
}

void run_B(struct cores *A, struct cores *B, struct cores *C, int trigger){
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
				if(trigger){
					B->state = S_Core;
				}
			}
            break;
        case S_Core:
			if(trigger){
				B->state = Sleep;
			}
            break;
        case Reboot:
			puts("Rebooting Core B");
			//delay(100);
			B->state = Sleep;
            break;
        case Sleep:
			if(trigger){
				B->state = P_Core;
			}
            break;
        case Killed:
            break;
    }
}

void run_C(struct cores *A, struct cores *B, struct cores *C, int trigger){
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
				if(trigger){
					C->state = S_Core;
				}
			}
            break;
        case S_Core:
			if(trigger){
				C->state = Sleep;
			}
            break;
        case Reboot:
			puts("Rebooting Core C");
			//delay(100);
			C->state = Sleep;
            break;
        case Sleep:
			if(trigger){
				C->state = P_Core;
			}
            break;
        case Killed:
            break;
    }
}