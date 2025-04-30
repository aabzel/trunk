#ifndef FLASH_CONFIG_GENERAL_H
#define FLASH_CONFIG_GENERAL_H

#include <stdbool.h>
#include <stdint.h>

#include "flash_types.h"

#ifndef HAS_FLASH_CUSTOM
#include "flash_custom_types.h"
#endif /*HAS_FLASH_CUSTOM*/

#include "sys_config.h"

#ifndef HAS_FLASH
#error "+ HAS_FLASH"
#endif /*HAS_FLASH*/

#ifndef MBR_START_ADDRESS
#define MBR_START_ADDRESS NOR_FLASH_BASE
#endif
#define	FILE_SYS_START  (0x08008000)
#define FILE_SYS_SIZE   (2*16*1024)
#define BOOT_START_ADDRESS 0x08160000
#define APP_START_ADDRESS 0x08010000

#define APP_SIZE (1360*K_BYTES)

#ifdef HAS_MBR
#define FW_START_ADDRESS MBR_START_ADDRESS
#endif /*HAS_MBR*/

#ifdef HAS_GENERIC
#define FW_START_ADDRESS APP_START_ADDRESS
#endif /*HAS_GENERIC*/

#ifdef HAS_BOOTLOADER
#define FW_START_ADDRESS BOOT_START_ADDRESS
#endif /*HAS_BOOTLOADER*/

extern FlashItem_t FlashItem;
extern const FlashConfig_t FlashConfig;
const extern FlashSectorConfig_t FlashSectorConfig[];

uint32_t flash_get_sector_cnt(void);

#endif /* FLASH_CONFIG_GENERAL_H  */
