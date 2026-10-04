#include "store_fs_config.h"

#include "data_utils.h"

const StoreFsConfig_t SECTION_CFG_DATA StoreFsConfig[] = {
    {
        .num = 1,
        .valid = true,
        .fs_num = 1,
        .storage_type = STORAGE_TYPE_FLASH_FS,
        .name = "NVRAM",
    },
    {
        .num = 2,
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
        .storage_type = STORAGE_TYPE_FLASH_FS,
    },
    {
        .num = 2,
        .valid = true,
        .fs_num = 1,
        .storage_type = STORAGE_TYPE_LITTLE_FS,
    },
};

COMPONENT_GET_CNT(StoreFs, store_fs)
