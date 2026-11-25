#ifndef POWER_CUSTOM_ISR_H
#define POWER_CUSTOM_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

//#include "power_custom_types.h"
//#include "power_mcal.h"
//#include "microcontroller_const.h"

#ifndef HAS_POWER_ISR
#error "+HAS_POWER_ISR"
#endif

bool PowerIRQHandler(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* POWER_CUSTOM_ISR_H  */
