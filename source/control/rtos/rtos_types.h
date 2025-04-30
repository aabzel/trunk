#ifndef RTOS_TYPES_H
#define RTOS_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "rtos_const.h"

#ifdef HAS_RTOS_CUSTOM
#include "rtos_custom_types.h"
#else
#define RTOS_CUSTOM_TYPES
#endif

//RtosTaskFunction_t TaskCode;
//typedef void (*RtosTaskFunction_t)( void *, void *,void * );

#define RTOS_COMMON_TYPES   \
    uint16_t num;   \
    bool valid;    \
    char* name;

typedef struct {
    RTOS_CUSTOM_TYPES
    RTOS_COMMON_TYPES
    uint8_t* stack_start;
    uint32_t stack_depth_byte;
    Priority_t priority;
}RtosTaskConfig_t;

typedef struct{
    RTOS_CUSTOM_TYPES
    RTOS_COMMON_TYPES
    //struct k_thread handle;
    //k_tid_t  id;
}RtosTaskHandle_t;


#ifdef __cplusplus
}
#endif

#endif /* RTOS_TYPES_H */
