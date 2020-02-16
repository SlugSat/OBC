#include <stdlib.h>
#include <stdio.h>
#include "state.h"
#include "arth.h"
#include <time.h>
#include <stdint.h>

#define max 5
#define min 0

//imagine if this is core A code
void delay(int number_of_seconds){
    int milli = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli);
}


int main(void) {
    States state, state_next;
    state = P_Core;
    
    int trigger = 0;
    int A_Sig, B_Sig, C_Sig = 0;
    int prev_A_Sig, prev_B_Sig, prev_C_Sig = 0;
    int A_Change, B_Change, C_Change = 0;
    uint32_t tres_core, dos_core, uno_core = 0;

    
    /*TODO:
       Check if the state is in primary. If that certain core is dead, 
	   then other core must partake in
       primary state.
    */
    
    
    
        
    
    while(1){
        
        //This would be done through polling in STM32
        //Randomly generated core health
        A_Sig = gen_event();
        B_Sig = gen_event();
        C_Sig = gen_event();
        printf("A_Sig: %d, B_Sig: %d, C_Sig: %d\n", A_Sig, B_Sig, C_Sig);
		/*In reality, change signals will not output if the core
		  is dead
		*/
        A_Change = prev_A_Sig ^ A_Sig ? 1 : 0;
        B_Change = prev_B_Sig ^ B_Sig ? 1 : 0;
        C_Change = prev_C_Sig ^ C_Sig ? 1 : 0;
    
        //The only wy for this to be 1 --> 1, 1, 1
        if((A_Sig & B_Sig & C_Sig) == 1){
            puts("3 cores are alive");
            tres_core = 1;
            dos_core = 0;
            uno_core = 0;
        }
        
        //Only will be 1 --> 0 and two 1's
        else if((A_Sig ^ B_Sig ^ C_Sig) == 0){
            puts("2 cores are alive");
            tres_core = 0;
            dos_core = 1;
            uno_core = 0;
        }
        else{
            puts("1 cores are alive");
            tres_core = 0;
            dos_core = 0;
            uno_core = 1;
        }
        
        int* instr = instruction();
        int result = instr[0] + instr[1];
        int temp1 = ( rand() % (max + 1 - min)) + min;
        int temp2 = ( rand() % (max + 1 - min)) + min;
        int comp = temp1 + temp2;
        
        printf("result: %d, comp: %d\n", result, comp);
        
        if(result ^ comp) trigger = 1;
        //Find a way to compare changes in states
        
        //printf("Before entering run_state, trigger: %d\n", trigger);
        state_next = run_state(trigger, tres_core,
                        dos_core, uno_core, 
                        A_Change, B_Change, C_Change,
                        state);
        delay(5000);
        state = state_next;
        prev_A_Sig = A_Sig;
        prev_B_Sig = B_Sig;
        prev_C_Sig = C_Sig;
    }
        
    
}
