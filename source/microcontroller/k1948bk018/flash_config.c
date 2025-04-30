#include "flash_config.h"

#ifndef HAS_FLASH
#error "Add HAS_FLASH"
#endif /*HAS_FLASH*/

#include "data_utils.h"
#include "flash_types.h"
#include "macro_utils.h"
#include "sys_config.h"

FlashHandle_t FlashInstance = {0};

const FlashSectorConfig_t FlashSectorConfig[] = {
    {
        .sector = 0,
        .start = ROM_START,
        .size = ROM_SIZE,
        .content = MEM_CONTENT_GENERIC_APP,
    },
    {
        .sector = 0,
        .start = EXT_ROM_START,
        .size = EXT_ROM_SIZE,
        .content = MEM_CONTENT_GENERIC_APP,
    },
};

uint32_t flash_get_sector_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(FlashSectorConfig);
    return cnt;
}

const FlashConfig_t FlashConfig = {
#ifdef HAS_BOOTLOADER
    .boot_start = BOOT_START_ADDRESS,
#endif
    .app_start = EXT_ROM_START,
    .page_size = (4 * K_BYTES), // W25Q32JVSSIQ  sector size
    .size = EXT_ROM_SIZE,
    .interrupt_on = false,
    .is_equal_sectors = true,
    .page_cnt = ARRAY_SIZE(FlashSectorConfig),
    .PageArray =(   FlashSectorConfig_t*) FlashSectorConfig,
    .start = ROM_START,
};
