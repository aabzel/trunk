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
/*
it separates 2 blocks, each block includes 256 sectors, each sector is 2 KB
0x0000_0000	0x0007_FFFF
0x0008_0000	0x000F_FFFF
0x0010_0000	0x0013_FFFF

0x00000000	0x0007FFFF
0x00080000	0x000FFFFF
0x00100000	0x0013FFFF
*/
const FlashSectorConfig_t FlashSectorConfig[] = {
    {
        .sector = 0,
        .start = 0x00000000,
        .size = 512 * K_BYTES,
        .content = MEM_CONTENT_GENERIC_APP,
    },
    {
        .sector = 1,
        .start = 0x00080000,
        .size = 512 * K_BYTES,
        .content = MEM_CONTENT_GENERIC_APP,
    },
    {
        .sector = 2,
        .start = 0x00100000,
        .size = 256 * K_BYTES,
        .content = MEM_CONTENT_GENERIC_APP,
    },

};

uint32_t flash_get_sector_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(FlashSectorConfig);
    return cnt;
}
