
#ifndef NRF5340_TYPES_H
#define NRF5340_TYPES_H

#include <stdint.h>

#include "nrf5340_const.h"

#ifndef HAS_MICROCONTROLLER
#error  "+HAS_MICROCONTROLLER"
#endif

/*GPIO port pin*/
typedef union {
    uint8_t byte;
    struct {
        uint8_t pin  : 5; /*0....31 ()*/
        uint8_t port : 3; /*[valid 0 1] (invalid 2 3 4 5 6 7) */
    };
}Pad_t;


#endif /* NRF5340_TYPES_H */
