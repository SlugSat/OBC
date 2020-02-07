#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "state.h"

int main(void){
	
	
	A_Core.state = P_Core;
	B_Core.state = S_Core;
	C_Core.state = Sleep;
	
	printf("A_Core: %d, B_Core: %d, C_Core: %d\n", A_Core.state, 
													B_Core.state,
													C_Core.state);
}
