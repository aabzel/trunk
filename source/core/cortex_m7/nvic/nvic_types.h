#ifndef NVIC_TYPES_S
#define NVIC_TYPES_S

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_NVIC
#error "+HAS_NVIC"
#endif
 
typedef struct  {
    const char *name;
    int8_t int_n;
}IntName_t;

typedef struct  {
    const char *name;
    uint8_t priority;
}IntPriorityName_t;
 
#ifdef __cplusplus
}
#endif

#endif /* NVIC_TYPES_S  */
