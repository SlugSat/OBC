#include "state.h"
#include "arth.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define upper 1
#define lower 0


States run_state(int trigger, uint32_t tres_core, 
                uint32_t dos_core, uint32_t uno_core, 
                States state){
                    
    printf("State is: %d\n", state);
    while(1){
        switch(state) {
            case P_Core:
                puts("State is P_Core");
                if(trigger) {
                    if(dos_core || tres_core) state = S_Core;
                    else state = Reboot;
                }
                break;
            case S_Core:
                puts("State is S_Core");
                if(trigger){
                    if(dos_core || tres_core ) state = Reboot;
                } 
                break;
            case Reboot:
                puts("State is Reboot");
                //Add a random chance of going 
                //to sleep or dead
                if(trigger) {
                    if(tres_core){
                        state = Sleep;
                    }
                    else{
                        state = P_Core;
                    }
                break;
            case Sleep:
                //Can only be in this state when 3 cores are active
                puts("State is Sleep");
                if(trigger){
                    if(tres_core) state = P_Core;
                } 
                break;
            case Dead:
                puts("Dead lmao");
                exit(1);
                break;
        }
        break;
    }
    return state;
    }
}

int gen_event(){
    int num = (rand()%(upper - lower + 1)) + lower;
    return num;
}
