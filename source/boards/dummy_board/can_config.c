#include "can_config.h"

#include "log_config.h"
#include "data_utils.h"

#define  MBIT_P_S_TO_BIT_P_S(MBPS) (   (uint32_t)     ((float)(MBPS))*1000000.0            )

#define  CAN_ID_TEST 0x04 // 0x04; 0x05 - ignored by receiver

/*constant compile-time known settings*/
const CanConfig_t CanConfig[] = {
#ifdef HAS_CAN0
    { .num = 0,
      .name = "CAN0",
      .bit_rate = MBPS_TO_BPS(0.25),
      .identifier= CAN_FRAME_ID_STANDARD,
      .mode = CAN_CFG_MODE_COMMUNICATE,
      .move_mode = MOVE_MODE_INTERRUPT,
      .clock_source =  CAN_CLOCK_SOURCE_PERIPHERAL,
      .padding = 0x55,
      .payload_size = 64,
      .re_tx = true,
      .bus_off_auto_recovery = true,
      .interrupt_on = true,
      .heart_beat = true,
      .rx_id = CAN_ID_TEST,
      .tx_id = CAN_ID_TEST,
      .valid = true,
#ifdef HAS_CAN_FD
      .bit_rate_fd = MBPS_TO_BPS(3),
      .fd_enable = true,
#endif
    },
#endif/*HAS_CAN0*/

#ifdef HAS_CAN1
    { .num = 1,
      .name = "CAN1",
      .bit_rate = MBPS_TO_BPS(0.25),
      .bus_off_auto_recovery = true,
      .clock_source =  CAN_CLOCK_SOURCE_PERIPHERAL,
#ifdef HAS_CAN_FD
      .bit_rate_fd = MBPS_TO_BPS(3),
      .fd_enable = false,
#endif
      .identifier= CAN_FRAME_ID_STANDARD,
      .mode = CAN_CFG_MODE_COMMUNICATE,
      .move_mode=MOVE_MODE_INTERRUPT,
      .padding=0x55,
      .payload_size=64,
      .interrupt_on = true,
      .re_tx=true,
      .heart_beat = true,
      .rx_id = CAN_ID_TEST,
      .tx_id = CAN_ID_TEST,
      .valid=true,
    },
#endif/*HAS_CAN1*/

#ifdef HAS_CAN2
    { .num =2,
      .name = "CAN2",
      .bit_rate = MBPS_TO_BPS(0.25),
      .bus_off_auto_recovery = true,
      .clock_source =  CAN_CLOCK_SOURCE_PERIPHERAL,
#ifdef HAS_CAN_FD
      .bit_rate_fd = MBPS_TO_BPS(3),
      .fd_enable = false,
#endif
      .identifier= CAN_FRAME_ID_STANDARD,
      .mode = CAN_CFG_MODE_COMMUNICATE,
      .move_mode=MOVE_MODE_INTERRUPT,
      .padding=0x55,
      .interrupt_on = true,
      .payload_size=64,
      .re_tx=true,
      .heart_beat = true,
      .rx_id = CAN_ID_TEST,
      .tx_id = CAN_ID_TEST,
      .valid=true,
    },
#endif/*HAS_CAN2*/

#ifdef HAS_CAN3
    { .num =3,
      .name = "CAN3",
      .bit_rate = MBPS_TO_BPS(0.25),
      .bus_off_auto_recovery = true,
      .clock_source =  CAN_CLOCK_SOURCE_PERIPHERAL,
#ifdef HAS_CAN_FD
      .bit_rate_fd = MBPS_TO_BPS(3),
      .fd_enable = false,
#endif
      .identifier= CAN_FRAME_ID_STANDARD,
      .mode = CAN_CFG_MODE_COMMUNICATE,
      .move_mode=MOVE_MODE_INTERRUPT,
      .padding=0x55,
      .payload_size=64,
      .interrupt_on = true,
      .re_tx=true,
      .heart_beat = true,
      .rx_id = CAN_ID_TEST,
      .tx_id = CAN_ID_TEST,
      .valid=true,},
#endif/*HAS_CAN3*/

#ifdef HAS_CAN4
    { .num =4,
      .name = "CAN4",
      .bit_rate = MBPS_TO_BPS(0.25),
      .bus_off_auto_recovery = true,
      .clock_source =  CAN_CLOCK_SOURCE_PERIPHERAL,
#ifdef HAS_CAN_FD
      .bit_rate_fd = MBPS_TO_BPS(3),
      .fd_enable=true,
#endif
      .identifier= CAN_FRAME_ID_STANDARD,
      .heart_beat = true,
      .mode = CAN_CFG_MODE_COMMUNICATE,
      .move_mode=MOVE_MODE_INTERRUPT,
      .padding=0x55,
      .interrupt_on = true,
      .payload_size=64,
      .re_tx=true,
      .rx_id = CAN_ID_TEST,
      .tx_id = CAN_ID_TEST,
      .valid = true,},
#endif/*HAS_CAN4*/


};

CanHandle_t CanInstance[] = {
#ifdef HAS_CAN0
    {.num =0, .valid=true,  },
#endif /*HAS_CAN0*/

#ifdef HAS_CAN1
    {.num =1, .valid=true,  },
#endif /*HAS_CAN1*/

#ifdef HAS_CAN2
    {.num =2, .valid=true,  },
#endif /*HAS_CAN2*/

#ifdef HAS_CAN3
    {.num =3, .valid=true,      },
#endif/*HAS_CAN3*/

#ifdef HAS_CAN4
    {.num =4, .valid=true,      },
#endif/*HAS_CAN4*/

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




