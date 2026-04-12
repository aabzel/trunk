#ifndef LED_DIAG_H
#define LED_DIAG_H

#include "led_general_const.h"

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#ifndef HAS_LED
#error "+HAS_LED"
#endif

#ifndef HAS_LED_DIAG
#error "+HAS_LED_DIAG"
#endif

#ifdef HAS_LED_MONO
#include "led_mono_types.h"

#ifdef HAS_LED_MONO_DIAG
#include "led_mono_diag.h"
#endif

#endif


bool LedTableHeaderPrint(void);
bool LedTableTailPrint(void);
const char* LedModeToStr(const LedMode_t mode);
const char* ColorToStr(Color_t color);

#endif /* LED_DIAG_H  */
