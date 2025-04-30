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


const char* LedMode2Str(LedMode_t mode);
bool LedTableHeaderPrint(void);
bool LedTableTailPrint(void);
const char* Color2Str(Color_t color);

#endif /* LED_DIAG_H  */
