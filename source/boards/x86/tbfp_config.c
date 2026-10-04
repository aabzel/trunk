#include "tbfp_config.h"

#include "data_utils.h"
#include "tbfp_const.h"

#define TBFP_RX_BUFF_SIZE 512

static uint8_t RxData1[TBFP_MAX_TX_BUFF] = {0};
static uint8_t RxData2[TBFP_MAX_TX_BUFF] = {0};
static uint8_t RxData3[TBFP_MAX_TX_BUFF] = {0};
static uint8_t RxData4[TBFP_MAX_TX_BUFF] = {0};
static uint8_t RxData5[TBFP_MAX_TX_BUFF] = {0};

static uint8_t TxBuff1[TBFP_MAX_TX_BUFF] = {0};
static uint8_t TxBuff2[TBFP_MAX_TX_BUFF] = {0};
static uint8_t TxBuff3[TBFP_MAX_TX_BUFF] = {0};
static uint8_t TxBuff4[TBFP_MAX_TX_BUFF] = {0};
static uint8_t TxBuff5[TBFP_MAX_TX_BUFF] = {0};

static uint8_t Mem1RxFrame[TBFP_MAX_FRAME] = {0};
static uint8_t Mem1RxFrameFix[TBFP_MAX_FRAME] = {0};

static uint8_t Mem2RxFrame[TBFP_MAX_FRAME] = {0};
static uint8_t Mem2RxFrameFix[TBFP_MAX_FRAME] = {0};

static uint8_t Mem3RxFrame[TBFP_MAX_FRAME] = {0};
static uint8_t Mem3RxFrameFix[TBFP_MAX_FRAME] = {0};

static uint8_t Mem4RxFrame[TBFP_MAX_FRAME] = {0};
static uint8_t Mem4RxFrameFix[TBFP_MAX_FRAME] = {0};

static uint8_t Mem5RxFrame[TBFP_MAX_FRAME] = {0};
static uint8_t Mem5RxFrameFix[TBFP_MAX_FRAME] = {0};


const TbfpConfig_t TbfpConfig[] = {
    {
     .num = TBFP_NUM_STDIO,
     .inter_face = { .interface_name=INTERFACE_NAME_STDIO, .num=0,},
     .RxArray = RxData1, .rx_array_size = sizeof(RxData1),
     .TxFrame = TxBuff1, .tx_array_size = sizeof(TxBuff1),
     .preamble_val = 0x49, .valid = true,
     .rx_frame = Mem1RxFrame, .fix_frame = Mem1RxFrameFix,
     },
    {
    .num = TBFP_NUM_LOOPBACK,
    .inter_face = { .interface_name=INTERFACE_NAME_LOOPBACK, .num=0,},
    .RxArray = RxData2, .rx_array_size = sizeof(RxData2),
    .TxFrame = TxBuff2, .tx_array_size = TBFP_MAX_TX_BUFF,
    .preamble_val = 0x4C, .valid = true,
    .rx_frame = Mem2RxFrame, .fix_frame = Mem2RxFrameFix,
    },
    {
    .num = TBFP_NUM_BLACK_HOLE,
    .inter_face = { .interface_name=INTERFACE_NAME_BLACKHOLE, .num=0,},
    .RxArray = RxData3, .rx_array_size = sizeof(RxData3),
    .TxFrame = TxBuff3, .tx_array_size = TBFP_MAX_TX_BUFF,
    .preamble_val = 0x42, .valid = true,
    .rx_frame = Mem3RxFrame, .fix_frame = Mem3RxFrameFix,
    },
#ifdef HAS_CAN0
    {
     .num = TBFP_NUM_CAN0,
     .inter_face = { .interface_name=INTERFACE_NAME_CAN, .num=0,},
     .RxArray = RxData4, .rx_array_size = sizeof(RxData4),
     .preamble_val = 0x43, .valid = true,
     .TxFrame = TxBuff4, .tx_array_size = TBFP_MAX_TX_BUFF,
     .rx_frame = Mem4RxFrame, .fix_frame = Mem4RxFrameFix,
     },
#endif

#ifdef HAS_SERIAL_PORT
    {
     .num = TBFP_NUM_SERIAL_PORT,
     .inter_face = { .interface_name = INTERFACE_NAME_SERIAL_PORT, .num = 0,},
     .RxArray = RxData5, .rx_array_size = sizeof(RxData5),
     .preamble_val = 0x53, .valid = true,
     .TxFrame = TxBuff5, .tx_array_size = TBFP_MAX_TX_BUFF,
     .rx_frame = Mem5RxFrame, .fix_frame = Mem5RxFrameFix,
     },
#endif

};

TbfpHandle_t TbfpInstance[] = {
    {.num = TBFP_NUM_STDIO, .valid = true,},
    {.num = TBFP_NUM_LOOPBACK, .valid = true,},
    {.num = TBFP_NUM_BLACK_HOLE, .valid = true,},

#ifdef HAS_CAN
    {.num = TBFP_NUM_CAN0, .valid = true,},
#endif

#ifdef HAS_SERIAL_PORT
    {.num = TBFP_NUM_SERIAL_PORT, .valid = true,},
#endif
};

COMPONENT_GET_CNT(Tbfp, tbfp)


