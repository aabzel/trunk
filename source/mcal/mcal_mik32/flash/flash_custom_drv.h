#ifndef FLASH_CUSTOM_DRV_H
#define FLASH_CUSTOM_DRV_H

#include "std_includes.h"

bool is_eeprom_address(uint32_t addr);
#ifdef HAS_FLASH_EX
bool AddrToSectorSize(const uint32_t addr,
		              uint32_t *const sector,
					  uint32_t *const sec_size);
#endif

#endif /* FLASH_CUSTOM_DRV_H  */
