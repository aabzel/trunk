#ifndef DRV8870_CONST_H
#define DRV8870_CONST_H

#include "time_mcal.h"
#include "drv8870_dep.h"

#define DRV8870_VERSION "2"
#define DRV8870_PERIOD_US MSEC_2_USEC(500)

typedef enum{
    DRV8870_MODE_BRAKE = 1,
    DRV8870_MODE_FORWARD= 2,
    DRV8870_MODE_REVERSE= 3,
    DRV8870_MODE_HI_Z = 4,
    DRV8870_MODE_UNDEF = 0,
}Drv8870Mode_t ;

#endif /* DRV8870_CONST_H */
