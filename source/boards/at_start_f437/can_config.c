#include "can_config.h"

#include "log_config.h"
#include "data_utils.h"

/*constant compile-time known settings*/
const CanConfig_t CanConfig[] = {
#ifdef HAS_CAN1
    { .num=1, .name = "CAN1", .tx_id=0x03CB, .rx_id=0x02BA, .valid=true, .bit_rate=500000, .re_tx=true, .mode =CAN_CFG_MODE_COMMUNICATE,},
#endif/*HAS_CAN1*/

#ifdef HAS_CAN2
    { .num=2, .name = "CAN2", .tx_id=0x03CB, .rx_id=0x02BA, .valid=true, .bit_rate=500000, .re_tx=true, .mode =CAN_CFG_MODE_COMMUNICATE,},
#endif/*HAS_CAN2*/
};

CanHandle_t CanInstance[] = {
#ifdef HAS_CAN1
    {.num=1, .valid=true,  },
#endif /*HAS_CAN1*/

#ifdef HAS_CAN2
    {.num=2, .valid=true,      },
#endif/*HAS_CAN2*/
};

uint32_t can_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(CanConfig);
    uint32_t cnt_ints = ARRAY_SIZE(CanInstance);
    if(cnt_conf==cnt_ints){
        cnt = cnt_ints;
    }
    return cnt;
}

