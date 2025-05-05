#ifndef SYSTEM_TYPES_H
#define SYSTEM_TYPES_H

#include "std_includes.h"
#include "sys_constants.h"

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
#ifdef HAS_LOG
    char *name;
#endif
}SystemInitInstance_t;

typedef struct{
    bool init;
    bool init_finish;
}System_t;


#endif /* SYSTEM_TYPES_H  */
