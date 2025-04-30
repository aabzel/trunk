#include "sdio_config.h"

#include "clock_utils.h"
#include "data_utils.h"
//#include "log_config.h"

/*48MHz - err
 * 1MHz unstable
 * */
/*30MHz - err*/
/*28MHz - */
/*24MHz - OK*/
/*20MHz - Err*/
/*10MHz - Err*/
/*5MHz  - Err*/

/*constant compile-time known settings in Flash*/
const SdioConfig_t SdioConfig[] = {
    {
        .num = 1,
        .bit_rate_hz = MHZ_2_HZ(1), //FatFsInitErr: 500000 1000000  < 10000000 24000000-err
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
