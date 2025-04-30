#ifndef LED_MONO_DIAG_H
#define LED_MONO_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "led_diag.h"
#include "led_mono_types.h"

#ifndef HAS_LED_MONO
#error "+ HAS_LED_MONO"
#endif

#ifndef HAS_LED_MONO_DIAG
#error "+ HAS_LED_MONO_DIAG"
#endif

bool LedMonoDiag(LedMonoHandle_t* const  LedNode);
bool LedMonoConfigDiag(const LedMonoConfig_t*const  Config);
bool led_mono_diag(void) ;

#endif /* LED_MONO_DIAG_H  */
