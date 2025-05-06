#include "tbfp_config.h"

#include "data_utils.h"
#include "tbfp_const.h"

#define TBFP_RX_BUFF_SIZE 512

static uint8_t RxData1[TBFP_MAX_TX_BUFF] = {0};

static uint8_t TxBuff1[TBFP_MAX_TX_BUFF] = {0};
static uint8_t TxBuff2[TBFP_MAX_TX_BUFF] = {0};
static uint8_t TxBuff3[TBFP_MAX_TX_BUFF] = {0};
static uint8_t TxBuff4[TBFP_MAX_TX_BUFF] = {0};

static uint8_t MemRxFrame[TBFP_MAX_FRAME] = {0};
static uint8_t MemRxFrameFix[TBFP_MAX_FRAME] = {0};

const TbfpConfig_t TbfpConfig[] = {
    {
     .num = 1, 
     .inter_face = IF_STDIO,
     .RxArray = RxData1,
     .rx_array_size = sizeof(RxData1),
     .TxFrame = TxBuff1, 
     .tx_array_size = sizeof(TxBuff1),
     .uart_num = 0x55,
     .preamble_val = 0xA5,
     .valid = true,
  	 .rx_frame = MemRxFrame,
	 .fix_frame = MemRxFrameFix,
     },

    {
        .num = 2,
        .inter_face = IF_LOOPBACK,
        .TxFrame=TxBuff2,
        .tx_array_size=TBFP_MAX_TX_BUFF,
        .preamble_val = 0xA5,
        .valid = true,
        .rx_frame = MemRxFrame,
        .fix_frame = MemRxFrameFix,
    },

    {
        .num = 3,
        .inter_face = IF_BLACK_HOLE,
        .TxFrame = TxBuff3,
        .tx_array_size = TBFP_MAX_TX_BUFF,
        .preamble_val = 0xB0,
        .valid = true,
 	    .rx_frame = MemRxFrame,
	    .fix_frame = MemRxFrameFix,
    },

    {
    .num = 4,
    .inter_face = IF_SERIAL_PORT,
    .TxFrame = TxBuff4,
    .tx_array_size = TBFP_MAX_TX_BUFF,
    .preamble_val = 0xA5,
    .valid = true,
 	 .rx_frame = MemRxFrame,
	 .fix_frame = MemRxFrameFix,
    },

#ifdef HAS_UWB
    {.num = 5,
     .inter_face = IF_UWB,
     .preamble_val = 0x12, 
     .valid = true, 
     .TxFrame=TxBuff3, 
     .tx_array_size=TBFP_MAX_TX_BUFF, 
  	 .rx_frame = MemRxFrame,
	 .fix_frame = MemRxFrameFix,
     },
#endif
};


TbfpHandle_t TbfpInstance[] = {
    {.num = 1, .valid = true,},
    {.num = 2, .valid = true,},
    {.num = 3, .valid = true,},
    {.num = 4, .valid = true,},
#ifdef HAS_UWB
    {.num = 5, .valid = true,},
#endif
};

uint32_t tbfp_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(TbfpInstance);
    cnt2 = ARRAY_SIZE(TbfpConfig);
    if (cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
