#include "tbfp_config.h"

#include "data_utils.h"
#include "gpio_const.h"
#include "common_const.h"
#include "tbfp_const.h"

#ifdef HAS_UART0
static uint8_t RxData0[TBFP_MAX_BUFF] = {0};
static uint8_t TxBuff0[TBFP_MAX_BUFF] = {0};
static uint8_t MemRxFrame0[TBFP_MAX_FRAME] = {0};
static uint8_t MemRxFrameFix0[TBFP_MAX_FRAME] = {0};
#endif

#ifdef HAS_UART1
static uint8_t RxData1[TBFP_MAX_BUFF] = {0};
static uint8_t TxBuff1[TBFP_MAX_BUFF] = {0};
static uint8_t MemRxFrame1[TBFP_MAX_FRAME] = {0};
static uint8_t MemRxFrameFix1[TBFP_MAX_FRAME] = {0};
#endif



const TbfpConfig_t TbfpConfig[] = {
#ifdef HAS_UART0
    {
     .num = 1,
     .inter_face = IF_UART0,
     .uart_num = 0,
     .heartbeat = false,
     .RxArray = RxData0,
     .rx_array_size = TBFP_MAX_BUFF,
     .TxFrame = TxBuff0,
     .tx_array_size = TBFP_MAX_BUFF,
     .preamble_val = 0xA5,
     .valid = true,
     .rx_frame = MemRxFrame0,
     .fix_frame = MemRxFrameFix0,
    },
#endif

#ifdef HAS_UART1
    {
     .num = 2,
     .inter_face = IF_UART1,
     .uart_num = 1,
     .heartbeat = true,
     .RxArray = RxData1,
     .rx_array_size = TBFP_MAX_BUFF,
     .TxFrame = TxBuff1,
     .tx_array_size = TBFP_MAX_BUFF,
     .preamble_val = 0xA5,
     .valid = true,
     .rx_frame = MemRxFrame1,
     .fix_frame = MemRxFrameFix1,
    },
#endif
};


TbfpHandle_t TbfpInstance[] = {
#ifdef HAS_UART0
    {
       .num = 1,
       .valid = true,
       .rx_frame = 0,
       .fix_frame = 0,
    },
#endif

#ifdef HAS_UART1
    {
       .num = 2,
       .valid = true,
       .rx_frame = 0,
       .fix_frame = 0,
    },
#endif
};

uint32_t tbfp_get_cnt(void) {
    return ARRAY_SIZE(TbfpConfig);
}
