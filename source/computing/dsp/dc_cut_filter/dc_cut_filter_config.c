#include "dc_cut_filter_config.h"

#include "data_utils.h"

const DcCutFilterConfig_t DcCutFilterConfig[] = {
    { .num = 1, .alfa = 0.95f, .valid = true, .name = "DcCutFILT2",    },
    { .num = 2, .alfa = 0.75f, .valid = true, .name = "DcCutFILT1",    },
};

DcCutFilterHandle_t DcCutFilterInstance[] = {
    { .num = 1, .valid = true, },
    { .num = 2, .valid = true, },
};

COMPONENT_GET_CNT(DcCutFilter, dc_cut_filter)


