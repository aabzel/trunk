#ifndef LED_GENERAL_DEP_H
#define LED_GENERAL_DEP_H

#ifndef HAS_LED
#error "+HAS_LED"
#endif

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif

#ifndef HAS_TIME
#warning "+HAS_TIME"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#endif /* LED_GENERAL_DEP_H  */
