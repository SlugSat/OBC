#include "util.h"
#include <time.h>
void delay (int numofsec){
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * numofsec; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) 
        ; 	
}

