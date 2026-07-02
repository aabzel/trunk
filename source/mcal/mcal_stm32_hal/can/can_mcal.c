#include "can_mcal.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "can_core.h"
#include "can_custom.h"
#include "can_mailbox_config.h"
#include "can_misc.h"
#include "clock_mcal.h"
#include "code_generator.h"
#include "common_diag.h"
#include "connectivity.h"
#include "data_utils.h"
#include "float_diag.h"
#include "gpio_mcal.h"
#include "hal_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "std_includes.h"
#include "time_mcal.h"

#ifdef HAS_LED_MONO
#include "led_mono_drv.h"
#endif

#ifdef HAS_CAN_DIFF
#include "can_diff_mcal.h"
#endif

#ifdef HAS_STORE_FS
#include "store_fs.h"
#endif

#ifdef HAS_CAN_RX_HIST
#include "can_rx_hist_mcal.h"
#endif

#ifdef HAS_ISO_TP
#include "iso_tp_mcal.h"
#endif

#ifdef HAS_TBFP
#include "tbfp.h"
#endif

#ifdef HAS_CAN_PROC
static bool can_proc_error_status_ll(CanHandle_t* const Node) {
    bool res = false;
    CanReg_ESR_t CAN_ESR;
    CAN_ESR.dword = Node->CANx->ESR;
    if(CAN_ESR.LEC) {
        LOG_DEBUG(CAN, "CAN%u,LastErrorCode:%u=%s", Node->num, CAN_ESR.LEC, CanLastErrorCodeToStr(CAN_ESR.LEC));
        Node->error_cnt++;
    }

    if(CAN_ESR.TEC) {
        LOG_DEBUG(CAN, "CAN%u,TEC:%u", Node->num, CAN_ESR.TEC);
        Node->tec_err_cnt++;
    }

    if(CAN_ESR.REC) {
        LOG_DEBUG(CAN, "CAN%u,REC:%u", Node->num, CAN_ESR.REC);
        Node->rec_err_cnt++;
    }

    if(CAN_ESR.BOFF) {
        /*This bit is set by hardware when it enters the bus-off state.
          The bus-off state is entered on TEC overflow, greater than 255,
          refer to Section 32.7.6.*/
        LOG_DEBUG(CAN, "CAN%u,BusOff", Node->num);
        Node->error_cnt++;
        Node->error = true;
        Node->warning_tx_cnt++;
        Node->warning_tx = true;
        Node->error_bus_off_cnt++;
        Node->error_bus_off = true;
    }

    if(CAN_ESR.EWGF) {
        LOG_DEBUG(CAN, "CAN%u,96<=RECorTEC", Node->num);
        Node->warning_tx_cnt++;
        Node->warning_tx = true;
    }

    if(CAN_ESR.EPVF) {
        /*This bit is set by hardware when the Error Passive limit has been
          reached (Receive Error Counter or Transmit Error Counter>127).*/
        LOG_DEBUG(CAN, "CAN%u,ErroPassive,127<RECorTEC", Node->num);
        Node->error_cnt++;
        Node->error = true;
    }

    return res;
}

static bool can_proc_status_tx_mail_box0_ll(CanHandle_t* const Node, CanReg_TSR_t TSR, uint8_t mb_num) {
    bool res = false;

    if(TSR.LOW0) {
        LOG_DEBUG(CAN, "CAN%u,LOW%u", Node->num, mb_num);
    }

    if(TSR.TERR0) {
        LOG_PARN(CAN, "CAN%u,Tx,MB%u,Err", Node->num, mb_num);
    }

    if(TSR.ALST0) {
        LOG_DEBUG(CAN, "CAN%u,ArbitrationLost,MB%u,Err", Node->num, mb_num);
        Node->arbitration_lost_cnt++;
    }

    if(TSR.RQCP0) {
        // can_tx_indication(Node);
        TSR.RQCP0 = 1;
        LOG_PARN(CAN, "CAN%u,RequestDone,MB%u", Node->num, mb_num);
    }

    if(TSR.TXOK0) {
        can_tx_indication(Node);
        LOG_PARN(CAN, "CAN%u,TxOk,MB%u", Node->num, mb_num);
    }

    if(TSR.TME0) {
        LOG_PARN(CAN, "CAN%u,Tx,MB%u,Empty", Node->num, mb_num);
    }
    Node->CANx->TSR = TSR.dword;
    return res;
}

static bool can_proc_status_tx_mail_box1_ll(CanHandle_t* const Node, CanReg_TSR_t TSR, uint8_t mb_num) {
    bool res = false;

    if(TSR.TERR1) {
        LOG_DEBUG(CAN, "CAN%u,Tx,MB%u,Err", Node->num, mb_num);
        Node->tx_error_cnt++;
    }

    if(TSR.ALST1) {
        LOG_DEBUG(CAN, "CAN%u,ArbitrationLost,MB%u,Err", Node->num, mb_num);
        Node->arbitration_lost_cnt++;
    }

    if(TSR.LOW1) {
        LOG_DEBUG(CAN, "CAN%u,LOW1,MB%u", Node->num, mb_num);
    }

    if(TSR.RQCP1) {
        TSR.RQCP1 = 1;
        // can_tx_indication(Node);
        LOG_PARN(CAN, "CAN%u,RequestDone,MB%u", Node->num, mb_num);
    }

    if(TSR.TXOK1) {
        can_tx_indication(Node);
        LOG_PARN(CAN, "CAN%u,TxOk,MB%u", Node->num, mb_num);
    }
    if(TSR.TME1) {
        LOG_PARN(CAN, "CAN%u,Tx,MB%u,empty", Node->num, mb_num);
    }
    Node->CANx->TSR = TSR.dword;
    return res;
}

static bool can_proc_status_tx_mail_box2_ll(CanHandle_t* const Node, CanReg_TSR_t TSR, uint8_t mb_num) {
    bool res = false;

    if(TSR.ALST2) {
        LOG_DEBUG(CAN, "CAN%u,ArbitrationLost,MB%u,Err", Node->num, mb_num);
        Node->arbitration_lost_cnt++;
    }

    if(TSR.LOW2) {
        LOG_DEBUG(CAN, "CAN%u,LowestPriority,MB%u", Node->num, mb_num);
    }

    if(TSR.TERR2) {
        LOG_ERROR(CAN, "CAN%u,TxMailBox,MB%u,Err", Node->num, mb_num);
    }

    if(TSR.RQCP2) {
        TSR.RQCP2 = 1;
        // can_tx_indication(Node);
        LOG_PARN(CAN, "CAN%u,RequestDone,MB%u", Node->num, mb_num);
    }

    if(TSR.TXOK2) {
        can_tx_indication(Node);
        LOG_PARN(CAN, "CAN%u,TxOk,MB%u", Node->num, mb_num);
    }

    if(TSR.TME2) {
        LOG_PARN(CAN, "CAN%u,Tx,empty,MB%u", Node->num, mb_num);
    }
    Node->CANx->TSR = TSR.dword;
    return res;
}

static bool can_proc_status_rx_fifo_one_ll(CanHandle_t* const Node, uint8_t fifo_num) {
    bool res = false;
    CanReg_RFxR_t RFxR;
    RFxR.dword = 0;

    switch(fifo_num) {
    case 0: {
        RFxR.dword = Node->CANx->RF0R;
    } break;
    case 1: {
        RFxR.dword = Node->CANx->RF1R;
    } break;
    default: {

    } break;
    }

    if(RFxR.FMP) {
        LOG_DEBUG(CAN, "CAN%u,FIFO%u,Messages:%u", Node->num, RFxR.FMP, fifo_num);
    }

    if(RFxR.FULL) {
        LOG_DEBUG(CAN, "CAN%u,FIFO%u,Full", Node->num, fifo_num);
    }

    if(RFxR.FOVR) {
        LOG_DEBUG(CAN, "CAN%u,FIFO%u,OverRun", Node->num, fifo_num);
    }

    return res;
}
#endif

#ifdef HAS_CAN_PROC
static bool can_proc_status_rx_fifo_ll(CanHandle_t* const Node) {
    bool res = false;
    res = can_proc_status_rx_fifo_one_ll(Node, 0);
    res = can_proc_status_rx_fifo_one_ll(Node, 1);
    return res;
}
#endif

#ifdef HAS_CAN_PROC
static bool can_proc_status_tx_ll(CanHandle_t* const Node) {
    bool res = false;
    CanReg_TSR_t TSR;
    TSR.dword = Node->CANx->TSR;
    res = can_proc_status_tx_mail_box0_ll(Node, TSR, 0);
    res = can_proc_status_tx_mail_box1_ll(Node, TSR, 1);
    res = can_proc_status_tx_mail_box2_ll(Node, TSR, 2);
    LOG_PARN(CAN, "CAN%u,Code:%u", Node->num, TSR.CODE);
    return res;
}
#endif

#ifdef HAS_CAN_PROC
static bool can_proc_status_ll(CanHandle_t* const Node) {
    bool res = false;
    CanReg_MSR_t CAN_MSR; // CAN master status register (CAN_MSR)
    CAN_MSR.dword = Node->CANx->MSR;
    if(CAN_MSR.ERRI) {
        LOG_ERROR(CAN, "CAN%u,Error", Node->num);
        Node->error = true;
        Node->error_cnt++;
    }

    if(CAN_MSR.TXM) {
        can_tx_indication(Node);
        LOG_PARN(CAN, "CAN%u,Tx", Node->num);
    }

    if(CAN_MSR.SLAK) {
        LOG_DEBUG(CAN, "CAN%u,SleepAck", Node->num);
    }

    if(CAN_MSR.INAK) {
        LOG_DEBUG(CAN, "CAN%u,Initialization,ack", Node->num);
    }

    if(CAN_MSR.WKUI) {
        /* Bit 3 WKUI: Wake-up interrupt
        This bit is set by hardware to signal that a SOF bit has been detected while the CAN
        hardware was in Sleep mode. Setting this bit generates a status change interrupt if the
        WKUIE bit in the CAN_IER register is set.
        This bit is cleared by software.*/
        CAN_MSR.WKUI = 0;
        LOG_DEBUG(CAN, "CAN%u,Wake-up,Int", Node->num);
    }

    if(CAN_MSR.SLAKI) {
        LOG_WARNING(CAN, "CAN%u,SleepAck,Int", Node->num);
    }

    if(CAN_MSR.RXM) {
        LOG_PARN(CAN, "CAN%u,RxMode", Node->num);
    }

    LOG_PARN(CAN, "CAN%u,LastSample:%u", Node->num, CAN_MSR.SAMP);
    LOG_PARN(CAN, "CAN%u,RxSignal:%u", Node->num, CAN_MSR.RX);

    if(CAN_MSR.ERRI) {
        Node->CANx->MSR = CAN_MSR.dword;
    }
    return res;
}
#endif

#ifdef HAS_CAN_STM32
uint32_t can_get_spare_mail_box(const uint8_t num) {
    uint32_t busy_cnt = 0;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        uint32_t m = 0;
        for(m = 0; m < 3; m++) {
            uint32_t tx_mailbox_code = CanMailBoxNumToCode(m);
            uint32_t status = HAL_CAN_IsTxMessagePending(&Node->Handle, tx_mailbox_code);
            busy_cnt += status;
        }
    }
    return (3U - busy_cnt);
}
#endif

#ifdef HAS_LED_MONO
static bool can_traffic_indication_ctrl(CanHandle_t* const Node) {
    bool res = false;
    uint32_t up_time_stamp = time_get_ms32();

    uint32_t diff_ms = up_time_stamp - Node->rx_time_stamp;
    if(CAN_LED_MOVE_TIME_OUT_MS < diff_ms) {
        res = led_mono_ctrl(Node->led_num_rx, false);
    }

    diff_ms = up_time_stamp - Node->tx_time_stamp;
    if(CAN_LED_MOVE_TIME_OUT_MS < diff_ms) {
        res = led_mono_ctrl(Node->led_num_tx, false);
    }

    return res;
}
#endif

/* CAN1 & CAN2 filter shared 28 filters, we use 14 for each one
 * can1: 0  1  2  3  4  5  6  7  8  9  10 11 12 13
 * can2: 14 15 16 17 18 19 20 21 22 23 24 25 26 27
 *
 * */
int8_t can_filter_num_calc(const uint8_t can_num, const uint8_t filt_num) {
    int8_t real_filter = -1;
    if(CAN2_FILTER_NUM_FIRST <= filt_num) {
        LOG_ERROR(CAN, "IllegalFilterNum:%d", filt_num);
    } else {
        real_filter = (int8_t)filt_num;
        if(2 == can_num) {
            real_filter = filt_num + CAN2_FILTER_NUM_FIRST;
        }
    }

    LOG_INFO(CAN, "CAN%u,NeedFilter:%u,RealFilter:%d", can_num, filt_num, real_filter);

    return real_filter;
}

#ifdef HAS_CAN_STM32
/*
 * bus [1 2]
 * format [CAN_FRAME_ID_STANDARD CAN_FRAME_ID_EXTENDED]
 * filt_num  [0...13]*/
bool can_mcal_filter_id_mask_set(const uint8_t can_num, const uint8_t filt_num, const CanIdentifier_t format,
                                 const uint32_t filt_id, const uint32_t filt_mask) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(can_num);
    if(Node) {
        CAN_FilterTypeDef FilterExtIdMask = {0};
        FilterExtIdMask.FilterMode = CAN_FILTERMODE_IDMASK;
        FilterExtIdMask.FilterScale = CAN_FILTERSCALE_32BIT;
        FilterExtIdMask.FilterFIFOAssignment = CAN_FILTER_FIFO0;
        FilterExtIdMask.FilterActivation = ENABLE;
        FilterExtIdMask.SlaveStartFilterBank = CAN2_FILTER_NUM_FIRST;

        CanRegFilter32Bit_t FilterID;
        CanRegFilter32Bit_t FilterMask;

        FilterID.ZERO = 0;
        FilterID.RTR = 0;
        FilterID.IDE = CanIdTypeToFiltIDE(format);

        FilterMask.ZERO = 0;
        FilterMask.RTR = 0;
        FilterMask.IDE = CanIdTypeToFiltIDE(format);

        switch(format) {
        case CAN_FRAME_ID_STANDARD: {
            FilterID.STD_ID = CAN_STD_ID_MAX_VAL & filt_id;
            FilterMask.STD_ID = filt_mask;
        } break;
        case CAN_FRAME_ID_EXTENDED: {
            FilterID.EXT_ID = CAN_EXT_ID_MAX_VAL & filt_id;
            FilterMask.EXT_ID = filt_mask;
        } break;
        default:
            res = false;
            break;
        }

        Type32Union_t Un32ID;
        Un32ID.u32 = FilterID.dword;
        FilterExtIdMask.FilterIdHigh = (uint16_t)Un32ID.u16[1];
        FilterExtIdMask.FilterIdLow = (uint16_t)Un32ID.u16[0];

        Type32Union_t Un32Mask;
        Un32Mask.u32 = FilterMask.dword;
        FilterExtIdMask.FilterMaskIdHigh = (uint16_t)Un32Mask.u16[1];
        FilterExtIdMask.FilterMaskIdLow = (uint16_t)Un32Mask.u16[0];

        int8_t filter_num = can_filter_num_calc(can_num, filt_num);
        if(0 <= filter_num) {
            HAL_StatusTypeDef ret = HAL_ERROR;
            FilterExtIdMask.FilterBank = (uint32_t)filter_num;
            ret = HAL_CAN_ConfigFilter(&Node->Handle, &FilterExtIdMask);
            res = HAL_retToRes(ret);
        }
    }

    return res;
}
#endif

#ifdef HAS_CAN_PROC
bool can_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(CAN, "CAN%u,Proc", num);
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
#ifdef HAS_CAN_STM32
        if(false == Node->interrupt_on) {
            HAL_CAN_IRQHandler(&Node->Handle);
        }
        uint32_t err = HAL_CAN_GetError(&Node->Handle);
        if(HAL_CAN_ERROR_NONE != err) {
            if(HAL_CAN_ERROR_PARAM != err) {
                LOG_ERROR(CAN, "CAN%u,Err:0x%08X=[%s]", num, err, HalCanErrorToStr(err));
            }
            if(HAL_CAN_ERROR_PARAM == (HAL_CAN_ERROR_PARAM & err)) {
                Node->Handle.ErrorCode &= ~(HAL_CAN_ERROR_PARAM);
            }
        }
#endif
        res = can_proc_status_ll(Node);
        res = can_proc_status_tx_ll(Node);
        res = can_proc_error_status_ll(Node);
        res = can_proc_status_rx_fifo_ll(Node);

        if(Node->unproc_rx_message) {
            Node->rx_time_stamp = time_get_ms32();
#ifdef HAS_LED_MONO
            led_mono_sw_pwm(Node->led_num_rx, 10, 50);
#endif

            LOG_NOTICE(CAN, "CAN%u,Rx:%s", num, CanMessageToStr(&Node->RxMessage));
            Node->unproc_rx_message = false;
#ifdef HAS_CAN_DIFF
            res = can_diff_proc_frame(&Node->RxMessage);
#endif

#ifdef HAS_CAN_RX_HIST
            res = can_rx_hist_add_message(num, &Node->RxMessage);
#endif

            /*Is allowed RX*/
#ifdef HAS_ISO_TP
            // static IsoTpFrame_t RxFrame = {0};
            // memcpy(RxFrame.data, Node->RxMessage.data, 8);
            // res = iso_tp_proc_rx(num, Node->RxMessage.identifier.standard, &RxFrame);
#endif

#ifdef HAS_TBFP
            InterfaceType_t ifCan;
            ifCan.interface_name = INTERFACE_NAME_CAN;
            ifCan.num = num;
            res = tbfp_data_rx(ifCan, Node->RxMessage.data, Node->RxMessage.size);
#endif
        }
#ifdef HAS_LED_MONO
        can_traffic_indication_ctrl(Node);
#endif
        if(Node->error) {
            // res = can_init_one(Node->num);
        }
    }
    return res;
}
#endif

bool can_init_custom(void) {
    bool res = true;
    return res;
}

bool can_health_monitor_proc_one(uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
    }
    return res;
}

/*see Figure 346. Bit timing*/
bool CanSegmentToStmSegment(const CanSegmentInfo_t* const Segment, CAN_InitTypeDef* const Init) {
    bool res = false;
    /* Specifies the length of a time quantum.
     This parameter must be a number between Min_Data = 1 and Max_Data = 1024. */
    Init->Prescaler = Segment->prescaler;

    /* Specifies the maximum number of time quanta the CAN hardware
     is allowed to lengthen or shorten a bit to perform resynchronization.
     This parameter can be a value of @ref CAN_synchronisation_jump_width */
    Init->SyncJumpWidth = CanSynchroToSyncJumpWidth(Segment->synchronization); //- 1);

    /* Specifies the maximum number of time quanta the CAN hardware is allowed to lengthen or shorten a bit to perform
     resynchronization. This parameter can be a value of @ref CAN_synchronisation_jump_width */

    /* Specifies the number of time quanta in Bit Segment 1. This parameter can be a value of @ref
     * CAN_time_quantum_in_bit_segment_1 */
    Init->TimeSeg1 = CanPhase1ToTimeSeg1(Segment->phase_1); //- 1);

    /* Specifies the number of time quanta in Bit Segment 2.
     This parameter can be a value of @ref CAN_time_quantum_in_bit_segment_2 */
    Init->TimeSeg2 = CanPhase2ToTimeSeg2(Segment->phase_2); // - 1);
    return res;
}

uint8_t CanHandleToCanNum(const CAN_HandleTypeDef* const hcan) {
    uint8_t num = 0xff;
    const CanInfo_t* Info = CanXToInfo(hcan->Instance);
    if(Info) {
        num = Info->num;
    }
    return num;
}

CanHandle_t* CanHandleToNode(const CAN_HandleTypeDef* const Handle) {
    CanHandle_t* Node = NULL;
    const CanInfo_t* Info = CanXToInfo(Handle->Instance);
    if(Info) {
        Node = CanGetNode(Info->num);
    }
    return Node;
}

bool can_config_to_init(const CanConfig_t* const Config, CAN_InitTypeDef* const Init) {
    bool res = false;
    if(Config) {
        if(Init) {
            uint32_t bus_freq_hz = 0;
            bus_freq_hz = can_base_clock_get(Config->num);

            CanSegmentInfo_t Segment = {0};
            res = can_stm32_segment_info_calc(bus_freq_hz, Config->bit_rate, &Segment);

            res = CanSegmentToStmSegment(&Segment, Init);

            /* Specifies the CAN operating mode. (  CAN_operating_mode) */
            Init->Mode = CanModeToOperatingMode(Config->mode);
            /* Ctrl time triggered communication mode. ( ENABLE or DISABLE). */
            Init->TimeTriggeredMode = DISABLE;

            /* Ctrl automatic bus-off management. ( ENABLE or DISABLE). */
            Init->AutoBusOff = Config->bus_off_auto_recovery;

            /* Ctrl automatic wake-up mode (ENABLE or DISABLE). */
            Init->AutoWakeUp = ENABLE;

            /* Ctrl non-automatic retransmission mode. ( ENABLE or DISABLE). */
            Init->AutoRetransmission = DISABLE;

            /* Ctrl Receive FIFO Locked mode. ( ENABLE or DISABLE). */
            Init->ReceiveFifoLocked = DISABLE;

            /* Ctrl transmit FIFO priority. ( ENABLE or DISABLE). */
            Init->TransmitFifoPriority = ENABLE;
            res = true;
        }
    }
    return res;
}

#ifdef HAS_CAN_STM32
bool can_loopback_set(const uint8_t num, const bool on_off) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        Node->Handle.Init.Mode = CanLoopBackToOperatingMode(on_off);
        HAL_StatusTypeDef ret = HAL_CAN_Init(&Node->Handle);
        res = HAL_retToRes(ret);
    }
    return res;
}
#endif

bool CanMessageToTxHeader(const CanMessage_t* const Message, CAN_TxHeaderTypeDef* pTxHeader) {
    bool res = false;
    if(Message) {
        if(pTxHeader) {
            pTxHeader->IDE = CanIdTypeToFrameIDE(Message->id_type);
            pTxHeader->DLC = Message->size;
            pTxHeader->ExtId = Message->identifier.extended;
            pTxHeader->StdId = Message->identifier.standard;
            pTxHeader->RTR = CanCanTxFrameToRtr(Message->frame_type);
            pTxHeader->TransmitGlobalTime = DISABLE;
            res = true;
        }
    }
    return res;
}

#ifdef HAS_CAN_STM32
bool can_mcal_transmit_message(uint8_t num, const CanMessage_t* const Message) {
    bool res = false;
    LOG_DEBUG(CAN, "TrySendFrame:%s", CanMessageToStr(Message));
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        uint32_t spare_mail_box = 0;
        spare_mail_box = can_get_spare_mail_box(num);
        if(spare_mail_box) {
            res = CanMessageToTxHeader(Message, &Node->TxHeader);
            if(res) {
                uint32_t tx_mail_box = CAN_TX_MAILBOX0;
                HAL_StatusTypeDef ret = HAL_ERROR;
                ret = HAL_CAN_AddTxMessage(&Node->Handle, &Node->TxHeader, Message->data, &tx_mail_box);
                res = HAL_retToRes(ret);
                if(res) {
                    // Message->time_stamp = time_get_ms32();
#ifdef HAS_CAN_DIAG
                    LOG_DEBUG(CAN, "AddToTx:%s,Ok,Mb:%u", CanMessageToStr(Message), spare_mail_box);
#endif
                }
            }
        }
    }
    return res;
}
#endif

/*see Figure 346. Bit timing*/
bool can_mcal_baudrate_get(uint8_t num, uint32_t* const bit_rate) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanReg_BTR_t CAN_BTR;
        CAN_BTR.dword = Info->CANx->BTR;
        uint32_t base_clock_hz = can_base_clock_get(num);

        res = can_mcal_baudrate_calc(base_clock_hz, CAN_BTR, bit_rate);
        return res;
    }
    return res;
}
#ifdef HAS_CAN_STM32
bool can_init_filters(const CanConfig_t* const Config, CanHandle_t* const Node) {
    bool res = true;

    uint32_t i = 0;
    LOG_INFO(CAN, "FilterAllowRx,Cnt:%u,IDs", Config->rx_id_cnt);
    if(Config->rx_id_cnt < 27) {
        for(i = 0; i < Config->rx_id_cnt; i++) {
            LOG_INFO(CAN, "FilterAllowRx,ID:0x%x", Config->rx_id[i]);
            CanRegFilter32Bit_t Filt2ExtId1;
            Filt2ExtId1.IDE = CanIdTypeToFiltIDE(CAN_FRAME_ID_EXTENDED);
            Filt2ExtId1.EXT_ID = Config->rx_id[i];
            Filt2ExtId1.ZERO = 0;
            Filt2ExtId1.RTR = 0;

            CanRegFilter32Bit_t Filt2ExtId2;
            Filt2ExtId2.IDE = CanIdTypeToFiltIDE(CAN_FRAME_ID_EXTENDED);
            Filt2ExtId2.EXT_ID = Config->rx_id[i];
            Filt2ExtId2.ZERO = 0;
            Filt2ExtId2.RTR = 0;

            CAN_FilterTypeDef canFilterConfig;

            Type32Union_t Un32;
            Un32.u32 = Filt2ExtId1.dword;
            canFilterConfig.FilterIdHigh = (uint16_t)Un32.u16[1];
            canFilterConfig.FilterIdLow = (uint16_t)Un32.u16[0];

            Un32.u32 = Filt2ExtId2.dword;
            canFilterConfig.FilterMaskIdHigh = (uint16_t)Un32.u16[1];
            canFilterConfig.FilterMaskIdLow = (uint16_t)Un32.u16[0];

            int8_t filter_num = can_filter_num_calc(Config->num, i);
            if(0 < filter_num) {
                HAL_StatusTypeDef ret;
                canFilterConfig.FilterActivation = ENABLE;
                canFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
                canFilterConfig.FilterBank = (uint32_t)filter_num;
                canFilterConfig.SlaveStartFilterBank = CAN2_FILTER_NUM_FIRST;
                canFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
                canFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;
                ret = HAL_CAN_ConfigFilter(&Node->Handle, &canFilterConfig);
                res = HAL_retToRes(ret);
            }
        }
    }

#if 0
    canFilterConfig.FilterBank = 0;
    canFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    canFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    canFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    canFilterConfig.FilterActivation = ENABLE;

    canFilterConfig.FilterIdHigh = (uint16_t)(0x000006D9 >> 13);
    canFilterConfig.FilterIdLow =  (uint16_t)(0x000006D9 << 3) | 0x04;
    canFilterConfig.FilterMaskIdHigh = (uint16_t)(0x000006D9 >> 13);
    canFilterConfig.FilterMaskIdLow = (uint16_t)(0x000006D9 << 3) | 0x04;

    ret = HAL_CAN_ConfigFilter(&Node->Handle, &canFilterConfig);
    res = HAL_retToRes(ret);

    canFilterConfig.FilterBank = 1;
    canFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;
    canFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    canFilterConfig.FilterIdHigh = 0x06D9 << 5;
    canFilterConfig.FilterIdLow = 0x0000;
    canFilterConfig.FilterMaskIdHigh = 0x04C6 << 5;
    canFilterConfig.FilterMaskIdLow = 0x0000;
    canFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;

    ret = HAL_CAN_ConfigFilter(&Node->Handle, &canFilterConfig);
    res = HAL_retToRes(ret);


    canFilterConfig.FilterBank = 3;
    canFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    canFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;
    canFilterConfig.FilterIdHigh = 0x06D9 << 5;
    canFilterConfig.FilterIdLow = 0x0000;
    canFilterConfig.FilterMaskIdHigh = 0x04C6 << 5;
    canFilterConfig.FilterMaskIdLow = 0x0000;
    canFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;

    ret = HAL_CAN_ConfigFilter(&Node->Handle, &canFilterConfig);
    res = HAL_retToRes(ret);
#endif

    return res;
}
#endif

/*. These bits must be configured while bxCAN is in Initialization mode.
 Once test mode has been selected, the INRQ bit in the CAN_MCR register must be reset to enter Normal mode.

 As a safeguard against programming errors, the configuration of the Bit Timing register
 (CAN_BTR) is only possible while the device is in Standby mode.

 */
bool can_mcal_baudrate_set(const uint8_t num, const uint32_t baudrate) {
    bool res = false;
    can_phy_connect_ctrl(num, false);

    LOG_INFO(CAN, "CAN%u,Set,BaudRate:%u", num, baudrate);
    res = can_mode_set(num, CAN_STM_MODE_INITIALIZATION);
    if(res) {
        uint32_t bus_freq_hz = can_base_clock_get(num);
        CanSegmentInfo_t Segment = {0};
        res = can_stm32_segment_info_calc(bus_freq_hz, baudrate, &Segment);
        if(res) {
            CanInfo_t* Info = CanGetInfo(num);
            if(Info) {
                CanReg_BTR_t BTR;
                BTR.dword = Info->CANx->BTR;
                res = can_segment_to_btr(&Segment, &BTR);
                if(res) {
                    Info->CANx->BTR = BTR.dword;
                }
            }
        }
        can_mode_set(num, CAN_STM_MODE_NORMAL);
    }

    can_phy_connect_ctrl(num, true);
    return res;
}
#ifdef HAS_CAN_STM32
bool can_init_notification(CanHandle_t* const Node) {
    bool res = false;
    HAL_StatusTypeDef ret = HAL_ERROR;
    ret = HAL_CAN_ActivateNotification(&Node->Handle, CAN_IT_RX_FIFO0_FULL);
    ret = HAL_CAN_ActivateNotification(&Node->Handle, CAN_IT_RX_FIFO0_MSG_PENDING);
    ret = HAL_CAN_ActivateNotification(&Node->Handle, CAN_IT_RX_FIFO0_OVERRUN);
    ret = HAL_CAN_ActivateNotification(&Node->Handle, CAN_IT_RX_FIFO1_FULL);
    ret = HAL_CAN_ActivateNotification(&Node->Handle, CAN_IT_RX_FIFO1_MSG_PENDING);
    ret = HAL_CAN_ActivateNotification(&Node->Handle, CAN_IT_RX_FIFO1_OVERRUN);
    ret = HAL_CAN_ActivateNotification(&Node->Handle, CAN_IT_WAKEUP);
    ret = HAL_CAN_ActivateNotification(&Node->Handle, CAN_IT_SLEEP_ACK);
    ret = HAL_CAN_ActivateNotification(&Node->Handle, CAN_IT_ERROR_WARNING);
    ret = HAL_CAN_ActivateNotification(&Node->Handle, CAN_IT_ERROR_PASSIVE);
    ret = HAL_CAN_ActivateNotification(&Node->Handle, CAN_IT_BUSOFF);
    ret = HAL_CAN_ActivateNotification(&Node->Handle, CAN_IT_ERROR);
    res = HAL_retToRes(ret);
    return res;
}
#endif

bool can_rx_all(const uint8_t can_num) {
    bool res = false;
    LOG_WARNING(CAN, "CAN%u,RxAllId", can_num);
    res = can_mcal_filter_id_mask_set(can_num, 0, CAN_FRAME_ID_STANDARD, 0, 0);
    res = can_mcal_filter_id_mask_set(can_num, 1, CAN_FRAME_ID_EXTENDED, 0, 0) && res;
    return res;
}

bool can_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(CAN, "CAN%u", num);
    const CanConfig_t* Config = CanGetConfig(num);
    if(Config) {
        res = CanIsValidConfig(Config);
        if(res) {
            res = can_interrupt_ctrl(num, false);
#ifdef HAS_CAN_DIAG
            LOG_WARNING(CAN, "%s", CanConfigToStr(Config));
#endif
            const CanInfo_t* Info = CanGetInfo(num);
            if(Info) {
                CanHandle_t* Node = CanGetNode(num);
                if(Node) {
                    Node->CANx = Info->CANx;
#ifdef HAS_CAN_STM32
                    Node->Handle.Instance = Info->CANx;
                    res = can_init_common(Config, Node);
                    res = can_init_node(Node);
                    res = can_clock_ctrl(num, true);
                    // res = can_interrupt_ctrl(num, Config->interrupt_on);
                    // res = can_priority_ctrl(num, Config->interrupt_priority);
                    res = can_config_to_init(Config, &Node->Handle.Init);
                    if(res) {
#ifdef HAS_LED_MONO
                        led_mono_ctrl(Node->led_num_rx, false);
                        led_mono_ctrl(Node->led_num_tx, false);
#endif

                        HAL_StatusTypeDef ret = HAL_ERROR;
                        can_phy_connect_ctrl(num, false);
                        ret = HAL_CAN_Init(&Node->Handle);
                        can_phy_connect_ctrl(num, true);
                        res = HAL_retToRes(ret);
                        if(res) {
                            res = can_init_filters(Config, Node);
                            if(Config->rx_all) {
                                can_rx_all(num);
                            }
                            ret = HAL_CAN_Start(&Node->Handle);
                            res = HAL_retToRes(ret);
                            res = can_init_notification(Node);
                            LOG_INFO(CAN, "CAN%u,InitOk", num);
                            Node->init_done = true;
                        }
                    }
#endif
                } else {
                    LOG_ERROR(CAN, "NodeErr %u", num);
                }
            }
        } else {
            LOG_ERROR(CAN, "ConfigErr %u", num);
        }
        can_interrupt_ctrl(num, Config->interrupt_on);
        can_priority_ctrl(num, Config->interrupt_priority);
    } else {
        LOG_PARN(CAN, "ConfigErr %u", num);
    }
    return res;
}
