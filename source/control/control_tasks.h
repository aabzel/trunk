#ifndef CONTROL_TASKS_H
#define CONTROL_TASKS_H

#ifdef HAS_LED
#include "led_tasks.h"
#else
#define	LEDS_TASKS
#endif /**/

#ifdef HAS_GPIO_PWM_PROC
#define	GPIO_PWM_TASK {.name="GPIO_PWM", .period_us=GPIO_PWM_POLL_PERIOD_US, .limiter.function=gpio_pwm_proc,},
#else
#define	GPIO_PWM_TASK
#endif /**/

#ifdef HAS_DISPLAY_PROC
#include "display_drv.h"
#define DISPLAY_TASK {.name="DISPLAY", .period_us=DISPLAY_PERIOD_US, .limiter.function=display_proc,},
#else
#define DISPLAY_TASK
#endif /**/

#ifdef HAS_HW_DAC_PROC
#define	HW_DAC_TASK {.name="HW_DAC", .period_us=HW_DAC_POLL_PERIOD_US, .limiter.function=dac_proc,},
#else
#define	HW_DAC_TASK
#endif /**/

#ifdef HAS_GENERIC_PROC
#include "boot_driver.h"
#define BOOT_TASK {.name="BOOT", .period_us=BOOT_PERIOD_US, .limiter.function=boot_proc,},
#else /*HAS_GENERIC*/
#define BOOT_TASK
#endif /*HAS_GENERIC*/

#ifdef HAS_MBR_PROC
#include "mbr_drv.h"
#define MBR_TASK {.name="MBR", .period_us=MBR_POLL_PERIOD_US, .limiter.function=mbr_proc,},
#else
#define MBR_TASK
#endif /**/

#ifdef HAS_PID_PROC
#include "pid.h"
#define PID_TASK {.name="PID", .period_us=PID_POLL_PERIOD_US, .limiter.function=pid_proc,},
#else
#define PID_TASK
#endif /**/

#ifdef HAS_RELAY_PROC
#include "relay.h"
#define	RELAY_TASK {.name="RELAY", .period_us=RELAY_PERIOD_US, .limiter.function=relay_proc,},
#else
#define	RELAY_TASK
#endif /**/


#ifdef HAS_SCRIPT_PROC
#include "script.h"
#define	SCRIPT_TASK {.name="script", .period_us=SCRIPT_POLL_PERIOD_US, .limiter.function=script_proc,},
#else
#define	SCRIPT_TASK
#endif /**/


#ifdef HAS_BOARD_PROC
#include "board_api.h"

#ifdef HAS_LOG
#define BOARD_TASK_NAME .name = "Board",
#else
#define BOARD_TASK_NAME
#endif

#define BOARD_TASK { .period_us = BOARD_POLL_PERIOD_US, .limiter.function = board_proc, BOARD_TASK_NAME},
#else
#define BOARD_TASK
#endif /**/


#define CONTROL_TASKS       \
    BOOT_TASK               \
    DISPLAY_TASK            \
    GPIO_PWM_TASK           \
    BOARD_TASK              \
    HW_DAC_TASK             \
    PID_TASK                \
    LEDS_TASKS              \
    MBR_TASK                \
    RELAY_TASK              \
    SCRIPT_TASK



#endif /* CONTROL_TASKS_H */
