#ifndef EXT_INT_MCAL_ISR_H
#define EXT_INT_MCAL_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ext_int_types.h"
#ifdef HAS_EXT_INT_CUSTOM
#include "ext_int_custom_isr.h"
#endif

bool ExtIntRisingCallBack(ExtIntHandle_t* const Node);
bool ExtIntFallingCallBack(ExtIntHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* EXT_INT_MCAL_ISR_H */
