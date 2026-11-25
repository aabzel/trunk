#ifndef FC7300F8MDT_TYPES_H
#define FC7300F8MDT_TYPES_H


#include "fc7300f8mdt_const.h"

typedef union {
    uint8_t byte;
    struct {
        uint8_t pin  : 5; /*0....31*/
        uint8_t port : 3; /*A B C D E*/
    };
}Pad_t;


#endif /* FC7300F8MDT_TYPES_H */
