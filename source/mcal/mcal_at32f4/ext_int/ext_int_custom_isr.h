#ifndef EXT_INT_CUSTOM_ISR_H
#define EXT_INT_CUSTOM_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ext_int_custom_types.h"
#include "ext_int_mcal.h"
#include "microcontroller_const.h"

#ifndef HAS_EXT_INT_ISR
#error "+HAS_EXT_INT_ISR"
#endif

bool EXINTx_IRQHandler(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* EXT_INT_CUSTOM_ISR_H  */
