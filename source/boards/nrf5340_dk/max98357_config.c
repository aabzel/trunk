#include "max98357_config.h"

#ifndef HAS_MAX98357
#error "Add HAS_MAX98357"
#endif /*HAS_MAX98357*/

#include "data_utils.h"
#include "max98357_types.h"

/*constant compile-time known settings*/
Max98357Config_t Max98357Config[] = {
    {
        .num = 1,
        .i2s_num = 0,
        .dac_num = 1,
        .shut_down_pad = {.port = 0, .pin = 17},
        .valid = true,
    },
};

Max98357Handle_t Max98357Instance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t max98357_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(Max98357Instance);
    cnt2 = ARRAY_SIZE(Max98357Config);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
