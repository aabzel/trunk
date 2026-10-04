#include "can_config.h"

#include "log_config.h"
#include "data_utils.h"

#define  MBIT_P_S_TO_BIT_P_S(MBPS) (   (uint32_t)     ((float)(MBPS))*1000000.0            )

#define  CAN_ID_TEST 0x04 // 0x04; 0x05 - ignored by receiver

#ifdef HAS_CAN0
static const uint32_t RxCANod[]={1, 2, 3, 4};
#endif

/*constant compile-time known settings*/
const CanConfig_t CanConfig[] = {
#ifdef HAS_CAN0
    { .num = 0,
      .name = "CAN0",
      .bit_rate = MBPS_TO_BPS(0.25),
      .identifier= CAN_FRAME_ID_STANDARD,
      .mode = CAN_CFG_MODE_COMMUNICATE,
      .move_mode = MOVE_MODE_POLLING,
      .clock_source =  CAN_CLOCK_SOURCE_PERIPHERAL,
      .my_id = 0x06,
      .padding = 0x55,
      .mac_mode = CAN_MAC_PC_EMULATED,
      .payload_size = 8,
      .slcan_num = 1,
      .rx_id = RxCANod,
      .rx_id_cnt = ARRAY_SIZE(RxCANod),
      .re_tx = true,
      .bus_off_auto_recovery = true,
      .interrupt_on = false,
      .heart_beat = false,
      .valid = true,
#ifdef HAS_CAN_FD
      .bit_rate_fd = MBPS_TO_BPS(3),
      .fd_enable = true,
#endif
    },
#endif/**/



};

CanHandle_t CanInstance[] = {
#ifdef HAS_CAN0
    {.num =0, .valid=true,  },
#endif /**/

};

COMPONENT_GET_CNT(Can, can)




