#ifndef EXT_INT_GENERAL_CONST_H
#define EXT_INT_GENERAL_CONST_H

#include "ext_int_dep.h"

#define EXT_INT_COMPONENT_VERSION "2"
#define EXT_INT_POLL_PERIOD_US 500

typedef enum {
    PIN_INT_EDGE_NONE = 1,
    PIN_INT_EDGE_FALLING = 2,
    PIN_INT_EDGE_RISING = 3,
    PIN_INT_EDGE_BOTH = 4,

    PIN_INT_EDGE_UNDEF = 0,
}PinIntEdge_t;

#endif /* EXT_INT_GENERAL_CONST_H */
