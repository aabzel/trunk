#include "nvs_config.h"

#include "data_utils.h"
#include "microcontroller_const.h"

#define DFLASH_HALF_SIZE (DFLASH_SIZE/2)

const NvsConfig_t NvsConfig[] = {
    {
        .num = 1,
        .valid = true,
        .name = "main",
        .start = DFLASH_START,
        .size = DFLASH_HALF_SIZE,
        .sector_size = DFLASH_ERASE_SECTOR_SIZE ,
    },

    {
        .num = 2,
        .valid = true,
        .name = "reserved",
        .start = DFLASH_START+DFLASH_HALF_SIZE,
        .size = DFLASH_HALF_SIZE,
        .sector_size = DFLASH_ERASE_SECTOR_SIZE ,
    },
};


NvsHandle_t NvsInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },

};

uint32_t nvs_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(NvsConfig);
    cnt2 = ARRAY_SIZE(NvsInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
