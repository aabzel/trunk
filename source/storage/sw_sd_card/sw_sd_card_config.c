#include "sw_sd_card_config.h"

#include "data_utils.h"

static uint8_t FlashMemory[DISK_SECTOR_SIZE * DISK_SECTOR_CNT] = {0};

const SwSdCardConfig_t SwSdCardConfig[] = {
    {
        .num = 0,
        .buff = FlashMemory,
        .size = sizeof(FlashMemory),
        .block_size = 512,
        .valid = true,
        .name = "SW_SD_CARD1",
    },
};

SwSdCardHandle_t SwSdCardInstance[] = {
    {
        .num = 0,
        .valid = true,
    },
};

uint32_t sw_sd_card_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(SwSdCardConfig);
    cnt2 = ARRAY_SIZE(SwSdCardInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
