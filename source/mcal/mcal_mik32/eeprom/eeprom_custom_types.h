#ifndef EEPROM_CUSTOM_TYPES_H
#define EEPROM_CUSTOM_TYPES_H

#include "eeprom_custom_const.h"
#include "mik32_hal_eeprom.h"
#include "eeprom.h"

#define EEPROM_CUSTOM_TYPES               \
    volatile EEPROM_REGS_TypeDef *EEPROMx;         \
    HAL_EEPROM_HandleTypeDef handle;


#endif /* EEPROM_CUSTOM_TYPES_H  */
