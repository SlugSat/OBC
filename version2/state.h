#ifndef STATE_H
#define STATE_H

#include <stdint.h>

typedef enum {
	P_Core = 0, S_Core = 1, Reboot = 2, Sleep = 3, Killed = 4	
} States;

typedef enum{
    Dead = 0, Alive = 1
}Power_status;

struct cores{
	States state;
    Power_status power;
};



void run_A(struct cores *A, struct cores *B, struct cores *C);
void run_B(void);
void run_C(void);

#endif /*STATE_H*/