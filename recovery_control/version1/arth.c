#include "arth.h"
#include <stdlib.h>

#define max 5
#define min 0

int* instruction(){
    static int r[1];
    r[0] = ( rand() % (max + 1 - min)) + min;
    r[1] = ( rand() % (max + 1 - min)) + min;
    
    return r;
}