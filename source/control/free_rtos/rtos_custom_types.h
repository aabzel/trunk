#ifndef FREE_RTOS_TYPES_H
#define FREE_RTOS_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "rtos_custom_const.h"
#include "FreeRTOS.h"
#include "task.h"


typedef void (*FreeRtosTaskFunction_t)( void * );

#define RTOS_CUSTOM_TYPES               \
    FreeRtosTaskFunction_t TaskCode ;   \
    TaskHandle_t handle ;

#if 0
typedef struct{
	uint16_t num;
    char* name;  
    uint32_t stack_depth_byte; /**/
    Priority_t priority;
    bool valid;
}FreeRtosTaskConfig_t;

typedef struct{
	uint16_t num;
	bool valid;
}FreeRtosTaskHandle_t;
#endif


#ifdef __cplusplus
}
#endif

#endif /* FREE_RTOS_TYPES_H */
