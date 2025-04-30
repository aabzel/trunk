#ifndef LED_MONO_DRIVER_H
#define LED_MONO_DRIVER_H

#include "std_includes.h"
#include "led_config.h"
#include "led_dep.h"
#include "led_mono_types.h"
#include "sys_config.h"

#ifndef HAS_GPIO
#error "+ HAS_GPIO"
#endif

#ifndef HAS_LED
#error "+ HAS_LED"
#endif

#ifndef HAS_LED_MONO
#error "+ HAS_LED_MONO"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+ HAS_MICROCONTROLLER"
#endif

/*API*/
const LedMonoConfig_t* LedMonoGetConfig(uint8_t num);
LedMonoHandle_t* LedMonoGetNode(uint8_t num);
LedMonoHandle_t* LedPad2Node(uint8_t pad_num);
bool led_mono_proc_one(uint32_t num);
bool led_mono_proc(void);
bool led_mono_init_one(uint32_t num);
bool led_mono_mcal_init(void);
bool led_mono_init_custom(void);

/*Setters*/
bool led_set_state(uint8_t pad_num, GpioLogicLevel_t des_logic_level);
bool led_mono_blink(uint8_t num, uint32_t duration_ms);
bool led_mono_pwm(uint8_t num, float freq, float duty);
bool led_mono_ctrl(const uint8_t num, const bool on_off);
bool led_mono_toggle(const uint8_t num);
bool led_mono_on(LedMonoHandle_t* const Node);
bool led_mono_off(LedMonoHandle_t* const Node);
bool led_mono_mode_set(uint8_t num, LedMode_t mode);
bool led_mono_set(uint8_t num, GpioLogicLevel_t level);

/*Getters*/
GpioLogicLevel_t led_mono_get(uint8_t num);


#endif /* LED_MONO_DRIVER_H  */
