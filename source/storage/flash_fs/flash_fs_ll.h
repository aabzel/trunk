#ifndef NOR_FLASH_API_H
#define NOR_FLASH_API_H

#include "std_includes.h"

#ifdef HAS_FLASH_FS_WRITE
bool flash_fs_write(const uint32_t address_des, const uint8_t* const address_src, const uint32_t len);
bool flash_fs_zero(uint32_t address, uint32_t len);
#endif

#endif /* NOR_FLASH_API_H */
