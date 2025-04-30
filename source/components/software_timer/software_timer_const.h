#ifndef SOFTWARE_TIMER_CONST_H
#define SOFTWARE_TIMER_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "software_timer_dep.h"

#define SW_TIMER_PERIOD_US 1000

typedef enum{
	SW_TIMER_CNT_DIR_UP=1,
	SW_TIMER_CNT_DIR_DOWN=2,
	SW_TIMER_CNT_DIR_UNDEF=3,
}SwTimerCntDir_t;

typedef enum{
	SW_TIMER_MODE_SINGLE=0,
	SW_TIMER_MODE_CONTINUOUS=1,
	SW_TIMER_MODE_UNDEF=2,
}SwTimerMode_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*SOFTWARE_TIMER_CONST_H*/
