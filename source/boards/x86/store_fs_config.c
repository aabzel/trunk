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
    },
};

COMPONENT_GET_CNT(StoreFs, store_fs)


