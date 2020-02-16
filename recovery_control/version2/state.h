#ifndef STATE_H
#define STATE_H

#include <stdint.h>

typedef enum {
	P_Core = 0, S_Core = 1, Reboot = 2, Sleep = 3, Killed = 4	
} States;

typedef enum{
    Dead = 0, Alive = 1
}Power_status;

/*Struct to hold each cores information*/
struct cores{
	States state;
    Power_status power;
	int error;
};



void run_A(struct cores *A, struct cores *B, struct cores *C, int trigger);
void run_B(struct cores *A, struct cores *B, struct cores *C, int trigger);
void run_C(struct cores *A, struct cores *B, struct cores *C, int trigger);

#endif /*STATE_H*/