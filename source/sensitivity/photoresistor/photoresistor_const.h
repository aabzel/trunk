
#ifndef PHOTORESISTOR_CONST_H
#define PHOTORESISTOR_CONST_H

#include "time_mcal.h"

#define PHOTORESISTOR_POLL_PERIOD_US SEC_2_USEC(10)

typedef enum {
	VOL_DIV_GND=1,
	VOL_DIV_VCC=2,

	VOL_DIV_UNDEF=0,
} VdPosition_t;

#endif /* PHOTORESISTOR_CONST_H */



