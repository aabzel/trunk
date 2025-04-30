#ifndef EXT_INT_CUSTOM_TYPES_H
#define EXT_INT_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ext_int_custom_const.h"
#include "microcontroller_types.h"
#include "clock_const.h"

#define EXT_INT_CUSTOM_VARIABLES


typedef struct {
    bool valid;
    uint8_t num;
    IRQn_Type irq_n;
    uint32_t exint_line_n;
}ExtIntInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* EXT_INT_CUSTOM_TYPES_H  */
