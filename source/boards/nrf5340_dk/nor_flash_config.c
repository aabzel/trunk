#include "nor_flash_config.h"

#include <stdbool.h>
#include <stddef.h>

#include "data_utils.h"

#ifdef HAS_FLASH_ON_CHIP
#include "nrf5340_app_const.h"
#endif

#ifdef HAS_FLASH_OFF_CHIP
#include "mx25r6435f_const.h"
#endif

const NorFlashConfig_t NorFlashConfig[] = {
    {
        .num = 1,
        .name = "SwNORFlash",
        .start = 0,
        .size = 512,
        .valid = true,
        .option = NOR_FLASH_OPTION_SW,
    },

#ifdef HAS_FLASH_ON_CHIP
    {
        .num = 2,
        .name = "On-ChipNORFlash",
        .start = ROM_START,
        .size = ROM_SIZE,
        .valid = true,
        .option = NOR_FLASH_OPTION_ON_CHIP,
    },
#endif

#ifdef HAS_FLASH_OFF_CHIP
    {
        .num = 3,
        .name = "SPI-NORFlash",
        .start = 0,
        .size = MX25R6435F_FLASH_SIZE,
        .option = NOR_FLASH_OPTION_OFF_CHIP,
        .valid = true,
    },
#endif
};

NorFlashItem_t NorFlashItem[] = {{
                                     .num = 1,
                                     .init = false,
                                     .valid = true,
                                 },

#ifdef HAS_FLASH_ON_CHIP
                                 {
                                     .num = 2,
                                     .valid = true,
                                     .init = false,
                                 },
#endif /*HAS_FLASH_ON_CHIP*/

#ifdef HAS_FLASH_OFF_CHIP
                                 {
                                     .num = 3,
                                     .init = false,
                                     .valid = true,
                                 }
#endif /*HAS_FLASH_OFF_CHIP*/
};

uint32_t nor_flash_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(NorFlashItem);
    cnt2 = ARRAY_SIZE(NorFlashConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
