#include "at24cxx_config.h"

#include "at24cxx_types.h"
#include "data_utils.h"

const At24cxxConfig_t At24cxxConfig[] = {
    {
        .num = 1,
        .i2c_num = 2,
        .valid = true,
        .chip_addr = 0x50, /*0xa1 0xa0  10100001 , 10100000 1010000*/
        .write_enable = true,
        .wp =
            {
                .port = 7,
                .pin = 15,
            },
        .chip_model = AT24C02,
    },
};

At24cxxHandle_t At24cxxInstance[] = {{
    .num = 1,
    .valid = true,
}};

uint32_t at24cxx_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(At24cxxInstance);
    cnt2 = ARRAY_SIZE(At24cxxConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
