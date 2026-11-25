#include "can_mcal.h"

#include "can.h"
#include "can_core.h"
#include "can_enhanced_fifo.h"
#include "can_legacy_fifo.h"
#include "can_mailbox_config.h"
#include "can_message_buffer.h"
#include "can_misc.h"
#include "can_node.h"
#include "can_packets.h"
#include "clock_mcal.h"
#include "code_generator.h"
#include "float_diag.h"
#include "gpio_mcal.h"
#include "log.h"

#ifdef HAS_IQUEUE
#include "iqueue.h"
#endif

#ifdef HAS_TBFP
#include "tbfp.h"
#endif

static const CanIdTypeInfo_t CanIdTypeInfo[] = {
    {
        .id_type = CAN_FRAME_ID_STANDARD,
        .IDE = CAN_ID_STD,
        .IdType = FLEXCAN_ID_STD,
    },
    {
        .id_type = CAN_FRAME_ID_EXTENDED,
        .IDE = CAN_ID_EXT,
        .IdType = FLEXCAN_ID_EXT,
    },
};

#ifdef HAS_CAN0
canPacket_t Can0Packet[3];
FLEXCAN_HandleType hCan0 = {.eInstance = FLEXCAN_INSTANCE_0};
#endif

#ifdef HAS_CAN1
canPacket_t Can1Packet[3] = {0};
FLEXCAN_HandleType hCan1 = {.eInstance = FLEXCAN_INSTANCE_1};
#endif

#ifdef HAS_CAN2
canPacket_t Can2Packet[3] = {0};
FLEXCAN_HandleType hCan2 = {.eInstance = FLEXCAN_INSTANCE_2};
#endif

#ifdef HAS_CAN3
canPacket_t Can3Packet[3] = {0};
FLEXCAN_HandleType hCan3 = {.eInstance = FLEXCAN_INSTANCE_3};
#endif

#ifdef HAS_CAN4
canPacket_t Can4Packet[3] = {0};
FLEXCAN_HandleType hCan4 = {.eInstance = FLEXCAN_INSTANCE_4};
#endif

#ifdef HAS_CAN5
canPacket_t Can5Packet[3] = {0};
FLEXCAN_HandleType hCan5 = {.eInstance = FLEXCAN_INSTANCE_5};
#endif

#ifdef HAS_CAN6
canPacket_t Can6Packet[3] = {0};
FLEXCAN_HandleType hCan6 = {.eInstance = FLEXCAN_INSTANCE_6};
#endif

#ifdef HAS_CAN7
canPacket_t Can7Packet[3] = {0};
FLEXCAN_HandleType hCan7 = {.eInstance = FLEXCAN_INSTANCE_7};
#endif

#ifdef HAS_CAN8
canPacket_t Can8Packet[3] = {0};
FLEXCAN_HandleType hCan8 = {.eInstance = FLEXCAN_INSTANCE_8};
#endif

#ifdef HAS_CAN9
canPacket_t Can9Packet[3] = {0};
FLEXCAN_HandleType hCan9 = {.eInstance = FLEXCAN_INSTANCE_9};
#endif

uint8_t CanResToRet(const bool res) {
    uint8_t ret = CAN_RET_ERR;
    if(res) {
        ret = CAN_RET_OK;
    } else {
        ret = CAN_RET_ERR;
    }
    return ret;
}

bool CanFsRetToRes(const FLEXCAN_ErrorType ret) {
    bool res = false;
    switch(ret) {
    case FLEXCAN_E_OK:
        res = true;
        break;
    case FLEXCAN_E_INVALID_VERSION:
        res = false;
        break;
    case FLEXCAN_E_FAILED:
        res = false;
        break;
    case FLEXCAN_E_INVALID_PARAM:
        res = false;
        break;
    case FLEXCAN_E_INVALID_SIZE:
        res = false;
        break;
    case FLEXCAN_E_INVALID_SEQUENCE:
        res = false;
        break;
    case FLEXCAN_E_NULL_POINT:
        res = false;
        break;
    case FLEXCAN_E_TIMEOUT:
        res = false;
        break;
    case FLEXCAN_E_BUSY:
        res = false;
        break;
    case FLEXCAN_E_MB_OUTOFRANGE:
        res = false;
        break;
    default:
        break;
    }
    return res;
}

bool can_init_custom(void) {
    LOG_WARNING(CAN, "InitCustom");
    return true;
}

static uint32_t CanIdTypeToIde(const CanIdentifier_t id_type) {
    uint32_t ide = FLEXCAN_ID_STD;
    uint32_t i = 0;
    for(i = 0; i < 2; i++) {
        if(id_type == CanIdTypeInfo[i].id_type) {
            ide = CanIdTypeInfo[i].IDE;
        }
    }
    return ide;
}

static uint8_t TxDataFuncPack(canPacket_t* pPacket, uint8_t* pAddr) {
    uint8_t tx_len = 0;
    if(pPacket) {
        tx_len = (uint8_t)pPacket->pTP->DataBytes;
        memcpy(pAddr, pPacket->pTP->pData, tx_len);
    }
    return tx_len;
}

static bool CanMessageToCanPacket(const CanMessage_t* const Message, canPacket_t* const TxPacket) {
    bool res = false;
    if(Message) {
        if(TxPacket) {
            TxPacket->isJ1939 = false;
            TxPacket->Id = Message->identifier.extended;
            TxPacket->isEnabled = true;
            TxPacket->sendOnce = true;
            TxPacket->period = 1;
            TxPacket->IDE = CanIdTypeToIde(Message->id_type);
            TxPacket->pFuncPack = TxDataFuncPack; /*BYTE_CAN_PACK_FUNC_t*/
            if(TxPacket->pTP) {
                TxPacket->pTP->pData = Message->data;
                TxPacket->pTP->DataBytes = Message->size;
                TxPacket->pTP->InProgress = true;
                res = true;
            }
        }
    }
    return res;
}

static bool can_init_slot(canTxSlot_t* const Slot, const canPacket_t* const pPacket) {
    bool res = false;
    if(Slot) {
        if(pPacket) {
            // Slot->mailbox = 1;
            Slot->status = CAN_SLOT_PENDING;
            Slot->pPacket = pPacket;
            res = true;
        }
    }
    return res;
}

bool can_mcal_transmit_message(uint8_t num, const CanMessage_t* const Message) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        res = CanMessageToCanPacket(Message, &canTxPackets.TxPacket);
        canTxPackets.TxPacket.isSent = false;
        canTxPackets.TxPacket.sentCntr++;
        canTxPackets.TxPacket.waitTime = 1;
        canTxPackets.TxPacket.pNode = Node->pCanNode;
        canTxPackets.TxPacket.state = P_IDLE;
        if(canTxPackets.TxPacket.pSlot) {
            canTxPackets.TxPacket.pSlot->status = CAN_SLOT_PENDING;
            res = true;
        }
        // Node->pCanNode->hcan=0;

        if(Node->pCanNode->pTxSlots) {
            can_init_slot(&(Node->pCanNode->pTxSlots->slot[0]), &canTxPackets.TxPacket);
            // can_init_slot(&(Node->pCanNode->pTxSlots->slot[1]),  &canTxPackets.TxPacket);
            // can_init_slot(&(Node->pCanNode->pTxSlots->slot[2]),  &canTxPackets.TxPacket);
        }

        // canTxPackets.TxPacket.pFuncPack = ;
        // canTxPackets.TxPacket.txCntr = 0;
        // canTxPackets.TxPacket.txErrCntr = 0;
    }
    return res;
}

static bool CanInitCanNode(const CanInfo_t* const Info, CanHandle_t* const Node, canNode_t* const canNode) {
    bool res = false;
    if(Info) {
        if(canNode) {
            Node->pCanNode = Info->pCanNode;
            Node->pCanNode->hcan = Info->pHandle;
            Node->pCanNode->hcan->eInstance = Info->e_instance;
            canNode->pJ1939tp = NULL;
            //     canNode->pTxSlots = Info->pTxSlots;
            canNode->rxMsg.u8CanIndex = Info->num;
            canNode->rxMsg.u8RxHandle = 0xFF;
            canNode->rxMsg.bEnFd = 0;
            canNode->rxMsg.bEnBrs = 0;
            canNode->rxMsg.eFrameType = FLEXCAN_ID_EXT;
            canNode->rxMsg.eDataType = FLEXCAN_FRAME_DATA;
            canNode->rxMsg.u32CanId = 0x55;
            canNode->rxMsg.u32DataLen = 8;
            memset(canNode->rxMsg.aData, 0, sizeof(canNode->rxMsg.aData));
            res = true;
#if 0
            if(Node->pCanNode->hcan) {
                canNode->hcan = Node->pCanNode->hcan; //(FLEXCAN_HandleType* )
                res = true;
            }
#endif
        }
    }
    return res;
}

static bool can_init_callback(const CanInfo_t* const Info, CanHandle_t* const Node) {
    bool res = true;
    Node->pCanNode->hcan->tSettings.pErrorNotify = Info->Call_Back_Error;
    Node->pCanNode->hcan->tSettings.pFifoIssueNotify = Info->Call_Back_Fifo_Issue;
    Node->pCanNode->hcan->tSettings.pTxNotify = Info->Call_Back_Tx;
    Node->pCanNode->hcan->tSettings.pRxNotify = Info->Call_Back_Rx;
    Node->pCanNode->hcan->tSettings.pWakeNotify = Info->Call_Back_Wake;
    return res;
}

static bool can_init_by_info_common(const CanInfo_t* const Info, CanHandle_t* const Node) {
    bool res = false;
    if(Info) {
        if(Node) {
            Node->num = Info->num;
            Node->valid = true;
            if(Info->pHandle) {
                Node->pCanNode->hcan = Info->pHandle;
                if(Info->CANx) {
                    Node->CANx = Info->CANx;
                    res = true;
                }
            }
            Node->pCanNode = Info->pCanNode;
            res = can_init_callback(Info, Node);
        }
    }
    return res;
}

static bool can_transmit_message_sdk(CanHandle_t* const Node, const FLEXCAN_TxMsgType* const TxMsg) {
    bool res = false;
    if(Node) {
        FLEXCAN_ErrorType ret = FLEXCAN_E_FAILED;
        ret = FLEXCAN_TransmitData(Node->pCanNode->hcan, TxMsg);
        res = CanRetToRes(ret);
        if(res) {
            LOG_DEBUG(CAN, "CAN%u,TxOk,%s", Node->num, CanTxMessageToStr(TxMsg));
        } else {
            LOG_ERROR(CAN, "%s", CanErrorToStr(ret));
        }
    }
    return res;
}

static uint8_t can_tx_message_buffer_get(const uint8_t num) {
    uint8_t tx_message_buffer = 0;
    uint32_t i = 0;
    uint32_t cnt = can_mailbox_get_cnt();
    for(i = 0; i < cnt; i++) {
        bool is_my_mb = CHECK_BIT_NUM(CanMessageBufferConfig[i].cans.word, num);
        if(is_my_mb) {
            if(CONNECT_DIR_TRANSMIT == CanMessageBufferConfig[i].direction) {
                tx_message_buffer = CanMessageBufferConfig[i].mb_index;
                break;
            }
        }
    }
    return tx_message_buffer;
}

static bool CanMessageToFlexCanTxMsg(uint8_t num, const CanMessage_t* const Message, FLEXCAN_TxMsgType* const Msg) {
    bool res = false;
    if(Message) {
        if(Msg) {
#ifdef HAS_CAN_FD
            Msg->bEnFd = Message->is_fd;
            Msg->bEnBrs = CanFdBitRateSwitchToBrs(Message->bit_rate_switch);
#else
            Msg->bEnBrs = CAN_FD_BIT_RATE_SWITCH_OFF;
            Msg->bEnFd = 0;
#endif
            Msg->eDataType = CanFrameTypeToDataType(Message->frame_type);
            Msg->eFrameType = CanMessageIdTyoeToFrameType(Message->id_type);
            Msg->u32CanId = Message->identifier.standard;
            memcpy(Msg->aData, Message->data, CAN_MAX_PAYLOAD_SIZE);
            Msg->u32DataLen = (uint32_t)Message->size;
            Msg->u8TxHandle = can_tx_message_buffer_get(num);
            res = true;
        }
    }
    return res;
}

static FLEXCAN_ClockSrcType CanClkSrcToClockSrcType(CanClockSource_t clock_source) {
    FLEXCAN_ClockSrcType clock_src = FLEXCAN_CLOCK_INTERFACE;
    switch(clock_source) {
    case CAN_CLOCK_SOURCE_PERIPHERAL: {
        clock_src = FLEXCAN_CLOCK_CANPE;
    } break;
    case CAN_CLOCK_SOURCE_OSCILLATOR: {
        clock_src = FLEXCAN_CLOCK_INTERFACE;
    } break;
    default:
        break;
    }
    return clock_src;
}

/* Normal bit table */
const CAN_BaudRegType s_aFlexCan_NormalBaudDividerTable[] = {
    /* clock source hz          baudrate             presdiv    propseg   pseg1   pseg2   rjw  */
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_16M, .eBaudrate = FLEXCAN_BAUD_500K, .u32Presdiv = 2, 8, 4, 3, 2},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_24M, .eBaudrate = FLEXCAN_BAUD_20K, .u32Presdiv = 60, 7, 6, 6, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_24M, .eBaudrate = FLEXCAN_BAUD_50K, .u32Presdiv = 24, 7, 6, 6, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_24M, .eBaudrate = FLEXCAN_BAUD_100K, .u32Presdiv = 12, 7, 6, 6, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_24M, .eBaudrate = FLEXCAN_BAUD_125K, .u32Presdiv = 12, 5, 5, 5, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_24M, .eBaudrate = FLEXCAN_BAUD_250K, .u32Presdiv = 8, 5, 3, 3, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_24M, .eBaudrate = FLEXCAN_BAUD_500K, .u32Presdiv = 4, 5, 3, 3, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_24M, .eBaudrate = FLEXCAN_BAUD_800K, .u32Presdiv = 3, 5, 2, 2, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_24M, .eBaudrate = FLEXCAN_BAUD_1M, .u32Presdiv = 2, 5, 3, 3, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_24M, .eBaudrate = FLEXCAN_BAUD_2M, .u32Presdiv = 1, 5, 3, 3, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_48M, .eBaudrate = FLEXCAN_BAUD_20K, .u32Presdiv = 160, 8, 3, 3, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_48M, .eBaudrate = FLEXCAN_BAUD_50K, .u32Presdiv = 64, 8, 3, 3, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_48M, .eBaudrate = FLEXCAN_BAUD_100K, .u32Presdiv = 32, 8, 3, 3, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_48M, .eBaudrate = FLEXCAN_BAUD_125K, .u32Presdiv = 24, 7, 4, 4, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_48M, .eBaudrate = FLEXCAN_BAUD_250K, .u32Presdiv = 24, 3, 2, 2, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_48M, .eBaudrate = FLEXCAN_BAUD_500K, .u32Presdiv = 6, 7, 4, 4, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_48M, .eBaudrate = FLEXCAN_BAUD_800K, .u32Presdiv = 4, 8, 3, 3, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_48M, .eBaudrate = FLEXCAN_BAUD_1M, .u32Presdiv = 3, 7, 4, 4, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_48M, .eBaudrate = FLEXCAN_BAUD_2M, .u32Presdiv = 2, 5, 3, 3, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_120M, .eBaudrate = FLEXCAN_BAUD_50K, .u32Presdiv = 160, 8, 3, 3, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_120M, .eBaudrate = FLEXCAN_BAUD_100K, .u32Presdiv = 80, 8, 3, 3, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_120M, .eBaudrate = FLEXCAN_BAUD_125K, .u32Presdiv = 64, 8, 3, 3, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_120M, .eBaudrate = FLEXCAN_BAUD_250K, .u32Presdiv = 32, 8, 3, 3, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_120M, .eBaudrate = FLEXCAN_BAUD_500K, .u32Presdiv = 16, 8, 3, 3, 3},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_120M, .eBaudrate = FLEXCAN_BAUD_800K, .u32Presdiv = 15, 5, 2, 2, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_120M, .eBaudrate = FLEXCAN_BAUD_1M, .u32Presdiv = 8, 8, 3, 3, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_120M, .eBaudrate = FLEXCAN_BAUD_2M, .u32Presdiv = 4, 8, 3, 3, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_150M, .eBaudrate = FLEXCAN_BAUD_500K, .u32Presdiv = 20, 8, 3, 3, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_150M, .eBaudrate = FLEXCAN_BAUD_1M, .u32Presdiv = 10, 8, 3, 3, 1},
    {.eClkHz = FLEXCAN_BAUDCLK_HZ_150M, .eBaudrate = FLEXCAN_BAUD_2M, .u32Presdiv = 5, 8, 3, 3, 1}

};

/* Data bit table */
const CAN_BaudRegType s_aFlexCan_DataBaudDividerTable[] = {
    /* clock source hz          baudrate             presdiv    propseg   pseg1   pseg2   rjw  */
    {FLEXCAN_BAUDCLK_HZ_16M, FLEXCAN_BAUD_2M, 1, 3, 2, 2, 1},
    {FLEXCAN_BAUDCLK_HZ_24M, FLEXCAN_BAUD_1M, 2, 5, 3, 3, 1},
    {FLEXCAN_BAUDCLK_HZ_24M, FLEXCAN_BAUD_2M, 1, 5, 3, 3, 1},
    {FLEXCAN_BAUDCLK_HZ_24M, FLEXCAN_BAUD_3M, 1, 3, 2, 2, 1},
    {FLEXCAN_BAUDCLK_HZ_48M, FLEXCAN_BAUD_1M, 3, 7, 4, 4, 1},
    {FLEXCAN_BAUDCLK_HZ_48M, FLEXCAN_BAUD_2M, 2, 5, 3, 3, 1},
    {FLEXCAN_BAUDCLK_HZ_48M, FLEXCAN_BAUD_3M, 1, 7, 4, 4, 1},
    {FLEXCAN_BAUDCLK_HZ_48M, FLEXCAN_BAUD_4M, 1, 5, 3, 3, 1},
    {FLEXCAN_BAUDCLK_HZ_48M, FLEXCAN_BAUD_6M, 1, 3, 2, 2, 1},
    {FLEXCAN_BAUDCLK_HZ_120M, FLEXCAN_BAUD_1M, 8, 8, 3, 3, 1},
    {FLEXCAN_BAUDCLK_HZ_120M, FLEXCAN_BAUD_2M, 4, 8, 3, 3, 1},
    {FLEXCAN_BAUDCLK_HZ_120M, FLEXCAN_BAUD_3M, 4, 5, 2, 2, 1},
    {FLEXCAN_BAUDCLK_HZ_120M, FLEXCAN_BAUD_4M, 3, 5, 2, 2, 1},
    {FLEXCAN_BAUDCLK_HZ_120M, FLEXCAN_BAUD_5M, 2, 5, 3, 3, 1},
    {FLEXCAN_BAUDCLK_HZ_120M, FLEXCAN_BAUD_6M, 2, 5, 2, 2, 1},
    {FLEXCAN_BAUDCLK_HZ_120M, FLEXCAN_BAUD_8M, 1, 8, 3, 3, 1},
    {FLEXCAN_BAUDCLK_HZ_150M, FLEXCAN_BAUD_1M, 10, 8, 3, 3, 1},
    {FLEXCAN_BAUDCLK_HZ_150M, FLEXCAN_BAUD_2M, 5, 8, 3, 3, 1},
    {FLEXCAN_BAUDCLK_HZ_150M, FLEXCAN_BAUD_3M, 5, 5, 2, 2, 1},
    {FLEXCAN_BAUDCLK_HZ_150M, FLEXCAN_BAUD_5M, 2, 8, 3, 3, 1}};

#if 0
static uint32_t can_mac_clock_get(uint8_t can_num, CanClockSource_t clock_source) {
    uint32_t mac_clock_hz = 0;
    switch (clock_source) {
        case CAN_CLOCK_SOURCE_PERIPHERAL: {
            const CanInfo_t* Info = CanGetInfo(can_num);
            if(Info ) {
                mac_clock_hz = PCC_GetPccFunctionClock(Info->e_clock_name);
            }
        }  break;
        case CAN_CLOCK_SOURCE_OSCILLATOR: {
            mac_clock_hz = SCG_GetScgClockFreq(SCG_FOSC_CLK);
        } break;
        default:
            mac_clock_hz = 0;
            break;
    }
    return mac_clock_hz;
}
#endif

uint32_t CanBitrateToPreScaler(const FLEXCAN_BaudRegType* const TimeSeg) {
    uint32_t prescaler = 0;
    uint32_t bit_dur_tq = 0;
    bit_dur_tq += TimeSeg->u32Rjw;
    bit_dur_tq += TimeSeg->u32Propseg;
    bit_dur_tq += TimeSeg->u32Pseg1;
    bit_dur_tq += TimeSeg->u32Pseg2;
    prescaler = (TimeSeg->u32Presdiv) * bit_dur_tq;
    return prescaler;
}

uint32_t CanTimeSegToBitrate(const uint32_t clk_freq_hz, const FLEXCAN_BaudRegType* const TimeSeg) {
    uint32_t prescaler = CanBitrateToPreScaler(TimeSeg);
    uint32_t bit_rate_real = clk_freq_hz / prescaler;
    return bit_rate_real;
}

bool CanMsgToMessage(uint32_t can_num, const FLEXCAN_RxMsgType* const Msg, CanMessage_t* const Message) {
    bool res = false;
    if(Msg) {
        if(Message) {
            Message->can_bus_num = can_num;
            Message->identifier.extended = Msg->u32CanId;
            Message->id_type = CanIdTypeToIdentifier(Msg->eFrameType);
            Message->size = Msg->u32DataLen;
            uint32_t min_size = DATA_MIN(sizeof(Message->data), sizeof(Msg->aData));
            memcpy(Message->data, Msg->aData, min_size);
            Message->frame_type = CanDataTypeToFrameType(Msg->eDataType);
            Message->mesg_buff_idx = 0xFF;
#ifdef HAS_CAN_FD
            Message->is_fd = Msg->bEnFd;
            Message->bit_rate_switch = CanEnBrsToFdBitRateSwitch(Msg->bEnBrs);
#endif
            res = true;
        }
    }
    return res;
}

bool CanBitRateToSegment(uint32_t clk_freq_hz, uint32_t bit_rate, FLEXCAN_BaudRegType* const TimeSeg) {
    bool res = false;
    if(bit_rate) {
        if(0 < clk_freq_hz) {
            uint32_t tq_freq_hz = bit_rate * 24;
            uint32_t tq_prescaler = calc_prescaler(clk_freq_hz, tq_freq_hz);
            LOG_INFO(CAN, "TqFreq:%u Hz,TqPsc:%u", tq_freq_hz, tq_prescaler);
            TimeSeg->u32Presdiv = tq_prescaler;
            TimeSeg->u32Rjw = 1;
            TimeSeg->u32Propseg = 7;
            TimeSeg->u32Pseg1 = 8;
            TimeSeg->u32Pseg2 = 8;

            uint32_t bit_rate_real = CanTimeSegToBitrate(clk_freq_hz, TimeSeg);
            int32_t error_hz = ((int32_t)bit_rate) - ((int32_t)bit_rate_real);
            LOG_INFO(CAN, "Set:%7u bit/s,Real:%7u bit/s,Error:%d Hz", bit_rate, bit_rate_real, error_hz);
            float bit_period_real = 1.0f / ((float)bit_rate_real);
            LOG_INFO(CAN, "BitPeriodReal:%ss", FloatBigToStr(bit_period_real));
            float sample_time_s = 1.0f / ((float)bit_rate);
            LOG_INFO(CAN, "BaseClock:%7u Hz,SampleTime:%ss,TiSeg:%s", clk_freq_hz, FloatBigToStr(sample_time_s),
                     FlexCanBaudRegToStr(TimeSeg));
            res = true;
        }
    }
    return res;
}

uint8_t BSP_CAN_LL_ProcessBaud(const FLEXCAN_InstanceType eInstance, FLEXCAN_InitType* const pInitCfg,
                               const uint32_t baudrate) {
    bool res = false;
    uint8_t ret = CAN_RET_ERR;
    uint32_t clk_freq_hz = 0;
    CanConfig_t* Config = CanGetConfig((uint8_t)eInstance);
    if(Config) {
        pInitCfg->eClkSrcSel = CanClkSrcToClockSrcType(Config->clock_source);
        clk_freq_hz = can_base_clock_get((uint8_t)eInstance);
        // clk_freq_hz = can_base_clock_get(Config->num);
    }

    if(clk_freq_hz) {
        res = CanBitRateToSegment(clk_freq_hz, baudrate, &pInitCfg->tNormalBaud);

        if(pInitCfg->bEnFd) {
            CanBitRateToSegment(clk_freq_hz, 3 * baudrate, &pInitCfg->tFdBaud);
        } else {
            CanBitRateToSegment(clk_freq_hz, baudrate, &pInitCfg->tFdBaud);
        }
    }

    ret = CanResToRet(res);

    return ret;
}

bool can_mcal_transmit_message_sdk(uint8_t num, const CanMessage_t* const Message) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        FLEXCAN_TxMsgType TxMsg = {0};
        res = CanMessageToFlexCanTxMsg(num, Message, &TxMsg);
        res = can_transmit_message_sdk(Node, &TxMsg);
    }
    return res;
}

static bool can_proc_mcr(CanHandle_t* Node) {
    bool res = true;
    CanRegMCR_t MCR;
    (void)MCR;
    MCR.dword = FLEXCAN_HWA_GetMCR(Node->CANx);

    if(MCR.NOTRDY) {
        LOG_ERROR(CAN, "CAN%u,NotReady", Node->num);
        res = false;
    }

    if(CAN_MCR_MDIS_DISABLE == MCR.MDIS) {
        LOG_ERROR(CAN, "CAN%u,ModuleDisabled", Node->num);
        /* When disabled, the FLEXCAN disables the clocks to the PE and CHI submodules.
           MDIS is not affected by soft reset.*/
        res = false;
    }

    if(MCR.FRZACK) {
        LOG_ERROR(CAN, "CAN%u,FreezeAck", Node->num);
        res = false;
    }

    if(MCR.LPMACK) {
        LOG_ERROR(CAN, "CAN%u,LowPowerAck", Node->num);
        res = false;
    }

    return res;
}

static bool can_proc_esr1_errors(CanHandle_t* Node) {
    bool res = true;
    if(Node->ESR1.CRCERR) {
        LOG_ERROR(CAN, "CAN%u,CrcErr", Node->num);
        Node->ESR1.CRCERR = 0;
        Node->error = true;
        res = false;
    }

    if(Node->ESR1.ERRINT) {
        LOG_ERROR(CAN, "CAN%u,Error!", Node->num);
        Node->ESR1.ERRINT = 0;
        Node->re_init = true;
        Node->error = true;
        res = false;
    }
    if(Node->ESR1.ACKERR) {
        LOG_ERROR(CAN, "CAN%u,AckErr", Node->num);
        Node->ESR1.ACKERR = 0;
        Node->error = true;
        res = false;
    }
    if(Node->ESR1.ERROVR) {
        LOG_ERROR(CAN, "CAN%u,OverrunErr", Node->num);
        Node->ESR1.ERROVR = 0;
        Node->re_init = true;
        Node->error = true;
        res = false;
    }
    if(Node->ESR1.BIT1ERR) {
        LOG_ERROR(CAN, "CAN%u,Bit1Err", Node->num);
        Node->ESR1.BIT1ERR = 0;
        Node->error = true;
        Node->re_init = true;
        res = false;
    }
    if(Node->ESR1.BIT0ERR) {
        LOG_ERROR(CAN, "CAN%u,Bit0Err", Node->num);
        Node->ESR1.BIT0ERR = 0;
        Node->re_init = true;
        Node->error = true;
        res = false;
    }
    if(Node->ESR1.FRMERR) {
        /*Wrong Bit Rate*/
        LOG_ERROR(CAN, "CAN%u,FormErr", Node->num);
        Node->ESR1.FRMERR = 0;
        Node->re_init = true;
        Node->error = true;
        res = false;
    }

    if(Node->ESR1.STFERR) {
        LOG_ERROR(CAN, "CAN%u,StuffingErr(BitRateWrong)", Node->num);
        Node->ESR1.STFERR = 0;
        Node->error = true;
        Node->re_init = true;
        res = false;
    }
    if(Node->ESR1.BOFFINT) {
        LOG_ERROR(CAN, "CAN%u,InBusOff", Node->num);
        Node->ESR1.BOFFINT = 0;
        Node->error = true;
        res = false;
    }
    if(Node->ESR1.BOFFDONEINT) {
        LOG_ERROR(CAN, "CAN%u,BusOff!", Node->num);
        Node->ESR1.BOFFDONEINT = 0;
        Node->re_init = true;
        Node->error = true;
        res = false;
    }
    return res;
}

static bool can_proc_esr1_warning(CanHandle_t* Node) {
    bool res = true;
    if(Node->ESR1.TWRNINT) {
        LOG_WARNING(CAN, "CAN%u,96<=TxErrCnt", Node->num);
        Node->ESR1.TWRNINT = 0;
    }

    if(Node->ESR1.RWRNINT) {
        LOG_WARNING(CAN, "CAN%u,96<=RxErrCnt", Node->num);
        Node->ESR1.RWRNINT = 0;
    }
    if(Node->ESR1.TXWRN) {
        LOG_WARNING(CAN, "CAN%u,TxWarn", Node->num);
        Node->ESR1.TXWRN = 0;
    }

    if(Node->ESR1.RXWRN) {
        LOG_WARNING(CAN, "CAN%u,RxErr", Node->num);
        Node->ESR1.RXWRN = 0;
    }

    return res;
}

static bool can_proc_esr1_notice(CanHandle_t* Node) {
    bool res = true;
    if(Node->ESR1.SYNCH) {
        LOG_PARN(CAN, "CAN%u,Synchronized", Node->num);
        Node->ESR1.SYNCH = 0;
    } else {
        LOG_PARN(CAN, "CAN%u,IsNotSynchronizedBus", Node->num);
    }

    if(Node->ESR1.IDLE) {
        LOG_PARN(CAN, "CAN%u,Idle", Node->num);
        Node->ESR1.IDLE = 0;
    }

    if(Node->ESR1.TX) {
        LOG_DEBUG(CAN, "CAN%u,Transmitting...", Node->num);
        Node->ESR1.TX = 0;
    }

    if(Node->ESR1.RX) {
        LOG_DEBUG(CAN, "CAN%u,Receiving...", Node->num);
        Node->ESR1.RX = 0;
    }

    return res;
}

static bool can_proc_esr1(CanHandle_t* Node) {
    bool res = true;
    Node->ESR1.dword = FLEXCAN_HWA_GetErrorInfo(Node->CANx);
    res = can_proc_esr1_errors(Node);
    res = can_proc_esr1_warning(Node);
    res = can_proc_esr1_notice(Node);
    return res;
}

bool can_phy_disconnect(uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        res = gpio_deinit_pad(Node->PadTx);
        res = gpio_deinit_pad(Node->PadRx) && res;
    }
    return res;
}

bool can_phy_connect(uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        res = gpio_init_pad(Node->PadTx);
        res = gpio_init_pad(Node->PadRx) && res;
    }
    return res;
}

static bool can_proc_iflags(const CanHandle_t* const Node) {
    bool res = false;
    CanRegIFLAG1_t IFLAG1;
    IFLAG1.dword = FLEXCAN_HWA_GetFlag1(Node->CANx);
    uint32_t i = 0;
    for(i = 0; i < 32; i++) {
        bool flag = CHECK_BIT_NUM(IFLAG1.dword, i);
        if(flag) {
            LOG_INFO(CAN, "CAN%u,MesgBuffer%u,MoveDone", Node->num, i);
            res = true;
        }
    }
    return res;
}

bool can_is_tx_done(const uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        if(Node->pCanNode) {
            res = Node->pCanNode->tx_done;
        }
    }
    return res;
}

bool can_tx_done_reset(const uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        if(Node->pCanNode) {
            Node->pCanNode->tx_done = false;
            res = true;
        }
    }
    return res;
}

/*
 Check if this CAN can receive this ID according to the configuration.
 */
bool can_is_my_id(const uint8_t num, const uint32_t can_id) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        CanMacMode_t mac_mode = can_get_mac_mode(num);
        switch(mac_mode) {
        case CAN_MAC_MODE_LEGACY_FIFO: {
#ifdef HAS_CAN_LEGACY_FIFO
            res = can_legacy_fifo_id_check(num, can_id);
#endif
        } break;
        case CAN_MAC_MODE_ENHANCED_FIFO: {
#ifdef HAS_CAN_ENHANCED_FIFO
            res = can_enhanced_id_check(num, can_id);
#endif
        } break;
        case CAN_MAC_MODE_MESSAGE_BUFFER: {
#ifdef HAS_CAN_MESSAGE_BUFFER
            res = can_message_buffer_id_check(num, can_id);
#endif
        } break;
        default:
            res = false;
            break;
        }
    }
    return res;
}

bool can_health_monitor_proc_one(uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        CanRegMCR_t MCR;
        MCR.dword = Node->CANx->MCR;
        if(MCR.NOTRDY) {
            LOG_ERROR(CAN, "CAN%u,NotReady", num);
        }

        if(MCR.FRZACK) {
            LOG_ERROR(CAN, "CAN%u,inFreezeMode", num);
        }

        bool on_off = false;
        res = can_loopback_get(num, &on_off);
        if(on_off) {
            LOG_WARNING(CAN, "CAN%u,InLoopBackMode", num);
        }
    }
    return res;
}

static bool can_proc_error_ll(CanHandle_t* const Node) {
    bool res = true;
    res = can_freeze_get(Node->num);
    if(res) {
        LOG_ERROR(CAN, "CAN%u,InFreeze", Node->num);
    }

    uint32_t tec = 0;
    res = can_tec_get(Node->num, &tec);
    if(tec) {
        LOG_ERROR(CAN, "CAN%u,TEC:%u", Node->num, tec);
        Node->re_init = true;
    }

    uint32_t rec = 0;
    res = can_rec_get(Node->num, &rec);
    if(rec) {
        LOG_ERROR(CAN, "CAN%u,REC:%u", Node->num, rec);
        Node->error = true;
        Node->error_for_test = true;
        Node->re_init = true;
    }

    if(Node->error_bus_off) {
        LOG_ERROR(CAN, "CAN%u,ErrBusOff,%u", Node->num, Node->error_bus_off_cnt);
        Node->error_bus_off = false;
        Node->re_init = true;
        Node->error = true;
        res = false;
    }

    if(Node->error_bus_off_done) {
        LOG_ERROR(CAN, "CAN%u,ErrBusOffDone,%u", Node->num, Node->error_bus_off_done_cnt);
        Node->error_bus_off_done = false;
        Node->error = true;
        Node->re_init = true;
        res = false;
    }

    if(Node->error_data_phase) {
        LOG_ERROR(CAN, "CAN%u,ErrDataPhase,%u", Node->num, Node->error_data_phase_cnt);
        Node->error_data_phase = false;
        Node->error = true;
        Node->re_init = true;
        res = false;
    }

    if(Node->error) {
        LOG_ERROR(CAN, "CAN%u,Error,%u", Node->num, Node->error_cnt);
        Node->error = true;
        Node->re_init = true;
        res = false;
    }

    if(Node->error_overrun) {
        LOG_ERROR(CAN, "CAN%u,ErrOverrun,%u", Node->num, Node->error_overrun_cnt);
        Node->error_overrun = false;
        Node->error = true;
        Node->re_init = true;
        res = false;
    }
    return res;
}

static bool can_proc_warning_ll(CanHandle_t* Node) {
    bool res = false;
    if(Node->warning_tx) {
        LOG_ERROR(CAN, "CAN%u,warningTx,%u", Node->num, Node->warning_tx_cnt);
        Node->warning_tx = false;
    }

    if(Node->warning_rx) {
        LOG_ERROR(CAN, "CAN%u,warningRx,%u", Node->num, Node->warning_rx_cnt);
        Node->warning_rx = false;
    }

    return res;
}

static bool can_proc_rx_packet(const uint8_t num, const CanMessage_t* const pRxMessage) {
    bool res = false;
    LOG_NOTICE(CAN, "CAN%u,Rx:%s", num, CanMessageToStr(pRxMessage));
#ifdef HAS_ISO_TP
    uint8_t iso_tp_num = iso_tp_can_num_to_iso_tp_num(num);
    res = iso_tp_rx_message(iso_tp_num, pRxMessage);
#endif

#ifdef HAS_TBFP
    InterfaceType_t ifCan = {
        .interface_name = INTERFACE_NAME_CAN,
        .num = num,
    };
    res = tbfp_data_rx(ifCan, pRxMessage->data, pRxMessage->size);
#endif
    return res;
}

bool can_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(CAN, "CAN%u,Proc", num);
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        canTxHandler(Node->pCanNode);

        res = can_proc_mcr(Node);
        res = can_proc_esr1(Node);
        res = can_proc_erfsr(Node);
        res = can_proc_iflags(Node);
        res = can_proc_error_ll(Node);
        res = can_proc_warning_ll(Node);

#ifdef HAS_IQUEUE
        InterfaceType_t ifCan = {
            .interface_name = INTERFACE_NAME_CAN,
            .num = num,
        };
        iQueueHandle_t* iQueue = iQueueInterfaceToNode(ifCan);
        if(iQueue) {
            CanMessage_t RxMessage = {0};
            i_status ret = iqueue_dequeue(iQueue->pHandle, &RxMessage);
            res = iqueue_ret_res(ret);
            if(res) {
                res = can_proc_rx_packet(num, &RxMessage);
            }
        }
#else
        if(Node->unproc_rx_message) {
            res = can_proc_rx_packet(num, &Node->RxMessage);
            Node->unproc_rx_message = false;
        }
#endif
        // FLEXCAN_PollingProcess(Node->pCanNode->hcan); // cause HardFault_Handler
        if(Node->re_init) {
            res = can_init_one(num);
        }
        Node->spin++;
    }
    return res;
}

bool can_init_one(uint8_t num) {
    bool res = false;
    const CanConfig_t* Config = CanGetConfig(num);
    const CanInfo_t* Info = CanGetInfo(num);
    CanHandle_t* Node = CanGetNode(num);
    if(Info) {
        LOG_WARNING(CAN, "SpotCAN:%s", CanInfoToStr(Info));
        res = CanIsValidInfo(Info);
        if(res) {
            if(Config) {
                LOG_WARNING(CAN, "SpotCfg:%s", CanConfigToStr(Config));
                res = CanIsValidConfig(Config);
            }
        }
    }

    if(res) {
        res = clock_init_peripheral2(Info->e_clock_name, PCC_CLKGATE_SRC_FOSCDIV, PCC_CLK_DIV_BY1);
        if(res) {
            if(Node) {
                res = can_init_common(Config, Node);
                res = can_init_node(Node);
            }
        }
    }

    if(res) {
        res = can_init_by_info_common(Info, Node);
        if(res) {
            res = CanInitCanNode(Info, Node, Node->pCanNode);
            if(res) {
                res = can_reset_error_counters(num);
                FLEXCAN_ErrorType ret = FLEXCAN_E_FAILED;
                ret = CAN_NodeInit(Node->pCanNode, Config->bit_rate);
                res = CanFsRetToRes(ret);
                if(FLEXCAN_E_OK == ret) {
                    LOG_INFO(CAN, "InitOk");
                } else {
                    LOG_ERROR(CAN, "Init,%u=%s,Err", ret, CanFlexErrorToStr(ret));
                }
            }
        }
    }
    return res;
}
