#ifndef FLASH_CONFIG_H
#define FLASH_CONFIG_H

#include "std_includes.h"
#include "flash_types.h"

#ifndef HAS_FLASH
#error "Add HAS_FLASHER"
#endif

#ifndef NOR_FLASH_BASE
#define NOR_FLASH_BASE ROM_START
#endif

#ifndef MBR_START_ADDRESS
#define MBR_START_ADDRESS NOR_FLASH_BASE
#endif


//#define APP_START_ADDRESS 0x08010000
#define APP_MAX_SIZE (320 * K_BYTES) //64+2*128=320

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
