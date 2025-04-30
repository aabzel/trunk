#ifndef NVIC_TYPES_S
#define NVIC_TYPES_S

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"


#define NON_MASKABLE_INT_IRQ_N   (-14)

#ifndef HAS_NVIC
#error "+HAS_NVIC"
#endif
 
typedef struct {
    const char* name;
    int8_t int_n;
}NvicName_t;

typedef struct {
    const char* name;
    uint8_t priority;
}NvicPriorityName_t;
 
#ifdef __cplusplus
}
#endif

#endif /* NVIC_TYPES_S  */
