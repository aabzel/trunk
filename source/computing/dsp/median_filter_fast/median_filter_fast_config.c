#include "median_filter_fast_config.h"

#include "data_utils.h"

#define MEDIAN_FILTER_FAST_ORDER 5
static int32_t memoryX[MEDIAN_FILTER_FAST_ORDER + 1] = {0};

#define MEDIAN_FILTER_BIN_HEAP_SIZE (MEDIAN_FILTER_FAST_ORDER * 3)

static int32_t memoryHeapLarge[MEDIAN_FILTER_BIN_HEAP_SIZE] = {0};
static int32_t memoryHeapSmall[MEDIAN_FILTER_BIN_HEAP_SIZE] = {0};
// static HashTableCell_t ToDeleteMemory[MEDIAN_FILTER_FAST_ORDER * 3] = {0};

static int32_t memory2X[2 + 1] = {0};
static int32_t memory2HeapLarge[2 * 3] = {0};
static int32_t memory2HeapSmall[2 * 3] = {0};
/// static HashTableCell_t ToDeleteMemory2[2 * 3] = {0};

static int32_t memory3X[3 + 1] = {0};
static int32_t memory3HeapLarge[3 * 3] = {0};
static int32_t memory3HeapSmall[3 * 3] = {0};
// static HashTableCell_t ToDeleteMemory3[3 * 3] = {0};

static int32_t memory6X[6 + 1] = {0};
static int32_t memory6HeapLarge[6 * 10] = {0};
static int32_t memory6HeapSmall[6 * 10] = {0};
// static HashTableCell_t ToDeleteMemory6[6 * 100] = {0};

static int32_t memory5X[5 + 1] = {0};
static int32_t memory5HeapLarge[5 * 10] = {0};
static int32_t memory5HeapSmall[5 * 10] = {0};
// static HashTableCell_t ToDeleteMemory5[5 * 100] = {0};

const MedianFilterFastConfig_t MedianFilterFastConfig[] = {
    {
        .num = 1,
        .size = MEDIAN_FILTER_FAST_ORDER,
        .sample_rate_hz = 10,
        .valid = true,
        .name = "MedianFilterFast",
        .x = memoryX, /*for cyclic buffer */
        .bin_heap_size = ARRAY_SIZE(memoryHeapLarge),
        .tempLarge = memoryHeapLarge,
        .tempSmall = memoryHeapSmall,
        //    .HashTableMemory = ToDeleteMemory,
        //   .hash_table_size = ARRAY_SIZE(ToDeleteMemory),
        .max_size = MEDIAN_FILTER_FAST_ORDER,

    },
    {
        .num = 2,
        .size = 2,
        .sample_rate_hz = 10,
        .valid = true,
        .name = "MedianFilterFast_k_2",
        .x = memory2X, /*for cyclic buffer */
        .bin_heap_size = ARRAY_SIZE(memory2HeapLarge),
        .tempLarge = memory2HeapLarge,
        .tempSmall = memory2HeapSmall,
        //  .HashTableMemory = ToDeleteMemory2,
        //  .hash_table_size = ARRAY_SIZE(ToDeleteMemory2),
        .max_size = 2,
    },

    {
        .num = 3,
        .size = 3,
        .sample_rate_hz = 10,
        .valid = true,
        .name = "MedianFilterFast_k_3",
        .x = memory3X, /*for cyclic buffer */
        .bin_heap_size = ARRAY_SIZE(memory3HeapLarge),
        .tempLarge = memory3HeapLarge,
        .tempSmall = memory3HeapSmall,
        //  .HashTableMemory = ToDeleteMemory3,
        //  .hash_table_size = ARRAY_SIZE(ToDeleteMemory3),
        .max_size = 3,
    },

    {
        .num = 4,
        .size = 6,
        .sample_rate_hz = 10,
        .valid = true,
        .name = "MedianFilterFast_k_6",
        .x = memory6X, /*for cyclic buffer */
        .bin_heap_size = ARRAY_SIZE(memory6HeapLarge),
        .tempLarge = memory6HeapLarge,
        .tempSmall = memory6HeapSmall,
        //  .HashTableMemory = ToDeleteMemory6,
        //  .hash_table_size = ARRAY_SIZE(ToDeleteMemory6),
        .max_size = 6,
    },

    {
        .num = 5,
        .size = 5,
        .sample_rate_hz = 10,
        .valid = true,
        .name = "MedianFilterFast_k_5",
        .x = memory5X, /*for cyclic buffer */
        .bin_heap_size = ARRAY_SIZE(memory5HeapLarge),
        .tempLarge = memory5HeapLarge,
        .tempSmall = memory5HeapSmall,
        //   .HashTableMemory = ToDeleteMemory5,
        //   .hash_table_size = ARRAY_SIZE(ToDeleteMemory5),
        .max_size = 5,
    },
};

MedianFilterFastHandle_t MedianFilterFastInstance[] = {
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

uint32_t median_filter_fast_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(MedianFilterFastConfig);
    uint32_t cnt_ints = ARRAY_SIZE(MedianFilterFastInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
