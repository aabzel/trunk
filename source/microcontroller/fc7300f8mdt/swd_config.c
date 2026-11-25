#include "swd_config.h"

#include "data_utils.h"

const SwdConfig_t SwdConfig[] = {
#ifdef HAS_SWD1
    { .num=1, .baud_rate=1000000, .name = "SWD1", .valid=true,  },
#endif
};

SwdHandle_t SwdInstance[]={
#ifdef HAS_SWD1
    {.num=1, .valid=true,   },
#endif

};

uint32_t swd_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(SwdConfig);
    uint32_t cnt_ints = ARRAY_SIZE(SwdInstance);
    if(cnt_conf==cnt_ints){
        cnt = cnt_ints;
    }
    return cnt;
}

