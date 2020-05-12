#include "DateConversion.h"

#include <stdio.h>

uint64_t double_to_unsigned(double input)
{
	union Date {
		double date;
		uint64_t udate;
	};
	union Date D;
	D.date = input;
	return D.udate;
}

void double_to_bytes(double input, uint8_t *retArr)
{	
	union Date {
		double date;
		uint64_t udate;
		uint8_t bdate[8];
	};
	union Date D;
	D.date = input;
	memcpy(retArr, D.bdate, 8);
}

double bytes_to_double(uint8_t input[8])
{
	union Date {
		double date;
		uint8_t bdate[8];
	};
	union Date D;
	memcpy(D.bdate, input, 8);
	return D.date;
}


// Convert from a float to a 4 byte value
void float_to_bytes(float input, uint8_t *retArr)
{
	union Date {
		float date;
		uint64_t udate;
		uint8_t bdate[4];
	};
	union Date D;
	D.date = input;
	memcpy(retArr, D.bdate, 4);
}

// Convert from 4 bytes into a float
float bytes_to_float(uint8_t *input)
{
	union Location {
		float date;
		uint8_t bdate[4];
	};
	union Location D;
	memcpy(D.bdate, input, 4);
	return D.date;
}


double JD_2_year(double JD)
{
	JD = JD - 2451545 + 0.5;
	int year = 2000;
	int days_per_year = 365;
	while(1) {
		if(((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0))) {
			days_per_year = 366; // Leap year
		}
		else {
			days_per_year = 365;
		}
		if (JD < days_per_year)
		{
			break;
		}
		
		year++;
		JD -= days_per_year;
	}
	
	return (double)year;
}

// The input to this function needs to be the output from the JD_2_year function
unsigned JD_2_days(double JD)
{
	double remainder = JD - (unsigned) JD;
	return (remainder * 356) + 1;
}


unsigned JD_2_H_M_S(double JD)
{
	double remainder = JD - (unsigned) JD;
	
	const unsigned long long base = 1000000; 
	const unsigned long long halfbase = 500000; 
	const unsigned secsPerDay = 86400; 

	// "rounded" remainder after adding half a day 
	unsigned long long rndRemainder = (unsigned long long)(remainder * base + halfbase) % base; 

	rndRemainder *= secsPerDay; 
	
	// "rounded" number of seconds 
	unsigned long long nsecs = (rndRemainder + halfbase) / base; 

	//hours: secs/3600 % 24, min: secs/60 % 60, secs secs % 60 
	unsigned rtn = (nsecs/3600 % 24) * 10000 + (nsecs/60 % 60) * 100 + (nsecs % 60); 
	
	// The value returned will be 6 decimal digits in the form HHMMSS
	return rtn; 
}




