#ifndef LED_MONO_PWM_MCAL_H
#define LED_MONO_PWM_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "led_mono_pwm_config.h"
#include "led_mono_pwm_types.h"
#ifdef HAS_LED_MONO_PWM_DIAG
#include "led_mono_pwm_diag.h"
#endif

/* API */
LedMonoPwmHandle_t* LedMonoPwmGetNode(uint8_t num);
const LedMonoPwmConfig_t* LedMonoPwmGetConfig(uint8_t num);
bool LedMonoPwmIsValidConfig(const LedMonoPwmConfig_t* const Config);

#ifdef HAS_LED_MONO_PWM_CUSTOM
const LedMonoPwmInfo_t* LedMonoPwmGetInfo(uint8_t num);
#endif

bool led_mono_pwm_mcal_init(void);
bool led_mono_pwm_init_custom(void);
bool led_mono_pwm_init_one(uint8_t num);

bool led_mono_pwm_proc_one(uint8_t num);
bool led_mono_pwm_proc(void);

/*setters*/
bool led_mono_pwm_set_duty(uint8_t num, float duty) ;
bool led_mono_pwm_ctrl(const Pad_t Pad, const bool on_off);

/*getters*/
LedMonoPwmHandle_t* LedMonoPwmPadToNode(const Pad_t Pad) ;

#ifdef __cplusplus
}
#endif

#endif /* LED_MONO_PWM_MCAL_H */
