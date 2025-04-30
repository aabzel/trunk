#ifndef EEPROM_CUSTOM_DRV_H
#define EEPROM_CUSTOM_DRV_H

#include "std_includes.h"
#include "eeprom.h"


bool eeprom_wait_bysy(const  EEPROM_REGS_TypeDef * const EEPROMx    );
bool is_eeprom_address(uint32_t addr);
#ifdef HAS_EEPROM_EX
bool AddrToSectorSize(const uint32_t addr,
                      uint32_t *const sector,
                      uint32_t *const sec_size);
#endif

#endif /* EEPROM_CUSTOM_DRV_H  */
