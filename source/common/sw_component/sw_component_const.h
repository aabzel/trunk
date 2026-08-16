#ifndef SW_COMPONENT_CONST_H
#define SW_COMPONENT_CONST_H

#include "time_mcal.h"
#include "sw_component_dep.h"

#define SW_COMPONENT_VERSION 2
#define SW_COMPONENT_PERIOD_US MSEC_2_USEC(500)

typedef enum {
    SW_COMPONENT_STATE_0 = 1,
    SW_COMPONENT_STATE_1 = 2,
    SW_COMPONENT_STATE_2 = 3,
    SW_COMPONENT_STATE_UNDEF = 0,
}SwComponentState_t;


#endif /* SW_COMPONENT_CONST_H */
