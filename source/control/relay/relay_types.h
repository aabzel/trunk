#ifndef RELAY_TYPES_H
#define RELAY_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "relay_constants.h"
#include "gpio_types.h"


#define RELAY_COMMON_VARIABLE    \
    uint8_t num;                 \
    Pad_t pad_set;               \
    Pad_t pad_get;               \
    bool valid;                  \
    RelayMode_t mode;            \
    uint8_t  duty;               \
    char* name;                  \
    GpioLogicLevel_t active;

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

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*RELAY_TYPES_H*/
