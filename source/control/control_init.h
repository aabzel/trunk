#ifndef CONTROL_INIT_H
#define CONTROL_INIT_H

#include "std_includes.h"

#ifndef HAS_CONTROL
#error "+HAS_CONTROL"
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
#endif /* */

#ifdef HAS_RELAY
#include "relay.h"
#define RELAY_INIT {.init_function=relay_mcal_init, .name="Relay",},
#else
#define RELAY_INIT
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
#endif /*HAS_PWM_DAC*/

#ifdef HAS_SCRIPT
#include "script.h"
#define SCRIPT_INIT {.init_function = script_mcal_init, .name = "script",},
#else
#define SCRIPT_INIT
#endif /*HAS_SCRIPT*/

//    LED_INIT      in MCAL INIT


// order matter
#define CONTROL_INIT    \
    LED_INIT            \
    USB_TO_I2S_INIT     \
    RELAY_INIT          \
    RTOS_INIT           \
    FREE_RTOS_INIT      \
    ZEPHYR_RTOS_INIT    \
    PWM_DAC_INIT        \
    PID_INIT            \
    MBR_INIT            \
    SCRIPT_INIT


//bool control_init(void);

#endif /* CONTROL_INIT_H */
