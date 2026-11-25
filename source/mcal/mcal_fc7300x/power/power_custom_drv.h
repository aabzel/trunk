#ifndef POWER_CUSTOM_HAL_H
#define POWER_CUSTOM_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "microcontroller_const.h"

PCU_Type* PowerNumToBase(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* POWER_CUSTOM_HAL_H  */
