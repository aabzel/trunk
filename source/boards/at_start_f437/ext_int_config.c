#include "ext_int_config.h"

#include "log_config.h"
#include "data_utils.h"

/*constant compile-time known settings*/
const ExtIntConfig_t ExtIntConfig[] = {
    { .num = 0,
      .name = "PA0",
      .Pad={.port=PORT_A, .pin=0},
      .edge=PIN_INT_EDGE_RISING,
      .valid=true,
      .irq_priority=2,
      .interrupt_on =true,
    },
};

ExtIntHandle_t ExtIntInstance[] = {
    {.num=0, .valid=true,},
};

uint32_t ext_int_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(ExtIntConfig);
    uint32_t cnt_ints = ARRAY_SIZE(ExtIntInstance);
    if(cnt_conf==cnt_ints){
        cnt = cnt_ints;
    }
    return cnt;
}

