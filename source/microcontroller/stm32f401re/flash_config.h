#ifndef FLASH_CONFIG_GENERAL_H
#define FLASH_CONFIG_GENERAL_H

#include <stdbool.h>
#include <stdint.h>

#include "flash_types.h"
#include "flash_custom_types.h"

#ifndef HAS_FLASH
#error "Add HAS_FLASHER"
#endif /*HAS_FLASHER*/

#define NOR_FLASH_BASE   0x08000000
#define	FILE_SYS_START  (0x08008000)
#define FILE_SYS_SIZE   (2*16*1024)
#define BOOT_START_ADDRESS 0x08060000
#define APP_START_ADDRESS 0x08010000
#define APP_SIZE ((2*128+64)*K_BYTES)

#define NOR_FLASH_END (ROM_START+ROM_SIZE)

extern FlashHandle_t FlashInstance;
extern const FlashConfig_t FlashConfig;
const extern FlashSectorConfig_t FlashSectorConfig[];

uint32_t flash_get_sector_cnt(void);

#endif /* FLASH_CONFIG_GENERAL_H  */
