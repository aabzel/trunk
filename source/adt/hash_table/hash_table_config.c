#include "hash_table_config.h"

#include "data_utils.h"

static HashTableCell_t Memory1[6 * 4];
static HashTableCell_t Memory2[200];

const HashTableConfig_t HashTableConfig[] = {
    {
        .num = 1,
        .valid = true,
        .size = ARRAY_SIZE(Memory1),
        .Memory = Memory1,
        .name = "HASH_TABLE1",
    },

    {
        .num = 2,
        .valid = true,
        .size = ARRAY_SIZE(Memory2),
        .Memory = Memory2,
        .name = "HASH_TABLE2",
    },
};

HashTableHandle_t HashTableInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },

};

uint32_t hash_table_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(HashTableConfig);
    cnt2 = ARRAY_SIZE(HashTableInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
