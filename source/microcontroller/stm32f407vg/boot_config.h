#ifndef BOOT_CFG_H
#define BOOT_CFG_H


#ifdef HAS_BOOTLOADER
#define FLASH_PAGE_BOOT_CNT APP_PAGE_START
#endif

#include "boot_types.h"

extern BootConfig_t BootConfig;

#ifdef HAS_FLASH_NVS
#define APP_PAGE_CNT (FLASH_PAGE_CNT-FLASH_PAGE_BOOT_CNT-NVS_SIZE_PAGES-1)
#endif /*HAS_FLASH_NVS*/



#endif /* BOOT_CFG_H */
