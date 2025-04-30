#ifndef SCHMITT_TRIGGER_CONST_H
#define SCHMITT_TRIGGER_CONST_H

#include "schmitt_trigger_dep.h"

typedef enum{
    SCHMITT_TRIGGER_STATE_UP=1,
    SCHMITT_TRIGGER_STATE_DOWN=2,

    SCHMITT_TRIGGER_STATE_UNDEF=0,
}SchmittTriggerState_t;

#endif /* SCHMITT_TRIGGER_CONST_H  */
