#include "spifi_config.h"

#ifndef HAS_SPIFI
#error "Add HAS_SPIFI"
#endif /*HAS_SPIFI*/

#include "spifi_types.h"

const SpiFiConfig_t SpiFiConfig[] = {
   {
       .num = 0,
       .cache_on_off = true,
       .cache_limit = 0x90000000,
#ifdef HAS_LOG
       .name = "Winbond",
#endif
       .valid = true,
   },
};

SpiFiHandle_t SpiFiInstance[] = {
    {.num = 0, .valid = true, },
};

uint32_t spifi_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(SpiFiInstance);
    cnt2 = ARRAY_SIZE(SpiFiConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
