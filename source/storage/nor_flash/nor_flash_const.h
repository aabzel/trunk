#ifndef NOR_FLASH_CONST_H
#define NOR_FLASH_CONST_H

#include "nor_flash_dep.h"

#define OFF_CHIP_NOR_FLASH_PAGE_SIZE 256

typedef enum {
    NOR_FLASH_BLOCK_4K = 4,
    NOR_FLASH_BLOCK_32K = 32,
    NOR_FLASH_BLOCK_64K = 64,

    NOR_FLASH_BLOCK_UNDEF = 0,
} NorFlashBlockSize_t;

typedef enum {
    NOR_FLASH_OPTION_SW=1,
    NOR_FLASH_OPTION_ON_CHIP=2,
    NOR_FLASH_OPTION_OFF_CHIP=3,

    NOR_FLASH_OPTION_UNDEF=0,
}NorFlashOption_t;

#endif /* NOR_FLASH_CONST_H */
