#include "flash_config.h"

#ifndef HAS_FLASH
#error "Add HAS_FLASH"
#endif /*HAS_FLASH*/

#include "data_utils.h"
#include "flash_types.h"
#include "macro_utils.h"

FlashHandle_t FlashInstance = {0};

const FlashSectorConfig_t FlashSectorConfig[] = {
    {
        .sector = 0,
        .start = 0x08000000,
        .size = 16 * K_BYTES,
        .content = MEM_CONTENT_MBR,
    },
    {
        .sector = 1,
        .start = 0x08004000,
        .size = 16 * K_BYTES,
        .content = MEM_CONTENT_MBR,
    },
    {
        .sector = 2,
        .start = 0x08008000,
        .size = 16 * K_BYTES,
        .content = MEM_CONTENT_FLASH_FS_PAGE1,
    },
    {
        .sector = 3,
        .start = 0x0800C000,
        .size = 16 * K_BYTES,
        .content = MEM_CONTENT_FLASH_FS_PAGE2,
    },
    {
        .sector = 4,
        .start = 0x08010000,
        .size = 64 * K_BYTES,
        .content = MEM_CONTENT_GENERIC,
    },
    {
        .sector = 5,
        .start = 0x08020000,
        .size = 128 * K_BYTES,
        .content = MEM_CONTENT_GENERIC,
    },
    {
        .sector = 6,
        .start = 0x08040000,
        .size = 128 * K_BYTES,
        .content = MEM_CONTENT_GENERIC,
    },
    {
        .sector = 7,
        .start = 0x08060000,
        .size = 128 * K_BYTES,
        .content = MEM_CONTENT_BOOTLADER,
    },
};

const FlashConfig_t FlashConfig = {
    .boot_start = BOOT_START_ADDRESS,
    .app_start = APP_START_ADDRESS,
    .start = ROM_START,
    .end = ROM_END,
    .size = ROM_SIZE,
    .PageArray = FlashSectorConfig,
    .page_cnt= ARRAY_SIZE(FlashSectorConfig),
    .page_size = 16* K_BYTES,
    .is_equal_sectors = false,
};

uint32_t flash_get_sector_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(FlashSectorConfig);
    return cnt;
}
