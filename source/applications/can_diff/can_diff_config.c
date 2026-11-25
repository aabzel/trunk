#include "can_diff_config.h"

#include "data_utils.h"

const CanDiffConfig_t CanDiffConfig[] = {
    {
        .num = 1,
        .can_num = 1,
        .can_id = 0xC2,
        .id_type = CAN_FRAME_ID_EXTENDED,
        .name = "ID:0xC2",
        .valid = true,
    },

    {
        .num = 2,
        .can_num = 2,
        .can_id = 0xC2,
        .id_type = CAN_FRAME_ID_EXTENDED,
        .valid = true,
        .name = "ID:0xC2",
    },
};

CanDiffHandle_t CanDiffInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },
    {
        .num = 3,
        .valid = true,
    },
    {
        .num = 4,
        .valid = true,
    },
    {
        .num = 5,
        .valid = true,
    },
};

uint32_t can_diff_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(CanDiffConfig);
    cnt2 = ARRAY_SIZE(CanDiffInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}

uint32_t can_diff_inst_get_cnt(void) {
    uint8_t cnt2 = 0;
    cnt2 = ARRAY_SIZE(CanDiffInstance);
    return cnt2;
}
