#include "gpio_dac_config.h"

#include "data_utils.h"

const GpioDacConfig_t GpioDacConfig[] = {
    {
        .num = 1,
        .valid = true,
        .timer_num = 99,
        .sample_freq_hz = 96000,
        .PadOut={.port = PORT_B, .pin = 2, },
        .name = "UartTx",
    },
};

GpioDacHandle_t GpioDacInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t gpio_dac_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(GpioDacConfig);
    cnt2 = ARRAY_SIZE(GpioDacInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
