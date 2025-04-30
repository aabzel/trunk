#ifndef WATCHDOG_DEP_H
#define WATCHDOG_DEP_H

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#ifndef HAS_WATCHDOG
#error "+HAS_WATCHDOG"
#endif

#ifndef HAS_CLOCK
#error "+HAS_CLOCK"
#endif

#ifndef HAS_TIME
#error "+HAS_TIME"
#endif


#endif /* WATCHDOG_DEP_H */
