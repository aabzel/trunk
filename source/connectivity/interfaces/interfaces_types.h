#ifndef INTERFACES_TYPES_H
#define INTERFACES_TYPES_H

/*
add
#include "interfaces_types.h"
*/

#include "interfaces_const.h"
#include "std_inc.h"

typedef union {
    uint16_t word;
    struct {
        uint16_t num:5; /*0... 31 Code 0x1F means all instanced */
        uint16_t interface_name:11; /* see enum InterfaceName_t for variants */
    };
} InterfaceType_t;

typedef struct {
    uint32_t byte_rx; // bytes
    uint32_t byte_tx; // bytes
} FlowCnt_t;

typedef struct {
    InterfaceName_t inter_face;
    bool valid;
    char *name;
}InterfaceNameInfo_t;

#endif /* INTERFACES_TYPES_H */
