#ifndef LED_MONO_PWM_CONFIG_H
#define LED_MONO_PWM_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "led_mono_pwm_types.h"
#include "led_mono_pwm_dep.h"

extern const LedMonoPwmConfig_t LedMonoPwmConfig[];
extern LedMonoPwmHandle_t LedMonoPwmInstance[];

uint32_t led_mono_pwm_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* LED_MONO_PWM_CONFIG_H */
