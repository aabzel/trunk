#ifndef LED_RGB_TYPES_H
#define LED_RGB_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "sys_config.h"
#include "led_general_types.h"
#include "led_rgb_const.h"
#include "gpio_types.h"

#ifdef HAS_LED
#include "led_general_const.h"
#endif

#ifndef HAS_LED
#error "+HAS_LED"
#endif

typedef union {
    uint8_t byte;
    struct{
        uint8_t blue:1;
        uint8_t green:1;
        uint8_t red:1;
        uint8_t res:5;
    };
} LedRgbState_t;

typedef struct  {
    Color_t color;
    LedRgbState_t gpio_state;
} LedRgbInfo_t;

typedef struct  {
    Pad_t red;
    Pad_t green;
    Pad_t blue;
} LedRgbPads_t;

typedef struct  {
	LED_GENERAL_VARIABLES
    LedRgbPads_t Pads;
    Color_t set_color;
    char name[LED_RGB_NAME_SIZE];
} LedRgbConfig_t;

typedef struct  {
	LED_GENERAL_VARIABLES
    Color_t set_color;
    Color_t temp_color;
    LedRgbPads_t Pads;
    LedRgbState_t prev;
    LedRgbState_t state;
    uint32_t cur_time_ms;
    bool init;
} LedRgbHandle_t;

#endif /* LED_RGB_TYPES_H  */
