
#ifndef LOAD_DETECT_TYPES_H
#define LOAD_DETECT_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "gpio_types.h"
//#include "gpio_const.h"
#include "load_detect_const.h"

#define LOAD_DETECT_PIN_COMMON_VARIABLES                                                                               \
    uint8_t num;                                                                                                       \
    bool valid;                                                                                                        \
    Pad_t pad;                                                                                                         \
    uint8_t pin_num;

typedef struct {
    LOAD_DETECT_PIN_COMMON_VARIABLES
    char* name;
} LoadDetectPinConfig_t;

typedef struct {
    LOAD_DETECT_PIN_COMMON_VARIABLES

    bool on_off;
    GpioLogicLevel_t llevel_at_pullair;
    GpioLogicLevel_t llevel_at_pulldown;
    GpioLogicLevel_t llevel_at_pullup;
    LoadDetectOut_t state;
    LoadDetectOut_t prev_state;
} LoadDetectPinInfo_t;

#define LOAD_DETECT_COMMON_VARIABLES                                                                                   \
    uint8_t num;                                                                                                       \
    bool valid;                                                                                                        \
    GpioClass_t gpio_class;

typedef struct {
    LOAD_DETECT_COMMON_VARIABLES
    char* name;
} LoadDetectConfig_t;

typedef struct {
    LOAD_DETECT_COMMON_VARIABLES
    GpioPullMode_t state;
    bool init_done;
    bool on_off;
    uint32_t spin_cnt;
    uint32_t err_cnt;
    uint32_t pause_ms;
    // uint32_t up_time;
    uint32_t time_start;
} LoadDetectHandle_t;

#endif /* LOAD_DETECT_TYPES_H  */
