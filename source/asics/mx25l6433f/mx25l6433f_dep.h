#ifndef MX25L6433F_DEP_H
#define MX25L6433F_DEP_H

#ifndef HAS_MX25L6433F
#error "+HAS_MX25L6433F"
#endif

#ifndef HAS_MICROCONTROLLER
#error "MX25L6433F Needs HAS_MICROCONTROLLER"
#endif

#ifndef HAS_SPI
#error "MX25L6433F: HAS_SPI must be defined! SPI driver is required."
#endif

#ifndef HAS_GPIO
#error "MX25L6433F: HAS_GPIO must be defined! GPIO for CS pin is required."
#endif

#ifndef HAS_TIME
#error "+HAS_TIME"
#endif

#endif /* MX25L6433F_DEP_H */
