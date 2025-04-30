#ifndef SOFTWARE_TIMER_TYPES_H
#define SOFTWARE_TIMER_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "software_timer_const.h"

#ifndef HAS_SOFTWARE_TIMER
#error "+HAS_SOFTWARE_TIMER"
#endif

typedef bool (*SwHandler_t)(void);

#define SW_TIMER_COMMON_VARIABLES  \
    volatile bool on_off;          \
	uint32_t num;         \
	bool valid;           \
	bool spare;           \
    uint32_t period_ms;   \
    uint32_t phase_ms;    \
    SwTimerCntDir_t dir;  \
    SwTimerMode_t mode;   \
    SwHandler_t handler;

typedef struct{
	volatile uint32_t cnt;//
	volatile uint32_t err_cnt;
    volatile uint32_t handler_cnt;
    volatile bool isr;
    SW_TIMER_COMMON_VARIABLES
}SoftwareTimer_t;

typedef struct{
	char name[100];
	SW_TIMER_COMMON_VARIABLES
}SoftwareTimerConfig_t;


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*SOFTWARE_TIMER_TYPES_H*/
