#ifndef FLASH_CONFIG_H
#define FLASH_CONFIG_H

#include "std_includes.h"
#include "flash_types.h"

#ifndef HAS_FLASH
#error "Add HAS_FLASHER"
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#define NOR_FLASH_BASE 0x08000000
#ifndef MBR_START_ADDRESS
#define MBR_START_ADDRESS NOR_FLASH_BASE
#endif

#ifndef BOOT_START_ADDRESS
#define BOOT_START_ADDRESS NOR_FLASH_BASE
#endif

#ifndef APP_START_ADDRESS
#define APP_START_ADDRESS NOR_FLASH_BASE
#endif

#define APP_SIZE (832 * K_BYTES)

#ifdef HAS_GENERIC
#define FW_START_ADDRESS APP_START_ADDRESS
#endif

#ifdef HAS_MBR
#define FW_START_ADDRESS NOR_FLASH_BASE
#endif

#ifdef HAS_BOOTLOADER
#define FW_START_ADDRESS BOOT_START_ADDRESS
#endif

extern FlashHandle_t FlashInstance;
extern const FlashConfig_t FlashConfig;
extern const MemoryConfig_t FlashSectorConfig[];
extern const MemoryConfig_t RamSectorConfig[];

uint32_t flash_get_sector_cnt(void);
uint32_t ram_get_sector_cnt(void) ;

#endif /* FLASH_CONFIG_H  */
