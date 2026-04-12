#include "led_drv.h"

#include "gpio_const.h"
#include "std_includes.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif

static GpioLogicLevel_t LedLogicLevelZero2Voltage(GpioLogicLevel_t active) {
    GpioLogicLevel_t voltage = GPIO_LVL_UNDEF;
    switch(active) {
    case GPIO_LVL_LOW:
        voltage = GPIO_LVL_HI;
        break;
    case GPIO_LVL_HI:
        voltage = GPIO_LVL_LOW;
        break;
    default:
        break;
    }
    return voltage;
}

static GpioLogicLevel_t LedLogicLevelHi2Voltage(GpioLogicLevel_t active) {
    GpioLogicLevel_t voltage = active;
    return voltage;
}

GpioLogicLevel_t LedLogicLevel2Voltage(uint8_t val, GpioLogicLevel_t active) {
    GpioLogicLevel_t voltage = GPIO_LVL_UNDEF;
    switch(val) {
    case GPIO_LVL_LOW:
        voltage = LedLogicLevelZero2Voltage(active);
        break;
    case GPIO_LVL_HI:
        voltage = LedLogicLevelHi2Voltage(active);
        break;
    default:
        break;
    }
    return voltage;
}

bool led_pwm(uint8_t led_num, float freq_hz, uint8_t duty) {
    bool res = true;
#ifdef HAS_LED_MONO
    res = led_mono_sw_pwm(led_num, freq_hz, duty);
#endif

#ifdef HAS_LED_RGB
    res = led_rgb_pwm(led_num, freq_hz, duty);
#endif
    return res;
}
