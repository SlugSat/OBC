#include "util.h"
#include <time.h>
#include <stdlib.h>

#define MAX 1
#define MIN 0

void delay (int numofsec){
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * numofsec; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) 
        ; 	
}

int event_gent(void){
	return rand() % (MAX + 1 - MIN) + MIN;
}


