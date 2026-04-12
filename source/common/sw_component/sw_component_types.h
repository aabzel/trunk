#ifndef SW_COMPONENT_TYPES_H
#define SW_COMPONENT_TYPES_H

#include "std_includes.h"
#include "sw_component_const.h"


#ifdef HAS_SW_COMPONENT_CUSTOM
#include "sw_component_custom_types.h"
#else
#define SW_COMPONENT_CUSTOM_VARIABLES
#endif

typedef struct {
    uint8_t num;
    uint16_t irq_n;
    /*Reg info*/
    /*Reg cnt*/
    uint32_t clock_type;
    uint32_t* SW_COMPONENTx; /*PHY Address. Initial physical address of the subsystem registers*/
    bool valid;
}SwComponentInfo_t;

#define SW_COMPONENT_COMMON_VARIABLES                  \
    char* name;                                        \
    uint8_t num;                                       \
    bool interrupt_on;                                 \
    bool valid;

typedef struct {
    SW_COMPONENT_COMMON_VARIABLES
}SwComponentConfig_t;

typedef struct {
    SW_COMPONENT_COMMON_VARIABLES
    SW_COMPONENT_CUSTOM_VARIABLES
    bool init;
    uint32_t spin;
}SwComponentHandle_t;


#endif /* SW_COMPONENT_TYPES_H */
