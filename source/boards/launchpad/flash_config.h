#ifndef FLASH_CONFIG_GENERAL_H
#define FLASH_CONFIG_GENERAL_H

#include <stdbool.h>
#include <stdint.h>

#include "flash_types.h"
#include "macro_utils.h"

#ifndef HAS_FLASH
#error "Add HAS_FLASHER"
#endif /*HAS_FLASHER*/
#define NOR_FLASH_SIZE (352 * K_BYTES)

#define NOR_FLASH_BASE 0x00000000
#ifndef MBR_START_ADDRESS
#define MBR_START_ADDRESS NOR_FLASH_BASE
#endif

#define BOOT_START_ADDRESS 0x00000000
#define APP_START_ADDRESS 0x00000000
#define APP_SIZE (NOR_FLASH_SIZE)

#define NOR_FLASH_START NOR_FLASH_BASE
#define NOR_FLASH_END (NOR_FLASH_START+NOR_FLASH_SIZE)

#define FLASH_SECTOR_SIZE  (8 * K_BYTES)

#define APP_PAGE_CNT 22

#ifdef HAS_GENERIC
#define FW_START_ADDRESS APP_START_ADDRESS
#endif

#ifdef HAS_BOOTLOADER
#define FW_START_ADDRESS BOOT_START_ADDRESS
#endif /*HAS_BOOTLOADER*/

extern const FlashConfig_t FlashConfig;
const extern FlashSectorConfig_t FlashSectorConfig[];

uint32_t flash_get_sector_cnt(void);

#endif /* FLASH_CONFIG_GENERAL_H  */
