#include "back_count_config.h"

#include "data_utils.h"

const BackCountConfig_t BackCountConfig[] = {
    {
        .time_out_ms = 500,
        .num = BACK_COUNT_WIFI_AP,
        .count = 0,
        .valid = true,
        .name = "WiFiAcIndication",
    },
};

BackCountHandle_t BackCountInstance[] = {
    {
        .num = BACK_COUNT_WIFI_AP,
        .valid = true,
    },
};

COMPONENT_GET_CNT(BackCount, back_count)


