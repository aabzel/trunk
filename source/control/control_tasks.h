#ifndef CONTROL_TASKS_H
#define CONTROL_TASKS_H

#ifdef HAS_LED
#include "led_tasks.h"
#else
#define	LEDS_TASKS
#endif

#ifdef HAS_GPIO_PWM_PROC
#define	GPIO_PWM_TASK {.name="GPIO_PWM", .period_us=GPIO_PWM_POLL_PERIOD_US, .limiter.function=gpio_pwm_proc,},
#else
#define	GPIO_PWM_TASK
#endif

#ifdef HAS_DISPLAY_PROC
#include "display_drv.h"
#define DISPLAY_TASK {.name="DISPLAY", .period_us=DISPLAY_PERIOD_US, .limiter.function=display_proc,},
#else
#define DISPLAY_TASK
#endif


#ifdef HAS_AUTO_EXIT_PROC
#include "auto_exit.h"
#define AUTO_EXIT_TASK {.name = "AutoExit", .period_us = AUTO_EXIT_PERIOD_US, .limiter.function = auto_exit_proc,},
#else
#define AUTO_EXIT_TASK
#endif


#ifdef HAS_GENERIC_PROC
#include "generic.h"
#define GENERIC_TASK {.name = "Generic", .period_us = GENERIC_PERIOD_US, .limiter.function = generic_proc,},
#else
#define GENERIC_TASK
#endif

#ifdef HAS_HW_DAC_PROC
#define	HW_DAC_TASK {.name="HW_DAC", .period_us=HW_DAC_POLL_PERIOD_US, .limiter.function=dac_proc,},
#else
#define	HW_DAC_TASK
#endif

#ifdef HAS_BOOT_PROC
#include "boot_driver.h"
#define BOOT_TASK {.name="BOOT", .period_us=BOOT_PERIOD_US, .limiter.function=boot_proc,},
#else /*HAS_GENERIC*/
#define BOOT_TASK
#endif

#ifdef HAS_MBR_PROC
#include "mbr_drv.h"

#ifdef HAS_LOG
#define MBR_TASK_NAME .name = "MBR",
#else
#define MBR_TASK_NAME
#endif

#define MBR_TASK {  .period_us=MBR_POLL_PERIOD_US, .limiter.function=mbr_proc, MBR_TASK_NAME},
#else
#define MBR_TASK
#endif

#ifdef HAS_PID_PROC
#include "pid.h"
#define PID_TASK {.name="PID", .period_us=PID_POLL_PERIOD_US, .limiter.function=pid_proc,},
#else
#define PID_TASK
#endif

#ifdef HAS_RELAY_PROC
#include "relay.h"
#define	RELAY_TASK {.name="RELAY", .period_us=RELAY_PERIOD_US, .limiter.function=relay_proc,},
#else
#define	RELAY_TASK
#endif

#ifdef HAS_BUZZER_PROC
#include "buzzer.h"
#define	BUZZER_TASK {.name="Buzzer", .period_us=BUZZER_PERIOD_US, .limiter.function=buzzer_proc,},
#else
#define	BUZZER_TASK
#endif

#ifdef HAS_SCRIPT_PROC
#include "script.h"
#define	SCRIPT_TASK {.name="script", .period_us=SCRIPT_POLL_PERIOD_US, .limiter.function=script_proc,},
#else
#define	SCRIPT_TASK
#endif

#ifdef HAS_GPIO_DAC_PROC
#include "gpio_dac_mcal.h"
#define GPIO_DAC_TASK {.name="GpioDac", .period_us=GPIO_DAC_POLL_PERIOD_US, .limiter.function = gpio_dac_proc,},
#else
#define GPIO_DAC_TASK
#endif


#ifdef HAS_POSTPONE_FUN_PROC
#include "postpone_fun.h"
#define POSTPONE_FUN_TASK {.name="POSTPONE_FUN", .period_us=POSTPONE_FUN_POLL_PERIOD_US, .limiter.function=postpone_fun_proc,},
#else
#define POSTPONE_FUN_TASK
#endif




#ifdef HAS_BOARD_PROC
#include "board_config.h"

#ifdef HAS_LOG
#define BOARD_TASK_NAME .name = "Board",
#else
#define BOARD_TASK_NAME
#endif

#define BOARD_TASK { .period_us = BOARD_POLL_PERIOD_US, .limiter.function = board_proc, BOARD_TASK_NAME},
#else
#define BOARD_TASK
#endif

#ifdef HAS_BOOTLOADER
#include "bootloader.h"
#define BOOTLOADER_TASK {.name="BOOTLOADER", .period_us=BOOTLOADER_PERIOD_US, .limiter.function=bootloader_proc,},
#else /**/
#define BOOTLOADER_TASK
#endif /**/


#define CONTROL_TASKS       \
    AUTO_EXIT_TASK            \
    BOOT_TASK               \
    BUZZER_TASK             \
    BOARD_TASK              \
    BOOTLOADER_TASK         \
    DISPLAY_TASK            \
    GPIO_DAC_TASK           \
    GPIO_PWM_TASK           \
    GENERIC_TASK            \
    HW_DAC_TASK             \
    MBR_TASK                \
    LEDS_TASKS              \
    PID_TASK                \
    RELAY_TASK              \
    POSTPONE_FUN_TASK       \
    SCRIPT_TASK



#endif /* CONTROL_TASKS_H */
