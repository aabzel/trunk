#include "gps_1bit_config.h"

#include "common_const.h"
#include "data_utils.h"



const Gps1BitConfig_t Gps1BitConfig[] = {
    {
       // visible sats: 5 14 30  13 15 20 28
        .num = 1,
        .valid = true,
    },

    {
        /*visible sats:  17 28 1 32 11 23 4 6 */
        .num = 2,
        .valid = true,
    },

};

Gps1BitHandle_t Gps1BitInstance[] = {
    {        .num = 1,        .valid = true,    },
    {        .num = 2,        .valid = true,    },
};

uint32_t gps_1bit_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(Gps1BitInstance);
    cnt2 = ARRAY_SIZE(Gps1BitConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
