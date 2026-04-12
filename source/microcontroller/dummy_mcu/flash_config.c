#include "flash_config.h"

#ifndef HAS_FLASH
#error "Add HAS_FLASH"
#endif /*HAS_FLASH*/

#include "flash_types.h"
#include "macro_utils.h"
#include "sys_config.h"

#ifdef HAS_DATA_MISC
#include "data_utils.h"
#endif


FlashHandle_t FlashInstance = {0};

const MemoryConfig_t FlashSectorConfig[] = {
};

const FlashConfig_t FlashConfig = {
#ifdef HAS_BOOTLOADER
 .boot_start = BOOT_START_ADDRESS,
#endif
 .app_start = APP_START_ADDRESS,
 .start = ROM_START,
#ifdef  HAS_FLASH_CUSTOM
 .page_size = FLASH_PAGE_SIZE,
#endif
 .is_equal_sectors = true,
 .interrupt_on =false,
 .size=8*1024*1024,
 .PageArray= (MemoryConfig_t*) FlashSectorConfig,
 .page_cnt=ARRAY_SIZE(FlashSectorConfig),
};




const MemoryConfig_t RamSectorConfig[] = {
};



uint32_t ram_get_sector_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(RamSectorConfig);
    return cnt;
}

uint32_t flash_get_sector_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(FlashSectorConfig);
    return cnt;
}
