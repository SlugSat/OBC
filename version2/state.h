#ifndef STATE_H
#define STATE_H

#include <stdint.h>

typedef enum {
	P_Core = 0, S_Core = 1, Reboot = 2, Sleep = 3, Dead = 4	
} States;

struct cores{
	States state;
};



void run_A(struct cores *A, struct cores *B, struct cores *C);
void run_B(void);
void run_C(void);

#endif /*STATE_H*/