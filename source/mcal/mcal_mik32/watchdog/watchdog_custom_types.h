#ifndef WATCHDOG_TYPES_H
#define WATCHDOG_TYPES_H

#include "std_includes.h"
#include "watchdog_custom_const.h"
#include "mik32_hal.h"
#include "watchdog_register_types.h"

typedef struct{
    uint16_t divider;
    Mik32WatchDogPreScale_t prescale;
}WatchDogInfo_t;




#define WATCHDOG_COSTOM_VARIABLE   \
    WatchDogRegMap_t * WATCHDOGx;

#endif /* WATCHDOG_TYPES_H  */
