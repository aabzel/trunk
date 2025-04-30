#include "w25m02gv_config.h"

#include "data_utils.h"
#include "w25m02gv_types.h"

static const W25m02gvRegVal_t W25m02RegArray[] = {
        {
                .addr = W25M02GV_REG_PROTECTION,
                .Reg.Protect={
                             .write_enable_bit=1,
                              },
        },

        {
            .addr = W25M02GV_REG_CONFIGURATION,
            .Reg.Configuration={
                    .buffer_mode=0,
                    .enable_ecc=0,
                    .enter_otp_mode=0,
            },
        },
};

const W25m02gvConfig_t W25m02gvConfig[] = {
    {
        .num = 1,
        .name = "W25M02GV",
        .reg_cnt = ARRAY_SIZE(W25m02RegArray),
        .RegArray = W25m02RegArray,
        .spi_num = 4,
        .valid = true,
        .Hold = {.port=PORT_G, .pin=8,},
        .ChipSelect = {.port=PORT_G, .pin=14,},
        .WriteProtect = {.port=PORT_G, .pin=10,},
    },
};

W25m02gvHandle_t W25m02gvInstance[] = {
    {
    .num = 1,
    .valid = true,
}
};

uint32_t w25m02gv_get_cnt(void) {
    uint8_t cnt = 0;
    cnt = ARRAY_SIZE(W25m02gvConfig);
    return cnt;
}
