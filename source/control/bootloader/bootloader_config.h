#ifndef BOOTLOADER_CONFIG_H
#define BOOTLOADER_CONFIG_H


#include "bootloader_types.h"

#ifdef HAS_FLASH
#include "flash_mcal.h"
#endif

#if 0
#ifdef HAS_FLASH_NVS
#include "flash_nvs_const.h"
#endif /*HAS_FLASH_NVS*/

#ifdef CC26XX
#define APP_PAGE_START (APP_START_ADDRESS/FLASH_SECTOR_SIZE)
#endif

#ifdef HAS_BOOTLOADER
#define FLASH_PAGE_BOOTLOADER_CNT APP_PAGE_START
#endif

#ifdef HAS_FLASH_NVS
#define APP_PAGE_CNT (FLASH_PAGE_CNT-FLASH_PAGE_BOOTLOADER_CNT-NVS_SIZE_PAGES-1)
#endif /*HAS_FLASH_NVS*/

#endif

extern const BootLoaderConfig_t BootLoaderConfig;

extern BootLoaderHandler_t BootLoaderInstance;



#endif /* BOOTLOADER_CONFIG_H */
