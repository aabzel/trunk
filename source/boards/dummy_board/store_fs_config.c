#include "store_fs_config.h"

#include "data_utils.h"

const StoreFsConfig_t StoreFsConfig[] = {
    {
        .num = 1,
        .valid = true,
        .fs_num = 1,
        .storage_type = STORAGE_TYPE_LITTLE_FS,
        .name = "StoreFs1",
    },
};

StoreFsHandle_t StoreFsInstance[] = {
    {
        .num = 1,
        .valid = true,
        .fs_num = 1,
        .storage_type = STORAGE_TYPE_LITTLE_FS,
    },
};

uint32_t store_fs_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(StoreFsConfig);
    cnt2 = ARRAY_SIZE(StoreFsInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
