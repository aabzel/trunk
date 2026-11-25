#include "can_rx_hist_config.h"

#include "data_utils.h"

#define CAN_RX_HIST_MAX_FRAME_CNT 25
static CanRxMesgInfo_t RxMesgArray1[CAN_RX_HIST_MAX_FRAME_CNT] = {0};
static CanRxMesgInfo_t RxMesgArray2[CAN_RX_HIST_MAX_FRAME_CNT] = {0};

const CanRxHistConfig_t CanRxHistConfig[] = {
    {
        .num = 1,
        .can_num = 1,
        .rx_mesg_array_cnt = ARRAY_SIZE(RxMesgArray1),
        .RxMesgArray = RxMesgArray1,
        .valid = true,
        .name = "CAN1",
    },

    {
        .num = 2,
        .can_num = 2,
        .rx_mesg_array_cnt = ARRAY_SIZE(RxMesgArray2),
        .RxMesgArray = RxMesgArray2,
        .valid = true,
        .name = "CAN2",
    },

};

CanRxHistHandle_t CanRxHistInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },

};

uint32_t can_rx_hist_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(CanRxHistConfig);
    cnt2 = ARRAY_SIZE(CanRxHistInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
