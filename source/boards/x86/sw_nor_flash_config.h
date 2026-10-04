#ifndef SW_NOR_FLASH_CONFIG_H
#define SW_NOR_FLASH_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sw_nor_flash_types.h"

#ifndef HAS_SW_NOR_FLASH
#error  "+HAS_SW_NOR_FLASH"
#endif /* */

#define SW_NOR_FLASH_FLASH_SIZE (2*1024*1024)
#define SW_NOR_FLASH_PAGE_SIZE 128
#define SW_NOR_FLASH_BLOCK_SIZE 0x10000   /* 128 blocks of 64KBytes */
#define SW_NOR_FLASH_SUBBLOCK_SIZE 0x8000 /* 256 blocks of 32KBytes */
#define SW_NOR_FLASH_SECTOR_SIZE 0x1000   /* 2048 sectors of 4kBytes */


extern const SwNorFlashConfig_t SwNorFlashConfig[];
extern SwNorFlashHandle_t SwNorFlashInstance[];

uint32_t sw_nor_flash_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /*SW_NOR_FLASH_CONFIG_H*/
