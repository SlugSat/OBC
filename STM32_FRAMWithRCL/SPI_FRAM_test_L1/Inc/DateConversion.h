#ifndef DATE_CONV
#define DATE_CONV

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Convert from the bytes to double 
double bytes_to_double(uint8_t input[8]);

// Convert from a double to an unsigned 64 bit value
uint64_t double_to_unsigned(double input);

// Convert from a double to a packet of size 8
void double_to_bytes(double input, uint8_t *retArr);

// Convert from a float to a 4 byte value
void float_to_bytes(float input, uint8_t *retArr);

// Convert from 4 bytes into a float
float bytes_to_float(uint8_t *input);

// Convert Julian date to a human readable date
double JD_2_year(double JD);

// Convert to the number of days in a year
unsigned JD_2_days(double JD);

// Convert Julian date to hours, minutes and seconds. The output is in the form of 6 decimal digits: HHMMSS
unsigned JD_2_H_M_S(double JD);


#endif // DATE_CONV
