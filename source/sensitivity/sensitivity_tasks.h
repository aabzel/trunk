#ifndef SENSITIVITY_TASKS_H
#define SENSITIVITY_TASKS_H

#ifdef HAS_ADC_IF_PROC
#include "adc_if_mcal.h"
#define ADC_IF_TASK {.name="ADC_IF", .period_us=ADC_IF_POLL_PERIOD_US, .limiter.function=adc_if_proc,},
#else
#define ADC_IF_TASK
#endif

#ifdef HAS_HEALTH_MONITOR_PROC
#include "health_monitor.h"
#define HEALTH_MONITOR_TASK {.name="HEAL_MON", .period_us=HEAL_MON_PERIOD_US, .limiter.function=health_monotor_proc,},
#else
#define HEALTH_MONITOR_TASK
#endif /**/

#ifdef HAS_BUTTON_PROC
#include "button_drv.h"
#define BUTTON_TASK { .name="BUTTON", .period_us=BUTTON_POLL_PERIOD_US, .limiter.function=button_proc,},
#else
#define BUTTON_TASK
#endif

#ifdef HAS_CROSS_DETECT_PROC
#include "cross_detect_drv.h"
#define CROSS_DETECT_TASK {.name="CROSS_DETECT", .period_us=CROSS_DETECT_POLL_PERIOD_US, .limiter.function=cross_detect_proc,},
#else
#define CROSS_DETECT_TASK
#endif

#ifdef HAS_DISTANCE_PROC
#include "distance_drv.h"
#define DISTANCE_TASK {.name="DISTANCE", .period_us=DISTANCE_POLL_PERIOD_US, .limiter.function=distance_proc,},
#else
#define DISTANCE_TASK
#endif /* */

#ifdef HAS_GNSS_PROC
#define GNSS_TASK
#else
#define GNSS_TASK
#endif /*HAS_GNSS_PROC*/

#ifdef HAS_LOAD_DETECT_PROC
#include "load_detect_drv.h"
#define LOAD_DETECT_TASK {.name="LOAD_DETECT", .period_us=LOAD_DETECT_PERIOD_US, .limiter.function=load_detect_proc,},
#else
#define LOAD_DETECT_TASK
#endif

#ifdef HAS_TIME_PROC
#include "time_mcal.h"
#define TIME_TASK {.name="TIME", .period_us=TIME_POLL_PERIOD_US, .limiter.function=time_proc,},
#else
#define TIME_TASK
#endif

#ifdef HAS_PDM_PROC
#include "pdm_drv.h"
#define PDM_TASK {.name="PDM", .period_us=PDM_POLL_PERIOD_US, .limiter.function=pdm_proc,},
#else
#define PDM_TASK
#endif

#ifdef HAS_PHOTORESISTOR_PROC
#include "photoresistor.h"
#define PHOTORESISTOR_TASK {.name="PHOTORESISTOR", .period_us=PHOTORESISTOR_POLL_PERIOD_US, .limiter.function=photoresistor_proc,},
#else
#define PHOTORESISTOR_TASK
#endif

#ifdef HAS_SOFTWARE_TIMER_PROC
#include "software_timer.h"
#define SOFTWARE_TIMER_TASK {.name="SW_TIMER", .period_us=SW_TIMER_PERIOD_US, .limiter.function=sw_timer_poll,},
#else
#define SOFTWARE_TIMER_TASK
#endif

#define TASK_SENSITIVITY    \
    ADC_IF_TASK             \
    BUTTON_TASK             \
    HEALTH_MONITOR_TASK     \
    CROSS_DETECT_TASK       \
    DISTANCE_TASK           \
    GNSS_TASK               \
    LOAD_DETECT_TASK        \
    PDM_TASK                \
    PHOTORESISTOR_TASK      \
    SOFTWARE_TIMER_TASK     \
    TIME_TASK


#endif /* SENSITIVITY_TASKS_H */
