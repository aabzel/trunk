#ifndef FLASH_NRF53_TYPES_H
#define FLASH_NRF53_TYPES_H

#include <stdint.h>

#include "flash_bsp_const.h"
#include "flash_custom_const.h"

#ifndef HAS_FLASH
#error "+HAS_FLASH"
#endif

#if 0
typedef struct {
    uint32_t start;
    uint32_t size;
    uint8_t sector;
    MemContent_t content;
} FlashSectorConfig_t;
#endif

#endif /* FLASH_NRF53_TYPES_H  */
