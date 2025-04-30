#include "nor_flash_config.h"


#include "std_includes.h"
#include "data_utils.h"
#include "microcontroller_const.h"


const NorFlashConfig_t NorFlashConfig[] = {
    {
        .num = 1,
        .name = "SpiNOR-Flash",
        .option = NOR_FLASH_OPTION_OFF_CHIP,
        .start = EXT_ROM_START,
        .size = EXT_ROM_SIZE,
        .valid = true,
        .CustomInit = NULL,
        .memory = NULL, /*Ptr to array*/
    },

    {
        .num = 2,
        .name = "EEPROM",
        .option = NOR_FLASH_OPTION_ON_CHIP,
        .start =ROM_START,
        .size = ROM_SIZE,
        .valid = true,
        .CustomInit = NULL,
        .memory = NULL,
    },
};

NorFlashItem_t NorFlashItem[] = {
    {        .num = 1,        .init = false,        .valid = true,    },
    {        .num = 2,        .init = false,        .valid = true,    },
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
