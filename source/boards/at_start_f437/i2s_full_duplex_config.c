#include "i2s_full_duplex_config.h"

#include "data_utils.h"

const I2sFullDuplexConfig_t I2sFullDuplexConfig[] = {
    {
        .num = 1,
        .valid = true,
        .name = "I2S2/5",
        .i2s_rx_num = 5,
        .echo_effect_num = 1,
        .i2s_tx_num = 2,
        .DebugPadTx = {.port=PORT_B, .pin=6,},
        .DebugPadRx = {.port=PORT_B, .pin=7,},
        .timer_num = 8,
    },
};

I2sFullDuplexHandle_t I2sFullDuplexInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t i2s_full_duplex_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(I2sFullDuplexConfig);
    uint32_t cnt_ints = ARRAY_SIZE(I2sFullDuplexInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
