#include "flash_config.h"

#ifndef HAS_FLASH
#error "Add HAS_FLASH"
#endif /*HAS_FLASH*/

#include "data_utils.h"
#include "flash_types.h"
#include "macro_utils.h"
#include "sys_config.h"

FlashHandle_t FlashInstance = {0};

const FlashConfig_t FlashConfig = {
#ifdef HAS_BOOTLOADER
    .boot_start = BOOT_START_ADDRESS,
#endif
    .app_start = APP_START_ADDRESS,
    .start = ROM_START,
    .end = ROM_END,
    .page_size = FLASH_PAGE_SIZE,
};

// hex(0x08000000+252*1024)   = 0x803f000
// hex(0x0803F800-2*1024)  = 0x803f000
// logical sector
const FlashSectorConfig_t FlashSectorConfig[] = {
    {
        .sector = 0,
        .start = 0x08000000,
        .size = 252 * K_BYTES,
        .content = MEM_CONTENT_GENERIC_APP,
    },
    {
        .sector = 2,
        .start = 0x0803f000,
        .size = 2 * K_BYTES,
        .content = MEM_CONTENT_FLASH_FS_PAGE1,
    },
    {
        .sector = 2,
        .start = 0x0803f800,
        .size = 2 * K_BYTES,
        .content = MEM_CONTENT_FLASH_FS_PAGE2,
    },

};

uint32_t flash_get_sector_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(FlashSectorConfig);
    return cnt;
}
