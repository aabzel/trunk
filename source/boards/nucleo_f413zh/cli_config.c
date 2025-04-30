#include "cli_config.h"

#include "log_config.h"
#include "data_utils.h"

#if (3!=LOG_UART_NUM)
#error "UART num mismatch"
#endif

const CliConfig_t CliConfig[] = {
    {
    .num = 1,
    .valid= true,
#ifdef HAS_LED
    .feedback_led=1,
#endif
    }
};

CliHandle_t CliInstance[]={
    {.num=1, .valid=true, }
};

uint32_t cli_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(CliInstance);
    cnt2 = ARRAY_SIZE(CliConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
