#include "hist_filter_config.h"

#include "data_utils.h"

#define HIST_FILTER_HIST 5.0

const HistFilterConfig_t HistFilterConfig[] = {
    {
        .num = 1,
        .valid = true,
        .SchmittTriggerShortConfig = {
                { .num=0, .up_val=0.0, .down_val=1.0, .hysteresis=HIST_FILTER_HIST, .switching_value=12.5,},
                { .num=1, .up_val=1.0, .down_val=2.0, .hysteresis=HIST_FILTER_HIST, .switching_value=37.5,},
                { .num=2, .up_val=2.0, .down_val=3.0, .hysteresis=HIST_FILTER_HIST, .switching_value=62.5,},
                { .num=3, .up_val=3.0, .down_val=4.0, .hysteresis=HIST_FILTER_HIST, .switching_value=87.5,},
        },
        .name = "HistFilter1",
    },
};

HistFilterHandle_t HistFilterInstance[] = {
    { .num = 1, .valid = true, },

};

COMPONENT_GET_CNT(HistFilter, hist_filter)
