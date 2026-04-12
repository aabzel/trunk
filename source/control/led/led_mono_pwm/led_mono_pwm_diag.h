#ifndef LED_MONO_PWM_DIAG_H
#define LED_MONO_PWM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "led_mono_pwm_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_LED_MONO_PWM
#error "+HAS_LED_MONO_PWM"
#endif /**/

#ifndef HAS_LED_MONO_PWM_DIAG
#error "+HAS_LED_MONO_PWM_DIAG"
#endif /**/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /**/

bool led_mono_pwm_diag(void);
const char* LedMonoPwmConfigToStr(const LedMonoPwmConfig_t* const Config);
const char* LedMonoPwmNodeToStr(const LedMonoPwmHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* LED_MONO_PWM_DIAG_H  */
