#ifndef EXT_INT_GENERAL_CONST_H
#define EXT_INT_GENERAL_CONST_H

#include "ext_int_dep.h"

#define EXT_INT_COMPONENT_VERSION "1"

typedef enum {
    PIN_INT_EDGE_NONE=0,
    PIN_INT_EDGE_FALLING=1,
    PIN_INT_EDGE_RISING=2,
    PIN_INT_EDGE_BOTH=3,
    PIN_INT_EDGE_UNDEF=4,
}PinIntEdge_t;




#endif /* EXT_INT_GENERAL_CONST_H */
