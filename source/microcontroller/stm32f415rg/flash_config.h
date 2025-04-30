#ifndef FLASH_CONFIG_GENERAL_H
#define FLASH_CONFIG_GENERAL_H

#include <stdbool.h>
#include <stdint.h>

#include "flash_custom_types.h"
#include "flash_types.h"

#ifndef HAS_FLASH
#error "Add HAS_FLASH"
#endif /*HAS_FLASHER*/

#define NOR_FLASH_BASE ROM_START

#ifdef HAS_GENERIC_MONOLITHIC
#include "flash_config_monolithic.h"
#else /*HAS_GENERIC_MONOLITHIC*/

#ifndef MBR_START_ADDRESS
#define MBR_START_ADDRESS NOR_FLASH_BASE
#endif /*MBR_START_ADDRESS*/

#define FILE_SYS_START (0x08004000)
#define FILE_SYS_SIZE (2 * 16 * 1024)
#define BOOT_START_ADDRESS 0x080E0000
#define APP_START_ADDRESS 0x0800C000
#define APP_SIZE (848 * K_BYTES)

#ifdef HAS_BOOTLOADER
#define FW_START_ADDRESS BOOT_START_ADDRESS
#endif /*HAS_BOOTLOADER*/

#ifdef HAS_MBR
#define FW_START_ADDRESS MBR_START_ADDRESS
#endif /*HAS_MBR*/

#ifdef HAS_GENERIC
#define FW_START_ADDRESS APP_START_ADDRESS
#endif /*HAS_GENERIC*/

#endif /*HAS_GENERIC_MONOLITHIC*/

extern FlashHandle_t FlashInstance;
extern const FlashConfig_t FlashConfig;
const extern FlashSectorConfig_t FlashSectorConfig[];

uint32_t flash_get_sector_cnt(void);

#endif /* FLASH_CONFIG_GENERAL_H  */
