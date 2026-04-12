#include "hash_table_s8_config.h"

#include "data_utils.h"

const HashTableS8Config_t HashTableS8Config[] = {
    {
        .num = 1,
        .valid = true,
        .name = "HASH_TABLE_S81",
    },

    {
        .num = 2,
        .valid = true,
        .name = "HASH_TABLE_S82",
    },
};

HashTableS8Handle_t HashTableS8Instance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },

};

uint8_t hash_table_s8_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(HashTableS8Config);
    cnt2 = ARRAY_SIZE(HashTableS8Instance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
