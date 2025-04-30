#ifndef LED_RGB_DRIVER_H
#define LED_RGB_DRIVER_H

#include <stdbool.h>
#include <stdint.h>

#include "led_rgb_config.h"
#include "led_rgb_types.h"
#include "sys_config.h"

#ifndef HAS_LED
#error "+ HAS_LED"
#endif

#ifndef HAS_LED_RGB
#error "+ HAS_LED_RGB"
#endif

#ifndef HAS_GPIO
#error "+ HAS_GPIO"
#endif

#ifndef HAS_MATH
#error "+ HAS_MATH"
#endif

extern const LedRgbInfo_t LedRgbInfoLUT[];

bool led_rgb_init(void);
bool led_rgb_init_one(uint32_t num );
bool led_rgb_set_color(uint8_t led_rgb_num, Color_t color);
bool led_rgb_test(void);
bool led_rgb_test_one(uint8_t led_rgb_num) ;
bool led_rgb_blink(uint8_t led_rgb_num, uint32_t duration_ms, Color_t color) ;
bool led_rgb_blink_ll(LedRgbHandle_t* inLed, uint32_t duration_ms, Color_t color) ;
bool led_rgb_pwm(uint8_t led_rgb_num, double freq, uint8_t duty);
bool led_rgb_on(LedRgbHandle_t* inLedRgb);
bool led_rgb_off(LedRgbHandle_t* inLedRgb);
bool proc_led_rgbs(void);
bool led_rgb_add(void);
Color_t led_rgb_get_color_ll(LedRgbHandle_t* inLed);
Color_t led_rgb_get_color(uint8_t led_rgb_num);
const LedRgbConfig_t* LedRgbGetConfig(uint8_t led_rgb_num);
LedRgbHandle_t* LedRgbGetNode(uint8_t led_rgb_num);
uint8_t Color2RgbGpio(Color_t color);
uint32_t led_rgb_get_color_cnt(void);

#endif /* LED_RGB_DRIVER_H  */
