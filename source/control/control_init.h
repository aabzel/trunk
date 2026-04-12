#ifndef CONTROL_INIT_H
#define CONTROL_INIT_H

#include "std_includes.h"

#ifndef HAS_CONTROL
#error "+HAS_CONTROL"
#endif

#ifdef HAS_AUTO_EXIT
#include "auto_exit.h"
#define AUTO_EXIT_INIT { .init_function=auto_exit_mcal_init, .name="AutoExit",},
#else
#define AUTO_EXIT_INIT
#endif

#ifdef HAS_GPIO_DAC
#include "gpio_dac_mcal.h"
#define GPIO_DAC_INIT {.init_function=gpio_dac_mcal_init, .name="GpioDac",},
#else
#define GPIO_DAC_INIT
#endif


#ifdef HAS_BUZZER
#include "buzzer.h"
#define BUZZER_INIT {.init_function=buzzer_mcal_init, .name="Buzzer",},
#else
#define BUZZER_INIT
#endif

#ifdef HAS_RTOS
#include "rtos_drv.h"
#define RTOS_INIT { .init_function=rtos_task_mcal_init, .name="RTOS",},
#else
#define RTOS_INIT
#endif

#ifdef HAS_FREE_RTOS
#include "rtos_custom_drv.h"
#define FREE_RTOS_INIT { .init_function=free_rtos_init, .name="FreeRtos",},
#else
#define FREE_RTOS_INIT
#endif

#ifdef HAS_MBR
#include "mbr_drv.h"

#ifdef HAS_LOG
#define MBR_INIT_NAME .name = "MBR",
#else
#define MBR_INIT_NAME
#endif

#define MBR_INIT {.init_function = mbr_init, MBR_INIT_NAME },
#else
#define MBR_INIT
#endif

#ifdef HAS_PID
#include "pid.h"
#define PID_INIT { .init_function=pid_mcal_init, .name="Pid",},
#else
#define PID_INIT
#endif

#ifdef HAS_LED
#include "led_init.h"
#else
#define LED_INIT
#endif

#ifdef HAS_RELAY
#include "relay.h"
#define RELAY_INIT {.init_function=relay_mcal_init, .name="Relay",},
#else
#define RELAY_INIT
#endif


#ifdef HAS_BOOT
#include "boot_driver.h"

#ifdef HAS_LOG
#define BOOT_INIT_NAME .name = "Boot",
#else
#define BOOT_INIT_NAME
#endif

#define BOOT_INIT {.init_function=boot_mcal_init, BOOT_INIT_NAME},
#else
#define BOOT_INIT
#endif


#ifdef HAS_USB_TO_I2S
#include "usb_to_i2s_drv.h"
#define USB_TO_I2S_INIT { .init_function=usb_to_i2s_init, .name="UsbI2s",},
#else
#define USB_TO_I2S_INIT
#endif

#ifdef HAS_ZEPHYR
#include "zephyr_rtos_drv.h"
#define ZEPHYR_RTOS_INIT { .init_function=zephyr_rtos_mcal_init, .name="ZephyrRtos",},
#else
#define ZEPHYR_RTOS_INIT
#endif

#ifdef HAS_PWM_DAC
#include "pwm_dac.h"
#define PWM_DAC_INIT {.init_function=pwm_dac_mcal_init, .name="PwmDac",},
#else
#define PWM_DAC_INIT
#endif


#ifdef HAS_SCRIPT
#include "script.h"
#define SCRIPT_INIT {.init_function = script_mcal_init, .name = "script",},
#else
#define SCRIPT_INIT
#endif



#ifdef HAS_POSTPONE_FUN
#include "postpone_fun.h"
#define POSTPONE_FUN_INIT {.init_function = postpone_fun_mcal_init, .name = "postponeFun",},
#else
#define POSTPONE_FUN_INIT
#endif


#ifdef HAS_SCHEDULER
#include "scheduler_mcal.h"

#ifdef HAS_LOG
#define SCHEDULER_INIT_NAME .name = "Scheduler",
#else
#define SCHEDULER_INIT_NAME
#endif

#define SCHEDULER_INIT {.init_function = scheduler_mcal_init, SCHEDULER_INIT_NAME},
#else
#define SCHEDULER_INIT
#endif


/* order matter */
#define CONTROL_INIT    \
    BOOT_INIT           \
    SCHEDULER_INIT      \
    LED_INIT            \
    USB_TO_I2S_INIT     \
    RELAY_INIT          \
    RTOS_INIT           \
    FREE_RTOS_INIT      \
    ZEPHYR_RTOS_INIT    \
    PWM_DAC_INIT        \
    PID_INIT            \
    BUZZER_INIT         \
    GPIO_DAC_INIT       \
    GPIO_PWM_INIT       \
    MBR_INIT            \
    POSTPONE_FUN_INIT   \
    AUTO_EXIT_INIT      \
    SCRIPT_INIT

#endif /* CONTROL_INIT_H */
