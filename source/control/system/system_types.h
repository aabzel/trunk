#ifndef SYSTEM_TYPES_H
#define SYSTEM_TYPES_H

#include "std_includes.h"
#include "sys_constants.h"

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif

typedef struct{
    facility_t facility;
    char* name;
}FacilityInfo_t;

typedef struct{
    BuildType_t fw_type;
    char *name;
}ProgTypeInfo_t;

typedef bool (*InitFunction_t)(void);

typedef struct{
    InitFunction_t init_function;
    char *name;
#ifdef HAS_LOG
#endif
}SystemInitInstance_t;

typedef struct{
    bool init;
    bool init_finish;
    char InitOrder[1600] ;
    char InitError[150] ;
#ifdef HAS_GPIO
    Pad_t DebugPad;
#endif
}System_t;


#endif /* SYSTEM_TYPES_H  */
