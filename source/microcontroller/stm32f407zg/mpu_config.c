#include "mpu_config.h"

#include "data_utils.h"

char gMpuTestDataBanWrite[32] = {0};
char gMpuTestDataBanRead[64] = {0};
char gMpuTestDataBanAll[128] = {0};

static const MpuRegionConfig_t SECTION_CFG_DATA MpuRegions[] = {
    {
        .num = 0,
        .start = (uint32_t)gMpuTestDataBanWrite,
        .size = sizeof(gMpuTestDataBanWrite),
        .on_off = true,
        .valid = true,
        .permission =
            {
                .read = 1,
                .write = 0,
                .execute = 1,
            },
        .name = "BanWrite",
    },
    {
        .num = 1,
        .start = (uint32_t)gMpuTestDataBanRead,
        .size = sizeof(gMpuTestDataBanRead),
        .on_off = true,
        .valid = true,
        .permission =
            {
                .read = 0,
                .write = 1,
                .execute = 1,
            },
        .name = "BanRead",
    },
    {
        .num = 2,
        .start = (uint32_t)gMpuTestDataBanAll,
        .size = sizeof(gMpuTestDataBanAll),
        .on_off = true,
        .valid = true,
        .permission =
            {
                .read = 0,
                .write = 0,
                .execute = 0,
            },
        .name = "BanAll",
    },
};

const MpuConfig_t SECTION_CFG_DATA MpuConfig[] = {
    {
        .num = 0,
        .Region = MpuRegions,
        .region_cnt = ARRAY_SIZE(MpuRegions),
        .valid = true,
        .name = "MPU",
    },
};

MpuHandle_t MpuInstance[] = {
    {
        .num = 0,
        .valid = true,
    },
};


COMPONENT_GET_CNT(Mpu, mpu)

