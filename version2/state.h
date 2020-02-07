#ifndef STATE_H
#define STATE_H

#include <stdint.h>

typedef enum {
	P_Core = 0, S_Core = 1, Reboot = 2, Sleep = 3, Dead = 4	
} States;

struct A_Core{
	States state;
} A_Core;

struct B_Core{
	States state;
} B_Core;

struct C_Core{
	States state;
}C_Core;

void run_A(void);
void run_B(void);
void run_C(void);

#endif /*STATE_H*/