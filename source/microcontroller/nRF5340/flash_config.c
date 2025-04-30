#include "flash_config.h"

#ifndef HAS_FLASH
#error "Add HAS_FLASH"
#endif /*HAS_FLASH*/

#include "data_utils.h"
#include "macro_utils.h"

#ifdef HAS_FLASH_CUSTOM
#include "flash_custom_types.h"
#endif
#include "nrf5340_const.h"

FlashHandle_t FlashInstance = {0};

const FlashConfig_t FlashConfig = {
    .boot_start= APP_START_ADDRESS,
    .app_start = APP_START_ADDRESS,
};

const FlashSectorConfig_t FlashSectorConfig[]= {
    {.sector=1 , .start=FLASH_START_APP_CORE,     .size = FLASH_SIZE_APP_CORE,  .content=MEM_CONTENT_GENERIC_APP,},
    {.sector=2 , .start=FLASH_START_NET_CORE,     .size = FLASH_SIZE_NET_CORE,  .content=MEM_CONTENT_GENERIC_NET,},
    {.sector=3 , .start=0x000fc000,     .size = 8*K_BYTES,  .content=MEM_CONTENT_FLASH_FS_PAGE1,},
    {.sector=4 , .start=0x000fe000,     .size = 8*K_BYTES,  .content=MEM_CONTENT_FLASH_FS_PAGE2,},
};

uint32_t flash_get_sector_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(FlashSectorConfig);
    return cnt;
}
