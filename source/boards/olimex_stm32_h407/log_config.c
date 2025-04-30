#include "log_config.h"

#include "data_utils.h"

const LogConfig_t LogConfig[] = {
    {
        .num = 1,
        .valid = true,
        .colored = true,
        .time_stamp = true,
#ifdef HAS_INTERFACES
        .interface_ = IF_UART3,
#endif
    },
#ifdef HAS_USB
    {
        .num = 2,
        .valid = true,
        .colored = false,
        .time_stamp = true,
        .interface_ = IF_USB_HID,
    },
#endif
};

LogHandle_t LogInstance[] = {
        {    .num = 1,    .valid = true,},
#ifdef HAS_USB
        {    .num = 2,    .valid = true,},
#endif
};

uint32_t log_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(LogInstance);
    cnt2 = ARRAY_SIZE(LogConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
