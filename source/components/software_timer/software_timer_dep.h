#ifndef SOFTWARE_TIMER_DEP_H
#define SOFTWARE_TIMER_DEP_H

#ifndef HAS_SOFTWARE_TIMER
#error "+HAS_SOFTWARE_TIMER"
#endif

#ifndef HAS_FLASH
#error "+HAS_FLASH"
#endif

#ifndef HAS_TIMER
#warning "+HAS_TIMER"
#endif

#ifndef HAS_SYSTICK
/*FreeRTOS adjust Systick itself*/
#warning "+HAS_SYSTICK"
#endif

#endif /*SOFTWARE_TIMER_DEP_H*/
