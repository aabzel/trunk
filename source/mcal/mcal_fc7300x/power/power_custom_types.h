#ifndef POWER_CUSTOM_TYPES_H
#define POWER_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "power_custom_const.h"
#include "microcontroller_types.h"
#include "clock_const.h"


#define POWER_CUSTOM_VARIABLES       PCU_Type* POWERx;


typedef struct {
    bool valid;
    PCU_Type* POWERx;
    uint8_t num;
    IRQn_Type irq_n;
}PowerInfo_t;



#ifdef __cplusplus
}
#endif

#endif /* POWER_CUSTOM_TYPES_H  */
