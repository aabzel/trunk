#include "log_config.h"

#include "data_utils.h"

const LogConfig_t LogConfig[1] = {
    {
        .num = 1,
        .valid = true,
        .colored = true,
        .time_stamp = true,
#ifdef HAS_UART
        .interface_ = IF_UART1,
#endif
    },
};

LogHandle_t LogInstance[1] = {
    {
      .num = 1,
      .valid = true,
      .serial_nun = 0,
      .time_stamp = true,
      .colored = true,
#ifdef HAS_UART
      .interface_ = IF_UART1,
#endif
    },
};

bool log_fix(void) {
    bool res = true;
    LogInstance[0].num = LogConfig[0].num;
    LogInstance[0].colored = LogConfig[0].colored;
    LogInstance[0].time_stamp = LogConfig[0].time_stamp;
#ifdef HAS_INTERFACES
    LogInstance[0].interface_ = LogConfig[0].interface_;
#endif
    LogInstance[0].valid = true;
    return res;
}



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
