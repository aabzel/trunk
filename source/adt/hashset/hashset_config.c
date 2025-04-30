#include "hashset_config.h"

#include "data_utils.h"

static HashSetEntry_t XmlHSHeap[100];

HashSet_t HashSetInstance = {
    .err_cnt = 0,
    .size = ARRAY_SIZE(XmlHSHeap),
    .cnt = 0,
    .heap = XmlHSHeap,
    .init_done = true,
};
