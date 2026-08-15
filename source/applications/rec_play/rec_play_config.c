#include "rec_play_config.h"

#include "data_utils.h"

const RecPlayConfig_t RecPlayConfig[] = {
    {
        .num = 1,
        .rec_num = 1,
        .wm8731_num = 1,
        .play_num = 1,
        .valid = true,
        .name = "RecPlay",
    },
};

RecPlayHandle_t RecPlayInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(RecPlay, rec_play)


