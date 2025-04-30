#include "uart_config.h"

#include "log_config.h"
#include "data_utils.h"

/*constant compile-time known settings*/
const UartConfig_t UartConfig[] = {
    { .num=1,    .valid=true,},
};


UartHandle_t UartInstance[]={
    {.num=1, .valid=true,    },

};

uint32_t uart_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(UartConfig);
    uint32_t cnt_ints = ARRAY_SIZE(UartInstance);
    if(cnt_conf==cnt_ints){
        cnt = cnt_ints;
    }
    return cnt;
}

