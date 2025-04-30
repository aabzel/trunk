#ifndef LED_MONO_DEP_H
#define LED_MONO_DEP_H


#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif

#ifndef HAS_LED
#error "+HAS_LED"
#endif

#ifndef HAS_LED_MONO
#error "+HAS_LED_MONO"
#endif

#ifndef HAS_MATH
#warning "+HAS_MATH"
#endif

#ifndef HAS_PINS
#warning "+HAS_PINS"
#endif

#ifndef HAS_TIME
#warning "+HAS_TIME"
#endif

#endif /* LED_MONO_DEP_H  */
