#include "eeprom_config.h"

#ifndef HAS_EEPROM
#error "Add HAS_EEPROM"
#endif /*HAS_EEPROM*/

#include "microcontroller_const.h"

EepromHandle_t EepromInstance = {0};

const EepromConfig_t EepromConfig = {
    .start = ROM_START,
    .size = ROM_SIZE,
    .interrupt_on = true,
};

uint32_t eeprom_get_sector_cnt(void) {
    uint32_t cnt = 1;
    return cnt;
}

