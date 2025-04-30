#ifndef SW_NOR_FLASH_CONST_H
#define SW_NOR_FLASH_CONST_H

#include "sw_nor_flash_dep.h"

#define SW_NOR_FLASH_FLASH_SIZE 0x800000
#define SW_NOR_FLASH_PAGE_SIZE 256
#define SW_NOR_FLASH_BLOCK_SIZE 0x10000   /* 128 blocks of 64KBytes */
#define SW_NOR_FLASH_SUBBLOCK_SIZE 0x8000 /* 256 blocks of 32KBytes */
#define SW_NOR_FLASH_SECTOR_SIZE 0x1000   /* 2048 sectors of 4kBytes */

#endif /* SW_NOR_FLASH_CONST_H */
