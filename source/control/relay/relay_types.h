#ifndef RELAY_TYPES_H
#define RELAY_TYPES_H

#include "relay_constants.h"
#include "gpio_types.h"
#include "control_const.h"
#include "pwm_types.h"

#define RELAY_COMMON_VARIABLE               \
    PWM_SIGNAL_VARIABLES                    \
    ControlMode_t ctrl_mode;                \
    GpioLogicLevel_t active;                \
    Pad_t pad_get;                          \
    Pad_t pad_set;                          \
    RelayMode_t mode;                       \
    bool valid;                             \
    char* con_name;                         \
    char* name;                             \
    uint8_t num;                            \
    uint8_t pwm_num;

typedef struct  {
    RELAY_COMMON_VARIABLE
} RelayConfig_t;

typedef struct  {
    RELAY_COMMON_VARIABLE
    RelayMode_t prev_mode;
    uint32_t on_time_ms;  /* for Blink mode*/
    uint32_t period_ms;   /* for PWM/Blink mode*/
    uint32_t cur_time_ms; /* for Blink mode*/
    uint32_t duration_ms; /* for Blink mode*/
    int32_t rest_duration_ms; /* for Blink mode*/
    uint32_t phase_ms;    /* for PWM mode*/
    uint32_t err_cnt;
    bool real_state; /*true - on; false - off*/
    bool init;
    bool on;
} RelayHandle_t;


#endif /*RELAY_TYPES_H*/
