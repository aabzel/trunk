#ifndef LED_MONO_PWM_DRIVER_H
#define LED_MONO_PWM_DRIVER_H

#include "std_includes.h"
#include "led_config.h"
#include "led_mono_types.h"
#include "sys_config.h"

#ifdef HAS_LED_MONO_DIAG
#include "led_mono_diag.h"
#endif

#ifndef HAS_LED_MONO
#error "+ HAS_LED_MONO"
#endif

#ifndef HAS_GPIO
#error "+ HAS_GPIO"
#endif

#ifndef HAS_LED
#error "+ HAS_LED"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+ HAS_MICROCONTROLLER"
#endif

/*API*/
bool LedMonoIsValidConfigPwm(const LedMonoConfig_t* const Config);

/*Setters*/
bool led_mono_set_on_duty(const uint8_t num, const float on_duty) ;
bool led_mono_set_off_duty(const uint8_t num, const float off_duty) ;

/*Getters*/
float led_logic_level_to_duty(const LedMonoHandle_t* const Node, const GpioLogicLevel_t des_logic_level);


#endif /* LED_MONO_PWM_DRIVER_H  */
