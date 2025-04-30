#include "sdio_config.h"

#include "data_utils.h"
#include "log_config.h"
#include "clock_utils.h"
/*1MHz<bit_rate_hz<10MHz*/
/*constant compile-time known settings in Flash*/
const SdioConfig_t SdioConfig[] = {
    {
        .num = 1,
        //.bit_rate_hz = MHZ_2_HZ(20),
        .bit_rate_hz = MHZ_2_HZ(1),
        .name = "SdCard", 
        .valid = true,
    },
};

SdioHandle_t SdioInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t sdio_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(SdioConfig);
    uint32_t cnt_ints = ARRAY_SIZE(SdioInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
