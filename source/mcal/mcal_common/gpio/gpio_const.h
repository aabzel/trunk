#ifndef GPIO_GENERAL_CONST_H
#define GPIO_GENERAL_CONST_H

#include <stdint.h>

#include "gpio_dep.h"

#ifdef HAS_GPIO_CUSTOM
#include "gpio_custom_const.h"
#endif

#define PIN_NAME_LEN 15
#define CONNECTOR_NAME_LEN 20
#define GPIO_TRANSITION_PROCESS_TIMEOUT_MS 300
#define GPIO_POLL_PERIOD_US 2000000

typedef enum {
/*GPIO_PULL_DOWN Was in conflict with Zephyr constants*/
    GPIO__PULL_DOWN = 1,
    GPIO__PULL_UP = 2,
    GPIO__PULL_AIR = 3,
    GPIO__PULL_BOTH = 4,

    GPIO__PULL_UNDEF = 5,
}GpioPullMode_t;

typedef enum  {
    GPIO_DIR_UNDEF = 0,
    GPIO_DIR_OUT = 1,
    GPIO_DIR_OUT_PUSH_PULL = 2,
    GPIO_DIR_OUT_OPEN_DRAIN =3,
    GPIO_DIR_INOUT = 4,
    GPIO_DIR_NONE = 5,
    GPIO_DIR_INOUT_OPEN_DRAIN = 6,
    GPIO_DIR_IN = 7,
} GpioDir_t;

typedef enum {
    GPIO_API_MODE_GPIO = 1,
    GPIO_API_MODE_ALT1 = 2,
    GPIO_API_MODE_ALT2 = 3,
    GPIO_API_MODE_HW_PWM = 4,
    GPIO_API_MODE_INPUT = 5,
    GPIO_API_MODE_OUTPUT = 6,
    GPIO_API_MODE_ANALOG = 7,
    GPIO_API_MODE_I2C = 8,
    GPIO_API_MODE_INPUT_EXINT = 9,
    GPIO_API_MODE_INPUT_EXINT_FAILLING = 10,
    GPIO_API_MODE_INPUT_EXINT_RISING = 11,

    GPIO_API_MODE_UNDEF = 0,
} GpioApiMode_t;

typedef enum {
    GPIO_DRIVE_SELECT_2MA = 2,
    GPIO_DRIVE_SELECT_4MA = 4,
    GPIO_DRIVE_SELECT_8MA = 8,
    GPIO_DRIVE_SELECT_UNDEF = 0,
} GpioDriveSelect_t;


/* Constants for GPIO logic levels*/
typedef enum {
    GPIO_LVL_LOW = 0, /*0 Volts*/
    GPIO_LVL_HI = 1, /*3.3 Volts*/

    GPIO_LVL_UNDEF = 2,
} GpioLogicLevel_t;

typedef enum  {
    GPIO_CORE_MUX_APP=0,
    GPIO_CORE_MUX_NET=1,
    GPIO_CORE_MUX_UNDEF=2,
} GpioCoreMux_t;

//GPIOx_CFGR
typedef enum {
    GPIO_FUN_INPUT=0,
    GPIO_FUN_OUT=1,
    GPIO_FUN_MULTIPLEXED=2,
    GPIO_FUN_ANALOG=3,

    GPIO_FUN_UNDEF=4,
}GpioPinFunction_t;

typedef enum {
    GPIO_SPEED_LOW_SPEED = 0,
    GPIO_SPEED_MEDIUM_SPEED = 1,
    GPIO_SPEED_FAST_SPEED = 2,
    GPIO_SPEED_HIGH_SPEED = 3,
    GPIO_SPEED_UNDEF = 4,
} GpioSpeed_t;

typedef struct  {
    GpioPullMode_t pull;
    GpioDir_t dir;
    GpioLogicLevel_t logic_level;
    GpioApiMode_t mode;
}GpioState_t;


#endif /* GPIO_GENERAL_CONST_H */
