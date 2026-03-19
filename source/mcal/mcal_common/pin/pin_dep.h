#ifndef PIN_GENERAL_DEP_H
#define PIN_GENERAL_DEP_H

#ifndef HAS_TIME
#warning "+HAS_TIME"
#endif

#ifndef HAS_PINS
#warning "+HAS_PINS"
#endif

#ifndef HAS_PIN
#error "+HAS_PIN"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#endif /* PIN_GENERAL_DEP_H */
