#include "sonar_config.h"

#include <stddef.h>

#include "data_utils.h"
#include "dds_config.h"
#include "fir_config.h"

const SonarConfig_t SonarConfig[] = {
    {
            .num = 1,
            .fir_num = FIR_MUN_CHIRP_CORRELATION,
            .dds_num = DDS_CHIRP_NUM,
            .convolution_file_name = "convolution.csv",
            .chirp_duration_s = MSEC_2_SEC(30),
            .frequency1 = 450,
            .frequency2 = 10000,
            .valid = true,
    },
};


SonarHandle_t SonarInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t sonar_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(SonarConfig);
    uint32_t cnt_ints = ARRAY_SIZE(SonarInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
