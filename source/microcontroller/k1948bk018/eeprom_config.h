#ifndef EEPROM_CONFIG_H
#define EEPROM_CONFIG_H

#include "std_includes.h"
#include "eeprom_types.h"

extern EepromHandle_t EepromInstance;
extern const EepromConfig_t EepromConfig;

uint32_t eeprom_get_sector_cnt(void);

#endif /* EEPROM_CONFIG_H  */
