#ifndef EXT_INT_GENERAL_CONST_H
#define EXT_INT_GENERAL_CONST_H

#include "ext_int_dep.h"

#define EXT_INT_COMPONENT_VERSION 4
#define EXT_INT_POLL_PERIOD_US 1000

/*For EventFIFO */
typedef enum {
    PIN_INT_DROP_FALLING = 1,
    PIN_INT_DROP_RISING = 2,
    PIN_INT_DROP_UNDEF = 0,
}PinIntDrop_t;

typedef enum {
    PIN_INT_EDGE_FALLING = 1,
    PIN_INT_EDGE_RISING = 2,
    PIN_INT_EDGE_NONE = 3,
    PIN_INT_EDGE_BOTH = 4,

    PIN_INT_EDGE_UNDEF = 0,
}PinIntEdge_t;

#endif /* EXT_INT_GENERAL_CONST_H */
