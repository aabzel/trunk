#include "tbfp_config.h"

#include "data_utils.h"
#include "tbfp_const.h"

#ifndef TBFP_MAX_FRAME
#define TBFP_MAX_FRAME (TBFP_MAX_PAYLOAD+TBFP_SIZE_OVERHEAD)
#endif

static uint8_t RxBuff1[TBFP_MAX_FRAME] = {0};
static uint8_t TxBuff1[TBFP_MAX_FRAME] = {0};
static uint8_t Mem1RxFrame[TBFP_MAX_FRAME] = {0};
static uint8_t Mem1RxFrameFix[TBFP_MAX_FRAME] = {0};

static uint8_t RxBuff2[TBFP_MAX_FRAME] = {0};
static uint8_t TxBuff2[TBFP_MAX_FRAME] = {0};
static uint8_t Mem2RxFrame[TBFP_MAX_FRAME] = {0};
static uint8_t Mem2RxFrameFix[TBFP_MAX_FRAME] = {0};

static uint8_t RxBuff3[TBFP_MAX_FRAME] = {0};
static uint8_t TxBuff3[TBFP_MAX_FRAME] = {0};
static uint8_t Mem3RxFrame[TBFP_MAX_FRAME] = {0};
static uint8_t Mem3RxFrameFix[TBFP_MAX_FRAME] = {0};

static uint8_t RxBuff4[TBFP_MAX_FRAME] = {0};
static uint8_t TxBuff4[TBFP_MAX_FRAME] = {0};
static uint8_t Mem4RxFrame[TBFP_MAX_FRAME] = {0};
static uint8_t Mem4RxFrameFix[TBFP_MAX_FRAME] = {0};

const TbfpConfig_t SECTION_CFG_DATA TbfpConfig[] = {
    {
     .num = TBFP_NUM_CAN0,
     .inter_face = { .interface_name = INTERFACE_NAME_CAN, .num=0,},
     .RxArray = RxBuff3, .rx_array_size = sizeof(RxBuff3),
     .TxFrame = TxBuff3, .tx_array_size = sizeof(TxBuff3)  ,
     .preamble_val = 0x43, .valid = true,
     .rx_frame = Mem3RxFrame, .fix_frame = Mem3RxFrameFix,
     },
     {
      .num = TBFP_NUM_CAN1,
      .inter_face = { .interface_name = INTERFACE_NAME_CAN, .num=1,},
      .RxArray = RxBuff4, .rx_array_size = sizeof(RxBuff4),
      .TxFrame = TxBuff4, .tx_array_size = sizeof(TxBuff4)  ,
      .preamble_val = 0x43, .valid = true,
      .rx_frame = Mem4RxFrame, .fix_frame = Mem4RxFrameFix,
      },
     {
    .num = TBFP_NUM_LOOPBACK,
    .inter_face = { .interface_name = INTERFACE_NAME_LOOPBACK, .num=0,},
    .RxArray = RxBuff1, .rx_array_size = sizeof(RxBuff1),
    .TxFrame = TxBuff1, .tx_array_size = sizeof(TxBuff1),
    .preamble_val = 0x4C, .valid = true,
    .rx_frame = Mem1RxFrame, .fix_frame = Mem1RxFrameFix,
    },
    {
    .num = TBFP_NUM_BLACK_HOLE,
    .inter_face = { .interface_name = INTERFACE_NAME_BLACKHOLE, .num=0,},
    .RxArray = RxBuff2, .rx_array_size = sizeof(RxBuff2),
    .TxFrame = TxBuff2, .tx_array_size = sizeof(TxBuff2),
    .preamble_val = 0x42, .valid = true,
    .rx_frame = Mem2RxFrame, .fix_frame = Mem2RxFrameFix,
    },
};

TbfpHandle_t TbfpInstance[] = {
    {.num = TBFP_NUM_CAN0, .valid = true,},
    {.num = TBFP_NUM_CAN1, .valid = true,},
    {.num = TBFP_NUM_LOOPBACK, .valid = true,},
    {.num = TBFP_NUM_BLACK_HOLE, .valid = true,},
};


COMPONENT_GET_CNT(Tbfp, tbfp)

