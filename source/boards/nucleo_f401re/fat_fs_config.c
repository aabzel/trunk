#include "fat_fs_config.h"

#include "data_utils.h"

const FatFsConfig_t FatFsConfig[] = {
    {
        .num = 1,
        .disk_num = 1,
        .valid = true,
        .name = "SPI",
    },
};

FatFsHandle_t FatFsInstance[] = {
    {
        .num = 1,
        .valid = true,
    },


};

COMPONENT_GET_CNT(FatFs, fat_fs)

