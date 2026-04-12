#include "min_heap_config.h"

#include "data_utils.h"

static int32_t data1[100] = {0};
static int32_t data2[100] = {0};

const BinHeapConfig_t MinHeapConfig[] = {
    {
        .num = 1,
        .array = data1,
        .capacity = ARRAY_SIZE(data1),
        .valid = true,
        .name = "MIN_HEAP1",
    },

    {
        .num = 2,
        .array = data2,
        .capacity = ARRAY_SIZE(data2),
        .valid = true,
        .name = "MIN_HEAP2",
    },
};

BinHeapHandle_t MinHeapInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },

};

uint32_t min_heap_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(MinHeapConfig);
    cnt2 = ARRAY_SIZE(MinHeapInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
