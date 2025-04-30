#ifndef NOR_FLASH_DIAG_H
#define NOR_FLASH_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "nor_flash_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_NOR_FLASH
#error "+HAS_NOR_FLASH"
#endif /*HAS_NOR_FLASH*/

#ifndef HAS_NOR_FLASH_DIAG
#error "+HAS_NOR_FLASH_DIAG"
#endif /*HAS_DIAG_NOR_FLASH*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

const char* NorFlashOption2Str(NorFlashOption_t option);
const char* NorFlashNum2Option(uint8_t flash_num);
bool nor_flash_diag(uint8_t flash_num);
bool nor_flash_usage(uint8_t flash_num, uint32_t piece_size);
bool nor_flash_mem_diag(uint8_t flash_num, uint32_t phy_address, uint32_t size, char* name);

#endif /* NOR_FLASH_DIAG_H  */
