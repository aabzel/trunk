#include "fw_loader_config.h"

#include <stddef.h>

#include "data_utils.h"

const FwLoaderConfig_t FwLoaderConfig[] = {
    {
            .num = 1,
            .hex_file_name = "start_mik32_v1_generic_gcc_m.hex",
            .tbfp_num = 1,
            .com_num = 4,
            .bit_rate = 56000,
            .valid = true,
    },
    {
            .num = 2,
            .hex_file_name = "start_mik32_v1_generic_gcc_m.hex",
            .tbfp_num = 1,
            .com_num = 3,
            .bit_rate = 56000,
            .valid = true,
    },
};

FwLoaderHandle_t FwLoaderInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },
};

uint32_t fw_loader_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(FwLoaderConfig);
    uint32_t cnt_ints = ARRAY_SIZE(FwLoaderInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
