#ifndef LED_MONO_DRIVER_H
#define LED_MONO_DRIVER_H

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
const LedMonoConfig_t* LedMonoGetConfig(uint8_t num);
LedMonoHandle_t* LedMonoGetNode(uint8_t num);
LedMonoHandle_t* LedPadToNode(Pad_t Pad);
bool led_mono_proc_one(uint32_t num);
bool led_mono_proc_group(uint32_t group);
bool led_mono_proc(void);
bool led_mono_proc_custom(void);

bool led_mono_init_one(uint32_t num);
bool led_mono_mcal_init(void);
bool led_mono_init_custom(void);

/*Setters*/
bool led_mono_duration_set(const uint8_t num, const uint32_t duration_ms);
bool led_mono_set_on_duty(const uint8_t num, const float on_duty) ;
bool led_set_state(Pad_t Pad, GpioLogicLevel_t des_logic_level);
bool led_mono_blink(uint8_t num, uint32_t duration_ms);
bool led_mono_frequency_set(uint8_t num, float freq);
bool led_mono_sw_pwm(uint8_t num, float freq, float duty);
bool led_mono_hw_pwm(uint8_t num, float freq, float duty);
bool led_mono_ctrl(const uint8_t num, const bool on_off);
bool led_mono_toggle(const uint8_t num);
bool led_mono_on(LedMonoHandle_t* const Node);
bool led_mono_off(LedMonoHandle_t* const Node);
bool led_mono_fix(void);
bool led_mono_mode_set(uint8_t num, LedMode_t mode);
bool led_mono_set(uint8_t num, GpioLogicLevel_t level);

/*Getters*/
bool led_mono_set_off_duty(const uint8_t num, const float off_duty) ;
float led_logic_level_to_duty(const LedMonoHandle_t* const Node, const GpioLogicLevel_t des_logic_level);
GpioLogicLevel_t led_mono_get(uint8_t num);
uint8_t LedMonoPadToNum(const Pad_t Pad);


#endif /* LED_MONO_DRIVER_H  */
