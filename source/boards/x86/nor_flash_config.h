#ifndef NOR_FLASH_CONFIG_H
#define NOR_FLASH_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nor_flash_types.h"

#ifndef HAS_NOR_FLASH
#error "+HAS_NOR_FLASH"
#endif /*HAS_NOR_FLASH*/

extern const NorFlashConfig_t NorFlashConfig[];
extern NorFlashItem_t NorFlashItem[];

uint32_t nor_flash_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /*NOR_FLASH_CONFIG_H*/
