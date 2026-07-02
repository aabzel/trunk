#ifndef INTERRUPT_TYPES_H
#define INTERRUPT_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "microcontroller_const.h"

typedef struct  {
    const char *name;
    int16_t int_n;  /*IRQn_Type*/
}IntNumInfo_t;

typedef struct {
    const char* name;
    uint8_t priority;
} IntPriorityName_t;

typedef struct {
    int16_t irq_n; /*IRQn_Type*/
    uint32_t priority;
    bool on_off;
    bool valid;
} InterruptConfig_t;

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPT_TYPES_H  */
