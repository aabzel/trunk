#ifndef DUMMY_MCU_TYPES_H
#define DUMMY_MCU_TYPES_H

#include "dummy_mcu_const.h"

#if 0
typedef union {
    uint8_t byte;
    struct {
        uint8_t pin  : 5; /*0....31*/
        uint8_t port : 3; /*A B C D E*/
    };
}Pad_t;
#endif


#endif /* DUMMY_MCU_TYPES_H */
