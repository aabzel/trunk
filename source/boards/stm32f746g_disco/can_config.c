#include "can_config.h"

#include "log_config.h"
#include "data_utils.h"

#ifdef HAS_LED_MONO
#include "led_mono_config.h"
#endif

#define  MBIT_P_S_TO_BIT_P_S(MBPS) (   (uint32_t)     ((float)(MBPS))*1000000.0            )

#ifdef HAS_CAN1
static const uint32_t Can1IDtoRx[] = { 0x72A23A4, 0xC2, 0xC3, 0x6, 0x7 };
#endif

#ifdef HAS_CAN2
static const uint32_t Can2IDtoRx[] = { 0x72A23A4, 0xC2, 0xC3, 0x6, 0x7 };
#endif


/*constant compile-time known settings*/
const CanConfig_t SECTION_CFG_DATA  CanConfig[] = {

#ifdef HAS_CAN1
    {
      .num = 1,
      .name = "CAN1",
      .bit_rate = 1000000, // MBPS_TO_BPS(0.01),
      .bus_off_auto_recovery = true,

      .PadRx = { .port = PORT_A, .pin = 12,},
      .PadTx = { .port = PORT_A, .pin = 11,},

#ifdef HAS_LED_MONO
      .led_num_rx = LED_RX1_LED,
      .led_num_tx = LED_TX1_LED ,
#endif

      .clock_source =  CAN_CLOCK_SOURCE_PERIPHERAL,
      .identifier = CAN_FRAME_ID_EXTENDED,
      .mac_mode = CAN_MAC_MODE_ENHANCED_FIFO,
      .mode = CAN_CFG_MODE_COMMUNICATE,
      .move_mode = MOVE_MODE_INTERRUPT,
      .padding = 0x55,
      .rx_all = true,
      .my_id = 0x1,
      .rx_id = Can1IDtoRx,
      .payload_size = 8,
      .rx_id_cnt = 0,
      .re_tx = true,
      .heart_beat = false,
      .valid = true,
     // .rx_id_cnt = ARRAY_SIZE(Can1IDtoRx),
#ifdef HAS_CAN_INTERRUPT
      .interrupt_on = true,
      .interrupt_priority = 2,
#else
      .interrupt_on = false,
#endif
    },
#endif/*HAS_CAN1*/

#ifdef HAS_CAN2
    {
      .num = 2,
      .name = "CAN2",
      .bit_rate = 1000000, // MBPS_TO_BPS(0.01),
      .bus_off_auto_recovery = true,
      .clock_source =  CAN_CLOCK_SOURCE_PERIPHERAL,
      .identifier = CAN_FRAME_ID_EXTENDED,
      .mac_mode = CAN_MAC_MODE_ENHANCED_FIFO,
      .mode = CAN_CFG_MODE_COMMUNICATE,
      .move_mode = MOVE_MODE_INTERRUPT,
      .padding = 0x55,
      .my_id = 0x2,
      .rx_all = true,
      .PadRx = { .port = PORT_B, .pin = 12,},
      .PadTx = { .port = PORT_B, .pin = 13,},

#ifdef HAS_LED_MONO
      .led_num_rx = LED_RX2_LED,
      .led_num_tx = LED_TX2_LED ,
#endif
      .rx_id = Can2IDtoRx,
      .rx_id_cnt = 0,
      //.rx_id_cnt = ARRAY_SIZE(Can2IDtoRx),
      .payload_size = 8,
      .re_tx = true,
      .heart_beat = false,
      .valid = true,

#ifdef HAS_CAN_INTERRUPT
      .interrupt_on = true,
      .interrupt_priority = 2,
#else
      .interrupt_on = false,
#endif
    },
#endif

};

CanHandle_t CanInstance[] = {

#ifdef HAS_CAN1
    {.num =1, .valid=true,  },
#endif

#ifdef HAS_CAN2
    {.num =2, .valid=true,  },
#endif
};


COMPONENT_GET_CNT(Can, can)





