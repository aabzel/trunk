#ifndef CRYP_GENERAL_H
#define CRYP_GENERAL_H

#include <stdbool.h>
#include <stdint.h>

#include "data_utils.h"
#ifdef HAS_MCU
#include "sys_config.h"
#endif

#ifdef USE_HAL_DRIVER
#include "stm32f4xx_hal.h"
#endif /*USE_HAL_DRIVER*/
#include "cryp_types.h"

bool cryp_is_valid(uint8_t cryp_num);
const CrypConfig_t* CrypGetConfigNode(uint8_t cryp_num);
CrypHandle_t* CrypGetNode(uint8_t cryp_num);

#endif /* CRYP_GENERAL_H */
