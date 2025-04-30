#ifndef LED_MONO_TYPES_H
#define LED_MONO_TYPES_H

#include "std_includes.h"
#include "led_mono_const.h"
#include "led_general_types.h"
#include "gpio_types.h"

#define LED_MONO_COMMON_VARIABLES    \
    Pad_t pad;                       \
    Color_t color;

typedef struct {
    LED_GENERAL_VARIABLES
    LED_MONO_COMMON_VARIABLES
#ifdef HAS_LOG
    char* name;
#endif
} LedMonoConfig_t;

typedef struct {
    LED_GENERAL_VARIABLES
    LED_MONO_COMMON_VARIABLES
    GpioLogicLevel_t prev;
    bool init;
    LedMode_t prev_mode;
    uint32_t cur_time_ms;
} LedMonoHandle_t;

#endif /* LED_MONO_TYPES_H  */
