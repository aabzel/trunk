#include "tbfp_config.h"

#include "data_utils.h"
#include "tbfp_const.h"
#include "interfaces_const.h"

#define TBFP_RX_BUFF_SIZE 512

static uint8_t RxData1[TBFP_MAX_TX_BUFF] = {0};
static uint8_t RxData2[TBFP_MAX_TX_BUFF] = {0};
static uint8_t RxData3[TBFP_MAX_TX_BUFF] = {0};
static uint8_t RxData4[TBFP_MAX_TX_BUFF] = {0};

static uint8_t TxBuff1[TBFP_MAX_TX_BUFF] = {0};
static uint8_t TxBuff2[TBFP_MAX_TX_BUFF] = {0};
static uint8_t TxBuff3[TBFP_MAX_TX_BUFF] = {0};
static uint8_t TxBuff4[TBFP_MAX_TX_BUFF] = {0};

static uint8_t MemRxFrame[TBFP_MAX_FRAME] = {0};
static uint8_t MemRxFrameFix[TBFP_MAX_FRAME] = {0};

const TbfpConfig_t TbfpConfig[] = {
    {
    .num = TBFP_NUM_SERIAL_PORT,
    .inter_face = IF_SERIAL_PORT,
    .preamble_val = 0xA5,
    .RxArray = RxData4,
    .TxFrame = TxBuff4,
    .tx_array_size = TBFP_MAX_TX_BUFF,
    .crc_check_need = false,
    .valid = true,
    .rx_frame = MemRxFrame,
    .fix_frame = MemRxFrameFix,
    },
    {
     .num = TBFP_NUM_STDIO,
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
        .num = TBFP_NUM_LOOPBACK,
        .inter_face = IF_LOOPBACK,
        .RxArray = RxData2,
        .TxFrame=TxBuff2,
        .tx_array_size=TBFP_MAX_TX_BUFF,
        .preamble_val = 0xA5,
        .valid = true,
        .rx_frame = MemRxFrame,
        .fix_frame = MemRxFrameFix,
    },

    {
        .num = TBFP_NUM_BLACK_HOLE,
        .inter_face = IF_BLACK_HOLE,
        .RxArray = RxData3,
        .TxFrame = TxBuff3,
        .tx_array_size = TBFP_MAX_TX_BUFF,
        .preamble_val = 0xB0,
        .valid = true,
         .rx_frame = MemRxFrame,
        .fix_frame = MemRxFrameFix,
    },


#ifdef HAS_UWB
    {
     .num = 5,
     .inter_face = IF_UWB,
     .preamble_val = 0x12, 
     .valid = true, 
     .RxArray = RxData5,
     .TxFrame=TxBuff5,
     .tx_array_size=TBFP_MAX_TX_BUFF, 
     .rx_frame = MemRxFrame,
     .fix_frame = MemRxFrameFix,
     },
#endif
};


TbfpHandle_t TbfpInstance[] = {
    {.num = TBFP_NUM_SERIAL_PORT, .valid = true,},
    {.num = TBFP_NUM_STDIO, .valid = true,},
    {.num = TBFP_NUM_LOOPBACK, .valid = true,},
    {.num = TBFP_NUM_BLACK_HOLE, .valid = true,},
#ifdef HAS_UWB
    {.num = 5, .valid = true,},
#endif
};

bool tbfp_init_common(const TbfpConfig_t* const Config, TbfpHandle_t* const Node) ;

uint32_t tbfp_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(TbfpInstance);
    cnt2 = ARRAY_SIZE(TbfpConfig);
    if (cnt1 == cnt2) {
        cnt = cnt1;
    }
    uint32_t i = 0 ;
    for(i=0;i<cnt;i++){
    	tbfp_init_common(&TbfpConfig[i], &TbfpInstance[i]);
    }
    return cnt;
}
