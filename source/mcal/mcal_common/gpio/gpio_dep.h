#ifndef GPIO_GENERAL_DEP_H
#define GPIO_GENERAL_DEP_H

#ifndef HAS_TIME
#warning "+HAS_TIME"
#endif

#ifndef HAS_PINS
#warning "+HAS_PINS"
#endif

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#endif /* GPIO_GENERAL_DEP_H */
