#ifndef FLASH_CONFIG_H
#define FLASH_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "flash_types.h"

#ifndef HAS_FLASH
#error "Add HAS_FLASHER"
#endif /*HAS_FLASHER*/

#define NOR_FLASH_BASE 0x08000000
#ifndef MBR_START_ADDRESS
#define MBR_START_ADDRESS NOR_FLASH_BASE
#endif
#define BOOT_START_ADDRESS 0x080E0000
#define APP_START_ADDRESS 0x08010000
#define APP_SIZE (832 * K_BYTES)

#ifdef HAS_GENERIC
#define FW_START_ADDRESS APP_START_ADDRESS
#endif

#ifdef HAS_MBR
#define FW_START_ADDRESS NOR_FLASH_BASE
#endif /*HAS_MBR*/

#ifdef HAS_BOOTLOADER
#define FW_START_ADDRESS BOOT_START_ADDRESS
#endif /*HAS_BOOTLOADER*/

extern FlashHandle_t FlashInstance;
extern const FlashConfig_t FlashConfig;
extern const FlashSectorConfig_t FlashSectorConfig[];

uint32_t flash_get_sector_cnt(void);

#endif /* FLASH_CONFIG_H  */
