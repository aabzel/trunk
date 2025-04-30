#ifndef FLASH_CONFIG_H
#define FLASH_CONFIG_H

#include "std_includes.h"
#include "flash_types.h"
#include "microcontroller_const.h"

#ifndef HAS_FLASH
#error "Add HAS_FLASHER"
#endif /*HAS_FLASHER*/

#define NOR_FLASH_BASE ROM_START

#ifndef MBR_START_ADDRESS
#define MBR_START_ADDRESS NOR_FLASH_BASE
#endif

#define BOOT_START_ADDRESS NOR_FLASH_BASE

#ifdef HAS_GENERIC_MONOLITHIC
#define APP_START_ADDRESS NOR_FLASH_BASE
#else
#define APP_START_ADDRESS ROM_START
#endif

#define APP_SIZE ROM_SIZE

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
