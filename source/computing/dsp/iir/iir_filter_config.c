#include "iir_config.h"

#include "data_utils.h"

const IirConfig_t IirFiltConfig[]={
    {
     .num=IIF_FILT_ECHO_NUM,
     .mult=0.4,
     .name="IIF",
     .capacity=IIF_FILT_ECHO_FIFO_SIZE,
    },
};

IirHandle_t IirFiltItem[]={
    {.num = IIF_FILT_ECHO_NUM, .init=false, },
};

uint32_t iir_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(IirFiltConfig);
    uint32_t cnt_ints = ARRAY_SIZE(IirFiltItem);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
