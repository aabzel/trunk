#include "sdio_config.h"

#include "data_utils.h"
#include "log_config.h"

/*constant compile-time known settings in Flash*/
const SdioConfig_t SdioConfig[] = {
    {
        .num = 1, .name = "SdCard", .valid = true,
        .clock_div = 32, /*32<OptimalVal <128 200 254*/    
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
