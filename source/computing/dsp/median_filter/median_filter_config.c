#include "median_filter_config.h"

#include "data_utils.h"

#define MEDIAN_FILTER_ORDER 3
static float memorySort[MEDIAN_FILTER_ORDER + 1] = {0};
static float memoryX[MEDIAN_FILTER_ORDER + 1] = {0};

static float memory2Sort[2 + 1] = {0};
static float memory2[2 + 1] = {0};

static float memory3Sort[3 + 1] = {0};
static float memory3[3 + 1] = {0};

static float memory5Sort[5 + 1] = {0};
static float memory5[5 + 1] = {0};

static float memory6Sort[6 + 1] = {0};
static float memory6[6 + 1] = {0};

const MedianFilterConfig_t MedianFilterConfig[] = {
    {
        .num = 1,
        .sample_rate_hz = 10,
        .valid = true,
        .name = "MedianFilter",
        .size = MEDIAN_FILTER_ORDER,
        .x = memoryX,
        .temp = memorySort,
        .max_size = MEDIAN_FILTER_ORDER,
    },
    {
        .num = 2,
        .sample_rate_hz = 10,
        .valid = true,
        .name = "MedianFilter2",
        .size = 2,
        .x = memory2,
        .temp = memory2Sort,
        .max_size = 2,
    },
    {
        .num = 3,
        .sample_rate_hz = 10,
        .valid = true,
        .name = "MedianFilter3",
        .size = 3,
        .x = memory3,
        .temp = memory3Sort,
        .max_size = 3,
    },

    {
        .num = 4,
        .sample_rate_hz = 10,
        .valid = true,
        .name = "MedianFilter4",
        .size = 6,
        .x = memory6,
        .temp = memory6Sort,
        .max_size = 6,
    },

    {
        .num = 5,
        .sample_rate_hz = 10,
        .valid = true,
        .name = "MedianFilter5",
        .size = 5,
        .x = memory5,
        .temp = memory5Sort,
        .max_size = 5,
    },
};

MedianFilterHandle_t MedianFilterInstance[] = {
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

uint32_t median_filter_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(MedianFilterConfig);
    uint32_t cnt_ints = ARRAY_SIZE(MedianFilterInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
