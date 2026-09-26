#include "disk_config.h"

#include "data_utils.h"
#include "interfaces_const.h"

const DiskConfig_t DiskConfig[] = {
    {
        .num = 0,
        .valid = true,
        .block_size = 512,
        .inter_face = {
                          .interface_name = INTERFACE_NAME_SDIO,
                          .num = 1,
                      },
        .name = "SDIO1",
    },
};

DiskHandle_t DiskInstance[] = {
    {
        .num = 0,
        .valid = true,
    },
};

COMPONENT_GET_CNT(Disk, disk)
