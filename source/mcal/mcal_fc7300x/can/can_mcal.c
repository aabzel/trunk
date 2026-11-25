#include "can_mcal.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "array.h"
#include "can_custom_drv.h"
#include "clock/clock.h"
#include "clock_YTM32B1Mx.h"
#include "code_generator.h"
#include "common_diag.h"
#include "data_utils.h"
#include "led_rgb_drv.h"
#include "log.h"
#include "microcontroller_const.h"
#include "flexcan_hw_access.h"
#include "time_mcal.h"
#include "fc7300x_misc.h"


CanIdentifier_t CanFc73MsgIdTypeToIdType(flexcan_msgbuff_id_type_t msgIdType){
	CanIdentifier_t id_type = CAN_FRAME_ID_STANDARD;
    switch(msgIdType) {
        case FLEXCAN_MSG_ID_STD:id_type = CAN_FRAME_ID_STANDARD; break;
        case FLEXCAN_MSG_ID_EXT:id_type = CAN_FRAME_ID_EXTENDED; break;
        default:id_type = CAN_FRAME_ID_STANDARD; break;
    }
    return id_type ;
}

static flexcan_operation_modes_t CanModeToFlexCanMode(CanMode_t mode) {
    /* User configurable FlexCAN operation modes.                                                                     */
    flexcan_operation_modes_t flex_can_mode = FLEXCAN_DISABLE_MODE;
    switch(mode) {
    case CAN_CFG_MODE_COMMUNICATE:
        flex_can_mode = FLEXCAN_NORMAL_MODE;
        break;
    case CAN_CFG_MODE_LISTENONLY:
        flex_can_mode = FLEXCAN_LISTEN_ONLY_MODE;
        break;
    case CAN_CFG_MODE_LOOPBACK:
        flex_can_mode = FLEXCAN_LOOPBACK_MODE;
        break;
    case CAN_CFG_MODE_LISTENONLY_LOOPBACK:
        flex_can_mode = FLEXCAN_LOOPBACK_MODE;
        break;
    case CAN_CFG_MODE_FREEZE:
        flex_can_mode = FLEXCAN_FREEZE_MODE;
        break;
    default:
        flex_can_mode = FLEXCAN_DISABLE_MODE;
        break;
    }
    return flex_can_mode;
}


static flexcan_msgbuff_id_type_t CanIdentifierToMesgIdType(CanIdentifier_t identifier) {
    flexcan_msgbuff_id_type_t msg_id_type = FLEXCAN_MSG_ID_STD;
    switch(identifier) {
    case CAN_FRAME_ID_STANDARD:
        msg_id_type = FLEXCAN_MSG_ID_STD;
        break;
    case CAN_FRAME_ID_EXTENDED:
        msg_id_type = FLEXCAN_MSG_ID_EXT;
        break;
    default:
        break;
    }
    return msg_id_type;
}

static volatile uint8_t rx_buff[CAN_COUNT][1];

static const CanInfo_t CanInfo[] = {
#ifdef HAS_CAN0
    {
        .num = 0,
        .valid = true,
        .CANx = CAN0,

        .irq_n_error = CAN0_Error_IRQn,
        .irq_n_wake_up = CAN0_Wake_Up_IRQn,
        .irq_n_ored = CAN0_ORed_IRQn,
        .irq_n_ored_0_15_mb = CAN0_ORed_0_15_MB_IRQn,
        .irq_n_ored_16_31_mb = CAN0_ORed_16_31_MB_IRQn,
        .irq_n_ored_32_47_mb = CAN0_ORed_32_47_MB_IRQn,
        .irq_n_ored_48_63_mb = CAN0_ORed_48_63_MB_IRQn,
    },
#endif

#ifdef HAS_CAN1
    {
        .num = 1,
        .valid = true,
        .CANx = CAN1,

        .irq_n_error = CAN1_Error_IRQn,
        .irq_n_wake_up = CAN1_Wake_Up_IRQn,
        .irq_n_ored = CAN1_ORed_IRQn,
        .irq_n_ored_0_15_mb = CAN1_ORed_0_15_MB_IRQn,
        .irq_n_ored_16_31_mb = CAN1_ORed_16_31_MB_IRQn,
        .irq_n_ored_32_47_mb = CAN1_ORed_32_47_MB_IRQn,
        .irq_n_ored_48_63_mb = CAN1_ORed_48_63_MB_IRQn,
    },
#endif

#ifdef HAS_CAN2
    {
        .num = 2,
        .valid = true,
        .CANx = CAN2,

        .irq_n_error = CAN2_Error_IRQn,
        .irq_n_wake_up = CAN2_Wake_Up_IRQn,
        .irq_n_ored = CAN2_ORed_IRQn,
        .irq_n_ored_0_15_mb = CAN2_ORed_0_15_MB_IRQn,
        .irq_n_ored_16_31_mb = CAN2_ORed_16_31_MB_IRQn,
        .irq_n_ored_32_47_mb = CAN2_ORed_32_47_MB_IRQn,
        .irq_n_ored_48_63_mb = CAN2_ORed_48_63_MB_IRQn,
    },
#endif

#ifdef HAS_CAN3
    {
        .num = 3,
        .valid = true,
        .CANx = CAN3,

        .irq_n_error = CAN3_Error_IRQn,
        .irq_n_wake_up = CAN3_Wake_Up_IRQn,
        .irq_n_ored = CAN3_ORed_IRQn,
        .irq_n_ored_0_15_mb = CAN3_ORed_0_15_MB_IRQn,
        .irq_n_ored_16_31_mb = CAN3_ORed_16_31_MB_IRQn,
        .irq_n_ored_32_47_mb = NotAvail_IRQn,
        .irq_n_ored_48_63_mb = NotAvail_IRQn,
    },
#endif

#ifdef HAS_CAN4
    {
        .num = 4,
        .valid = true,
        .CANx = CAN4,

        .irq_n_error = CAN4_Error_IRQn,
        .irq_n_wake_up = CAN4_Wake_Up_IRQn,
        .irq_n_ored = CAN4_ORed_IRQn,
        .irq_n_ored_0_15_mb = CAN4_ORed_0_15_MB_IRQn,
        .irq_n_ored_16_31_mb = CAN4_ORed_16_31_MB_IRQn,
        .irq_n_ored_32_47_mb = NotAvail_IRQn,
        .irq_n_ored_48_63_mb = NotAvail_IRQn,
    },
#endif

#ifdef HAS_CAN5
    {
        .num = 5,
        .valid = true,
        .CANx = CAN5,

        .irq_n_error = CAN5_Error_IRQn,
        .irq_n_wake_up = CAN5_Wake_Up_IRQn,
        .irq_n_ored = CAN5_ORed_IRQn,
        .irq_n_ored_0_15_mb = CAN5_ORed_0_15_MB_IRQn,
        .irq_n_ored_16_31_mb = CAN5_ORed_16_31_MB_IRQn,
        .irq_n_ored_32_47_mb = NotAvail_IRQn,
        .irq_n_ored_48_63_mb = NotAvail_IRQn,
    },
#endif
};

COMPONENT_GET_INFO(Can)

static bool can_fd_baudrate_set_ll(CanHandle_t* const Node, uint32_t bit_rate) {
    bool res = false;
    if(Node) {
        if(bit_rate) {
            flexcan_time_segment_t TimeSeg = {0};
            /* Get the PE clock frequency */
            uint32_t clk_freq = 0;
            status_t ret;
            (void)ret;
            ret = CLOCK_SYS_GetFreq(FEATURE_CAN_PE_OSC_CLK_NAME, &clk_freq);
            uint32_t bit_rate_real = FLEXCAN_BitrateToTimeSeg(bit_rate, clk_freq, &TimeSeg);
            (void)bit_rate_real;
            FLEXCAN_DRV_SetBitrateCbt(Node->num, &TimeSeg);
            res = true;
        }
    }
    return res;
}



static bool can_api_baudrate_set_ll(CanHandle_t* const Node, uint32_t bit_rate) {
    bool res = false;
    if(Node) {
        if(bit_rate) {
            flexcan_time_segment_t TimeSeg = {0};
            /* Get the PE clock frequency */
            uint32_t clk_freq = 0;
            status_t ret;
            (void)ret;
            ret = CLOCK_SYS_GetFreq(FEATURE_CAN_PE_OSC_CLK_NAME, &clk_freq);
            uint32_t bit_rate_real = FLEXCAN_BitrateToTimeSeg(bit_rate, clk_freq, &TimeSeg);
            (void)bit_rate_real;
            FLEXCAN_DRV_SetBitrate(Node->num, &TimeSeg);
            res = true;
        }
    }
    return res;
}

static flexcan_fd_payload_size_t CanPayloadSizeToPayload(uint8_t payload_size) {
    /* The payload size of the mailboxes specified in bytes. */
    flexcan_fd_payload_size_t fd_payload_size = FLEXCAN_PAYLOAD_SIZE_8;
    switch(payload_size) {
    case 8:
        fd_payload_size = FLEXCAN_PAYLOAD_SIZE_8;
        break;
    case 16:
        fd_payload_size = FLEXCAN_PAYLOAD_SIZE_16;
        break;
    case 32:
        fd_payload_size = FLEXCAN_PAYLOAD_SIZE_32;
        break;
    case 64:
        fd_payload_size = FLEXCAN_PAYLOAD_SIZE_64;
        break;
    default:
        fd_payload_size = FLEXCAN_PAYLOAD_SIZE_8;
        break;
    }
    return fd_payload_size;
}



static flexcan_rxfifo_transfer_type_t CanMoveModeToTransferType(MoveMode_t move_mode) {
    /* Specifies if the Rx FIFO uses interrupts or DMA. */
    flexcan_rxfifo_transfer_type_t transfer_type = FLEXCAN_RXFIFO_USING_INTERRUPTS;
    switch(move_mode) {
#if FEATURE_CAN_HAS_DMA_ENABLE
    case MOVE_MODE_DMA:
        transfer_type = FLEXCAN_RXFIFO_USING_DMA;
        break;
#endif
    case MOVE_MODE_INTERRUPT:
        transfer_type = FLEXCAN_RXFIFO_USING_INTERRUPTS;
        break;
    default:
        transfer_type = FLEXCAN_DISABLE_MODE;
        break;
    }
    return transfer_type;
}

static bool CanBitRateToBitRate(clock_names_t clockName, uint32_t bit_rate, flexcan_time_segment_t* const TimeSeg) {
    bool res = false;

    uint32_t clk_freq_hz = 0;
    status_t ret = CLOCK_SYS_GetFreq(clockName, &clk_freq_hz);
    if(STATUS_SUCCESS == ret) {
        if(0 < clk_freq_hz) {
            uint32_t prescaler = calc_prescaler(clk_freq_hz, bit_rate);
            uint32_t bit_rate_real = FLEXCAN_BitrateToTimeSeg(bit_rate, clk_freq_hz, TimeSeg);
            double sample_time_s = 1.0 / ((double)bit_rate);
            LOG_INFO(CAN, "BaseClock:%7u Hz,RateSet:%7u bit/s,SampleTime:%ss,PSC:%u,TiSeg:%s,RateReal:%u bit/s",
                     clk_freq_hz, bit_rate, BigVal2Str(sample_time_s), prescaler, FlaxCanBitRateStr(TimeSeg),
                     bit_rate_real);
            res = true;
        }
    }
    return res;
}

static bool CanConfigToFlexConfig(const CanConfig_t* const Config, flexcan_user_config_t* const FlexConfig) {
    bool res = false;
    if(Config) {
        if(FlexConfig) {
            uint32_t bitrate;
            bitrate = FLEXCAN_DRV_GetDefaultConfig(FlexConfig);
            LOG_INFO(CAN, "CAN%u,DefBitRate:%u", Config->num, bitrate);

            /* The clock source of the CAN Protocol Engine (PE). */
            // FlexConfig->pe_clock = FLEXCAN_CLK_SOURCE_OSC;

            /* The CAN engine clock source is the oscillator clock. */
            FlexConfig->pe_clock = FLEXCAN_CLK_SOURCE_PERIPH;

            /* The bitrate used for the data phase of FD frames. */
            res = CanBitRateToBitRate(FAST_BUS_CLK, Config->bit_rate, &FlexConfig->bitrate);
            res = CanBitRateToBitRate(FAST_BUS_CLK, Config->bit_rate_fd, &FlexConfig->bitrate_cbt);

            /* The maximum number of Message Buffers */
            FlexConfig->max_num_mb = 6; // 13 HardFault
            FlexConfig->is_rx_fifo_needed = false;
            FlexConfig->payload = CanPayloadSizeToPayload(Config->payload_size);
            FlexConfig->transfer_type = CanMoveModeToTransferType(Config->move_mode);
            FlexConfig->flexcanMode = CanModeToFlexCanMode(Config->mode);
            /* Enable/Disable the Flexible Data Rate feature. */
            FlexConfig->fd_enable = Config->fd_enable;
#if 0
            /* The number of enhance rx fifo filters needed */
         //   FlexConfig->num_enhance_rx_fifo_filters = 0;

            /* The number of enhance rx fifo filters needed for extended id */
            FlexConfig->num_enhance_rx_fifo_extid_filters = 0;

            FlexConfig->num_enhance_rx_fifo_min_messages = 0;

            /* 1 if needed; 0 if not. This controls whether the use
             *   legecy Rx FIFO or enhance Rx FIFO. */
            FlexConfig->is_enhance_rx_fifo_needed = 0;

            FlexConfig->rxFifoDMALastWord = 0;

            /* Specifies the DMA channel number to be used for DMA transfers. */
            FlexConfig->rxFifoDMAChannel = Config->dma_channel_rx;

            /* 1 if needed; 0 if not. This controls whether the Rx FIFO
             * feature is enabled or not.                                                                      */
            FlexConfig->is_rx_fifo_needed = Config->rx_fifo_on_off;


            /* The number of RX FIFO ID filters needed                                                                      */
            FlexConfig->num_id_filters = FLEXCAN_RX_FIFO_ID_FILTERS_8;
#endif
            res = true;
        }
    }
    return res;
}

bool can_fd_baudrate_set(uint8_t num, uint32_t bit_rate) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        res = can_fd_baudrate_set_ll(Node, bit_rate);
    }
    return res;
}

bool can_api_baudrate_set(uint8_t num, uint32_t bit_rate) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        res = can_api_baudrate_set_ll(Node, bit_rate);
    }
    return res;
}

bool can_check(void) { return false; }

uint32_t can_wakeup_message_buffer_id_get(uint8_t num, uint32_t mb_idx) {
    uint32_t rx_id = 0;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        uint32_t* RxIdPtr = (uint32_t*)(((uint32_t)Node->CANx) + 0xB44 + (mb_idx * 16));
        rx_id = *RxIdPtr;
    }
    return rx_id;
}

bool can_tec_get(uint8_t num, uint32_t* const tec) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        if(tec) {
            CanRegECR_t Reg = {0};
            Reg.qword = Node->CANx->ECR;
            *tec = Reg.TXERRCNT;
            res = true;
        }
    }
    return res;
}

bool can_rec_get(uint8_t num, uint32_t* const rec) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        if(rec) {
            CanRegECR_t Reg = {0};
            Reg.qword = Node->CANx->ECR;
            *rec = Reg.RXERRCNT;
            res = true;
        }
    }
    return res;
}

bool can_fd_tec_get(uint8_t num, uint32_t* const tec) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        if(tec) {
            CanRegECR_t Reg = {0};
            Reg.qword = Node->CANx->ECR;
            *tec = Reg.TXERRCNT_FAST;
            res = true;
        }
    }
    return res;
}

bool can_fd_rec_get(uint8_t num, uint32_t* const rec) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        if(rec) {
            CanRegECR_t Reg = {0};
            Reg.qword = Node->CANx->ECR;
            *rec = Reg.RXERRCNT_FAST;
            res = true;
        }
    }
    return res;
}

bool can_api_transmit_data(uint8_t num, const CanMessage_t* const Message) {
    bool res = false;
    LOG_DEBUG(CAN, "CAN%u:Tx:%s", num, CanMessageToStr(Message));
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        if(Node->CANx) {
            res = can_is_message_valid(Message);
            if(res) {
                res = false;
            } else {
                LOG_ERROR(CAN, "InvalidMessage");
            }
        } else {
            LOG_ERROR(CAN, "CanErr");
        }
    } else {
        LOG_DEBUG(CAN, "CAN%u NodeErr", num);
    }
    return res;
}

bool can_fd_send(uint8_t num, const CanMessage_t* const Message) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        LOG_DEBUG(CAN_FD, "CAN%u,Send:%s", num, CanMessageToStr(Message));
        Node->TxMsg.cs = 0U;
        Node->TxMsg.msgId = Message->identifier.standard;
        Node->TxMsg.dataLen = Message->size;
        memcpy(Node->TxMsg.data, Message->data, Message->size);
        status_t ret = STATUS_ERROR;
        ret = FLEXCAN_DRV_GetTransferStatus(num, TX_MAILBOX);
        if(STATUS_BUSY == ret) {
            res = false;
            LOG_DEBUG(CAN_FD, "CAN%u,TxBusy", num);
        } else {
            ret = FLEXCAN_DRV_Send(num, TX_MAILBOX, &Node->txMbStdInfo, Node->TxMsg.msgId, Node->TxMsg.data);
            if(STATUS_SUCCESS == ret) {
                LOG_NOTICE(CAN_FD, "CAN%u,Send,%s,Ok", num, FlexCanMessageToStr(&Node->TxMsg));
            } else {
                LOG_ERROR(CAN_FD, "CAN%u,SendErr,%s", num, RetToStr(ret));
            }
        }
        res = Fc7300xSdkStatusToRes(ret);
    }
    return res;
}

static uint32_t CanTimeSegToBitRate(uint32_t clk_freq, flexcan_time_segment_t* TimeSeg) {
    uint32_t one_bit_quants = 0;
    one_bit_quants += TimeSeg->phaseSeg1;
    one_bit_quants += TimeSeg->phaseSeg2;
    one_bit_quants += TimeSeg->rJumpwidth;
    one_bit_quants += TimeSeg->propSeg + 1;

    double quant_freq = ((double)clk_freq) / ((double)(TimeSeg->preDivider + 1));

    double quant_peroid_s = ((double)one_bit_quants) * (1.0 / quant_freq);
    double bit_rate_hz = 1.0 / quant_peroid_s;
    return (uint32_t)bit_rate_hz;
}

bool can_api_baudrate_get(uint8_t num, uint32_t* const bit_rate) {
    bool res = false;
    if(bit_rate) {
        status_t ret;
        (void)ret;
        *bit_rate = 0;
        flexcan_time_segment_t TimeSeg = {0};
        FLEXCAN_DRV_GetBitrate(num, &TimeSeg);
        uint32_t mac_freq_hz = 0;
        ret = CLOCK_SYS_GetFreq(FAST_BUS_CLK, &mac_freq_hz);
        *bit_rate = CanTimeSegToBitRate(mac_freq_hz, &TimeSeg);
        res = true;
    }
    return res;
}

bool can_fd_baudrate_get(uint8_t num, uint32_t* const bit_rate) {
    bool res = false;
    if(bit_rate) {
        status_t ret;
        (void)ret;
        *bit_rate = 0;
        flexcan_time_segment_t TimeSeg = {0};
        FLEXCAN_DRV_GetBitrateFD(num, &TimeSeg);
        uint32_t mac_freq_hz = 0;
        ret = CLOCK_SYS_GetFreq(FAST_BUS_CLK, &mac_freq_hz);
        *bit_rate = CanTimeSegToBitRate(mac_freq_hz, &TimeSeg);
        res = true;
    }
    return res;
}

static bool can_deinit_interrupt_ll(CanInfo_t* Info) {
    bool res = false;
    if(Info) {
        NVIC_DisableIRQ(Info->irq_n_error);
        NVIC_DisableIRQ(Info->irq_n_wake_up);
        NVIC_DisableIRQ(Info->irq_n_ored);
        NVIC_DisableIRQ(Info->irq_n_ored_0_15_mb);
        NVIC_DisableIRQ(Info->irq_n_ored_16_31_mb);
        NVIC_DisableIRQ(Info->irq_n_ored_32_47_mb);
        NVIC_DisableIRQ(Info->irq_n_ored_48_63_mb);
        res = true;
    }
    return res;
}

static bool can_init_interrupt_ll(CanInfo_t* Info) {
    bool res = false;
    if(Info) {
        NVIC_EnableIRQ(Info->irq_n_error);
        NVIC_EnableIRQ(Info->irq_n_wake_up);
        NVIC_EnableIRQ(Info->irq_n_ored);
        NVIC_EnableIRQ(Info->irq_n_ored_0_15_mb);
        NVIC_EnableIRQ(Info->irq_n_ored_16_31_mb);
        NVIC_EnableIRQ(Info->irq_n_ored_32_47_mb);
        NVIC_EnableIRQ(Info->irq_n_ored_48_63_mb);
        res = true;
    }
    return res;
}

static bool can_init_mail_box_ll(CanHandle_t* const Node) {
    bool res = false;
    if(Node) {
        status_t ret = STATUS_ERROR;
        res = true;

        Node->txMbStdInfo.msg_id_type = CanIdentifierToMesgIdType(Node->identifier);
        Node->txMbStdInfo.data_length = 64;
        Node->txMbStdInfo.fd_enable = Node->fd_enable;
        Node->txMbStdInfo.fd_padding = 0x55;
        Node->txMbStdInfo.enable_brs = true;
        Node->txMbStdInfo.is_remote = false;
        /* Configure TX buffer with index TX_MAILBOX*/
        ret = FLEXCAN_DRV_ConfigTxMb(Node->num, TX_MAILBOX, &Node->txMbStdInfo, Node->tx_id);
        res = log_fc73_ret(CAN, ret, "ConfigTxMb") && res;

        Node->rxMbStdInfo.msg_id_type = CanIdentifierToMesgIdType(Node->identifier);
        Node->rxMbStdInfo.data_length = 64;
        Node->rxMbStdInfo.fd_enable = Node->fd_enable;
        Node->rxMbStdInfo.fd_padding = 0x55;
        Node->rxMbStdInfo.enable_brs = true;
        Node->rxMbStdInfo.is_remote = false;
        /* Configure RX buffer with index RX_MAILBOX */
        ret = FLEXCAN_DRV_ConfigRxMb(Node->num, RX_MAILBOX, &Node->rxMbStdInfo, Node->rx_id);
        res = log_fc73_ret(CAN, ret, "ConfigRxMb") && res;
    }
    return res;
}

/*

  false - The corresponding buffer has no occurrence of successfully completed transmission or
          reception.

  true The corresponding buffer has successfully completed transmission or reception.

 */
bool can_move_info_get(uint8_t num, uint8_t message_buffer_num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        uint32_t mask = 0;
        uint32_t imask_val = 0;
        if(0 <= message_buffer_num) {
            if(message_buffer_num <= 31) {
                SET_BIT_NUM(mask, message_buffer_num);
                imask_val = Node->CANx->IFLAG1;
            }
        }
        if(32 <= message_buffer_num) {
            if(message_buffer_num <= 63) {
                SET_BIT_NUM(mask, message_buffer_num - 32);
                imask_val = Node->CANx->IFLAG2;
            }
        }

        if(mask & imask_val) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

bool can_message_buffer_interrupt_get(uint8_t num, uint8_t message_buffer_num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        uint32_t mask = 0;
        uint32_t imask_val = 0;
        if(0 <= message_buffer_num) {
            if(message_buffer_num <= 31) {
                SET_BIT_NUM(mask, message_buffer_num);
                imask_val = Node->CANx->IMASK1;
            }
        }
        if(32 <= message_buffer_num) {
            if(message_buffer_num <= 63) {
                SET_BIT_NUM(mask, message_buffer_num - 32);
                imask_val = Node->CANx->IMASK2;
            }
        }

        if(mask & imask_val) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}


bool can_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(CAN, "CAN%u,Proc", num);
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        status_t ret = STATUS_ERROR;
        ret = FLEXCAN_DRV_GetTransferStatus(num, RX_MAILBOX);
        if(STATUS_BUSY == ret) {
            LOG_DEBUG(CAN, "RxBysy,Err");
        } else {
            res = true;
        }

        if(Node->RxMsg.dataLen) {
#if 0
            flexcan_msgbuff_code_status_t cs;
			cs=(flexcan_msgbuff_code_status_t) Node->RxMsg.cs;
			Node->RxMessage.id_type=CanFc73MsgIdTypeToIdType(cd.msgIdType);
#endif

            led_rgb_blink(1, 200, COLOR_BLUE);
            LOG_INFO(CAN, "CAN%u,Rx:%s", num, FlexCanMessageToStr(&Node->RxMsg));
            Node->RxMessage.identifier.standard = Node->RxMsg.msgId;
            Node->RxMessage.size = Node->RxMsg.dataLen;
            memcpy(Node->RxMessage.data, Node->RxMsg.data, Node->RxMessage.size);

            Node->RxMsg.dataLen = 0;
            ret = FLEXCAN_DRV_Receive(num, RX_MAILBOX, &Node->RxMsg);
        }

        if(STATUS_SUCCESS == ret) {
            Node->unproc_rx_message = false;
        }
        if(res) {
        }
        res = true;
#if 0
            if(Node->rx_id == Node->RxMessage.identifier.standard) {
                /*Is allowed RX*/
#ifdef HAS_ISO_TP
                static IsoTpFrame_t RxFrame = {0};
                memcpy(RxFrame.data, Node->RxMessage.data, 8);
                res = iso_tp_proc_rx(num, Node->RxMessage.identifier.standard, &RxFrame);
#endif
            } else {
                LOG_DEBUG(CAN, "AlienCanID 0x%x,MyCanID:0x%x", Node->RxMessage.identifier.standard, Node->rx_id);
            }
#endif
    }
    return res;
}

static bool can_wait_busy(uint8_t num, uint32_t time_out_ms) {
    bool res = false;
    bool loop = true;
    uint32_t start_ms = time_get_ms32();
    while(loop) {
        status_t ret = FLEXCAN_DRV_GetTransferStatus(num, RX_MAILBOX);
        if(STATUS_BUSY == ret) {
            loop = true;
        } else {
            loop = false;
            res = true;
        }

        uint32_t cur_ms = time_get_ms32();
        uint32_t dutation_ms = cur_ms - start_ms;
        if(time_out_ms < dutation_ms) {
            loop = false;
            res = false;
        }
    }

    return res;
}

bool can_health_monitor_proc_one(uint8_t num){
    bool res = true;
    LOG_PARN(CAN, "CAN%u,Proc", num);
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {

        uint32_t tec=0;
        res = can_tec_get(   num, &tec);
        if(tec) {
            LOG_ERROR(CAN, "CAN%u,TEC:%u", num, tec);
        }

        uint32_t rec=0;
        res = can_rec_get(   num, &rec);
        if(rec) {
            LOG_ERROR(CAN, "CAN%u,REC:%u", num, rec);
        }


        res = can_fd_tec_get(   num, &tec);
        if(tec) {
            LOG_ERROR(CAN, "CAN_FD%u,TEC:%u", num, tec);
        }


        res = can_fd_rec_get(   num, &rec);
        if(rec) {
            LOG_ERROR(CAN, "CAN_FD%u,REC:%u", num, rec);
        }


        /*
          Note: To minimize errors when processing FD frames, use the same value
          for FPRESDIV and PRESDIV (in CAN_CBT or CAN_CTRL1). For more details,
          see ”CAN FD Frames”
        */
        CanRegFDCBT_t FDCBT;
        FDCBT.qword = Node->CANx->FDCBT;

        CanRegCBT_t CBT;
        CBT.qword = Node->CANx->CBT;
        if(FDCBT.FPRESDIV != CBT.EPRESDIV) {
            LOG_DEBUG(CAN, "CAN%u,PrescalerErr:%u,%u", num, FDCBT.FPRESDIV, CBT.EPRESDIV);
            res = false;
        }
    }
    return res;
}

bool can_init_one(uint8_t num) {
    bool res = false;
    const CanConfig_t* Config = CanGetConfig(num);
    if(Config) {
        LOG_WARNING(CAN, "SpotCfg:%s", CanConfigTo2Str(Config));
        res = CanIsValidConfig(Config);
        if(res) {
            CanHandle_t* Node = CanGetNode(num);
            if(Node) {
                LOG_WARNING(CAN, "CAN%u,Init..", num);
                res = can_init_common_one(Config, Node);
                CanInfo_t* Info = CanGetInfo(num);
                if(Info) {
                    Node->CANx = Info->CANx;
                    Node->heart_beat_sn = num;
                    res = can_deinit_interrupt_ll(Info);
                    flexcan_user_config_t FlexConfig = {0};
                    res = CanConfigToFlexConfig(Config, &FlexConfig);
                    if(res) {
                        status_t ret = STATUS_ERROR;
                        ret = FLEXCAN_DRV_Init(num, &Node->handle, &FlexConfig);
                        res = log_fc73_ret(CAN, ret, "FlexCanInit");
                        if(res) {
                            res = can_init_mail_box_ll(Node);
                            log_res(CAN, res, "InitMailBox");

                            res = can_wait_busy(num, 3000);
                            log_res(CAN, res, "Wait");
                            if(res) {
                                /* Start receiving data in RX_MAILBOX. */
                                ret = FLEXCAN_DRV_Receive(num, RX_MAILBOX, &Node->RxMsg);
                                res = log_fc73_ret(CAN, ret, "FlexCanRx");
                            }
                        }
                        log_res(CAN, res, "Init");
                        res = can_init_interrupt_ll(Info);
                    }
                } else {
                    res = false;
                    LOG_ERROR(CAN, "CAN%u,InfoErr", num);
                }
                log_level_get_set(CAN, LOG_LEVEL_INFO);
            } else {
                res = false;
                LOG_ERROR(CAN, "NodeErr");
            }
        }
    } else {
        LOG_DEBUG(CAN, "CAN%u NoConfig", num);
    }
    return res;
}
