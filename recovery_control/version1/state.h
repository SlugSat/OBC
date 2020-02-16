#ifndef STATE_H
#define STATE_H

#include <stdint.h>

typedef enum state {
    P_Core = 0, S_Core = 1, Reboot = 2, Sleep = 3, Dead = 4
}States;
    
enum signals {A_Sig = 0, B_Sig = 1, C_Sig = 2};

States run_state(int trigger, uint32_t tres_core, 
                uint32_t dos_core, uint32_t uno_core,
                int A_Change, int B_Change, int C_Change,
                States state);
                
int gen_event();
#endif
