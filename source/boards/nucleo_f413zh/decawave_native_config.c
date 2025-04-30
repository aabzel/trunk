#include "decawave_native_config.h"

#include "common_const.h"
#include "data_utils.h"
#include "decawave_native_types.h"
#include "gpio_const.h"

const DecaWaveNativeConfig_t DecaWaveNativeConfig[] = {
    {
        .num = 1,
        .addr_def = 0x0A,
        .interface = IF_UWB,
        .valid = true,

#ifdef HAS_DECAWAVE_SNIFFER
        .debug_led_num = 4,
#else
        .debug_led_num = 2,
#endif
    },
};

DecaWaveNativeHandle_t DecaWaveNativeInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t decawave_native_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(DecaWaveNativeInstance);
    cnt2 = ARRAY_SIZE(DecaWaveNativeConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
