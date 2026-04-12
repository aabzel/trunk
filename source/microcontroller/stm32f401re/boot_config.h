#ifndef BOOT_CONFIG_H
#define BOOT_CONFIG_H


#ifdef HAS_BOOTLOADER
#define FLASH_PAGE_BOOT_CNT APP_PAGE_START
#endif

#include "boot_types.h"

extern const BootConfig_t BootConfig[];
extern BootHandle_t BootInstance[] ;

#ifdef HAS_FLASH_NVS
#define APP_PAGE_CNT (FLASH_PAGE_CNT-FLASH_PAGE_BOOT_CNT-NVS_SIZE_PAGES-1)
#endif

uint32_t boot_get_cnt(void);

#endif /* BOOT_CONFIG_H */
