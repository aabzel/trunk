#ifndef CLOCK_CUCUSTOM_CONST_H
#define CLOCK_CUCUSTOM_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "clock_custom_dep.h"



typedef enum{
	SRCSEL_NO = 0,
	SRCSEL_FIRC = 1,
	SRCSEL_SIRC = 2,
	SRCSEL_FXOSC = 3,
	SRCSEL_SXOSC = 4,
	SRCSEL_PLL = 5,
	SRCSEL_RES1 = 6,
	SRCSEL_RES2 = 7,
	SRCSEL_UNDEF = 8,
}ClockSourceSelection_t;


#ifdef __cplusplus
}
#endif

#endif // CLOCK_CUCUSTOM_CONST_H
