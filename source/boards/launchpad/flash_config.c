#include "flash_config.h"

#ifndef HAS_FLASH
#error "Add HAS_FLASH"
#endif /*HAS_FLASH*/

#include "data_utils.h"
//#include "flash_cc26x2_types.h"
#include "macro_utils.h"

FlashItem_t FlashItem = {0};

const FlashConfig_t FlashConfig = {
    .boot_start = BOOT_START_ADDRESS,
    .app_start = APP_START_ADDRESS,
};

const FlashSectorConfig_t FlashSectorConfig[] = {
    {  .sector = 0,  .start = 0,               .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,    },
    {  .sector = 1,  .start = 1* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,    },
    {  .sector = 2,  .start = 2* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,    },
    {  .sector = 3,  .start = 3* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,    },
    {  .sector = 4,  .start = 4* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,    },
    {  .sector = 5,  .start = 5* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,    },
    {  .sector = 6,  .start = 6* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,    },
    {  .sector = 7,  .start = 7* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,    },
    {  .sector = 8,  .start = 8* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,    },
    {  .sector = 9,  .start = 9* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,    },
    {  .sector = 10, .start = 10* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,    },
    {  .sector = 11, .start = 11* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,  },
    {  .sector = 12, .start = 12* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,  },
    {  .sector = 13, .start = 13* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,  },
    {  .sector = 14, .start = 14* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,  },
    {  .sector = 15, .start = 15* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,  },
    {  .sector = 16, .start = 16* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,  },
    {  .sector = 17, .start = 17* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,  },
    {  .sector = 18, .start = 18* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,  },
    {  .sector = 19, .start = 19* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,  },
    {  .sector = 20, .start = 20* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_BOOTLADER,  },
    {  .sector = 21, .start = 21* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 22, .start = 22* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 23, .start = 23* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 24, .start = 24* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 25, .start = 25* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 26, .start = 26* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 27, .start = 27* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 28, .start = 28* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 29, .start = 29* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 30, .start = 30* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 31, .start = 31* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 32, .start = 32* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 33, .start = 33* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 34, .start = 34* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 35, .start = 35* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 36, .start = 36* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 37, .start = 37* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 38, .start = 38* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 39, .start = 39* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_GENERIC,  },
    {  .sector = 40, .start = 40* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_FLASH_FS_PAGE1,  },
    {  .sector = 41, .start = 41* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_FLASH_FS_PAGE1,  },
    {  .sector = 42, .start = 42* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_FLASH_FS_PAGE2,  },
    {  .sector = 43, .start = 43* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_FLASH_FS_PAGE2,  },
    {  .sector = 44, .start = 44* 8 * K_BYTES,  .size = 8 * K_BYTES,  .content = MEM_CONTENT_CONFIG,  },
};

uint32_t flash_get_sector_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(FlashSectorConfig);
    return cnt;
}
