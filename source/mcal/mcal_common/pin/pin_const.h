#ifndef PIN_GENERAL_CONST_H
#define PIN_GENERAL_CONST_H

#include <stdint.h>

#include "pin_dep.h"

#ifdef HAS_PIN_CUSTOM
#include "pin_custom_const.h"
#endif

#define PIN_NAME_LEN 15
#define CONNECTOR_NAME_LEN 20
#define PIN_TRANSITION_PROCESS_TIMEOUT_MS 300
#define PIN_POLL_PERIOD_US 2000000

typedef enum {
/*PIN_PULL_DOWN Was in conflict with Zephyr constants*/
    PIN__PULL_DOWN = 1,
    PIN__PULL_UP = 2,
    PIN__PULL_AIR = 3,
    PIN__PULL_BOTH = 4,

    PIN__PULL_UNDEF = 5,
}PinPullMode_t;

typedef enum  {
    PIN_DIR_UNDEF = 0,
    PIN_DIR_OUT = 1,
    PIN_DIR_OUT_PUSH_PULL = 2,
    PIN_DIR_OUT_OPEN_DRAIN =3,
    PIN_DIR_INOUT = 4,
    PIN_DIR_NONE = 5,
    PIN_DIR_INOUT_OPEN_DRAIN = 6,
    PIN_DIR_IN = 7,
} PinDir_t;

typedef enum {
    PIN_API_MODE_PIN = 1,
    PIN_API_MODE_ALT1 = 2,
    PIN_API_MODE_ALT2 = 3,
    PIN_API_MODE_HW_PWM = 4,
    PIN_API_MODE_INPUT = 5,
    PIN_API_MODE_OUTPUT = 6,
    PIN_API_MODE_ANALOG = 7,
    PIN_API_MODE_I2C = 8,
    PIN_API_MODE_INPUT_EXINT = 9,
    PIN_API_MODE_INPUT_EXINT_FAILLING = 10,
    PIN_API_MODE_INPUT_EXINT_RISING = 11,

    PIN_API_MODE_UNDEF = 0,
} PinApiMode_t;

typedef enum {
    PIN_DRIVE_SELECT_2MA = 2,
    PIN_DRIVE_SELECT_4MA = 4,
    PIN_DRIVE_SELECT_8MA = 8,
    PIN_DRIVE_SELECT_UNDEF = 0,
} PinDriveSelect_t;


/* Constants for PIN logic levels*/
typedef enum {
    PIN_LVL_LOW = 0, /*0 Volts*/
    PIN_LVL_HI = 1, /*3.3 Volts*/

    PIN_LVL_UNDEF = 2,
} PinLogicLevel_t;

typedef enum  {
    PIN_CORE_MUX_APP=0,
    PIN_CORE_MUX_NET=1,
    PIN_CORE_MUX_UNDEF=2,
} PinCoreMux_t;

//PINx_CFGR
typedef enum {
    PIN_FUN_INPUT=0,
    PIN_FUN_OUT=1,
    PIN_FUN_MULTIPLEXED=2,
    PIN_FUN_ANALOG=3,

    PIN_FUN_UNDEF=4,
}PinPinFunction_t;

typedef enum {
    PIN_SPEED_LOW_SPEED = 0,
    PIN_SPEED_MEDIUM_SPEED = 1,
    PIN_SPEED_FAST_SPEED = 2,
    PIN_SPEED_HIGH_SPEED = 3,
    PIN_SPEED_UNDEF = 4,
} PinSpeed_t;

typedef struct  {
    PinPullMode_t pull;
    PinDir_t dir;
    PinLogicLevel_t logic_level;
    PinApiMode_t mode;
}PinState_t;


#endif /* PIN_GENERAL_CONST_H */
