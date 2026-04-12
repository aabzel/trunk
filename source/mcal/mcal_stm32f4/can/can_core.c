#include "can_core.h"

#include <limits.h>
#include <stdlib.h>

#include "bit_utils.h"
#include "clock_mcal.h"
#include "code_generator.h"
#include "common_diag.h"
#include "float_utils.h"
#include "interrupt_mcal.h"

bool CanIsValidInfo(const CanInfo_t* const Info) {
    bool res = false;
    if(Info) {
        res = true;
    }
    return res;
}

#define FLEX_CAN_INFO_ONE(NUM)                                                                                         \
    {                                                                                                                  \
        .num = NUM,                                                                                                    \
        .CANx = CAN##NUM,                                                                                              \
        .nvram_id = PAR_ID_CAN##NUM##_BITRATE_HZ,                                                                      \
        .clock_bus = CLOCK_BUS_APB1,                                                                                   \
        .valid = true,                                                                                                 \
        .irq_n_tx = CAN##NUM##_TX_IRQn,                                                                                \
        .irq_n_rx0 = CAN##NUM##_RX0_IRQn,                                                                              \
        .irq_n_rx1 = CAN##NUM##_RX1_IRQn,                                                                              \
        .irq_n_sce = CAN##NUM##_SCE_IRQn,                                                                              \
    },

#ifdef HAS_CAN1
#define FLEX_CAN_INFO_CAN1 FLEX_CAN_INFO_ONE(1)
#else
#define FLEX_CAN_INFO_CAN1
#endif

#ifdef HAS_CAN2
#define FLEX_CAN_INFO_CAN2 FLEX_CAN_INFO_ONE(2)
#else
#define FLEX_CAN_INFO_CAN2
#endif

#define CAN_INFO_ALL                                                                                                   \
    FLEX_CAN_INFO_CAN1                                                                                                 \
    FLEX_CAN_INFO_CAN2

static const CanInfo_t CanInfo[] = {CAN_INFO_ALL};

COMPONENT_GET_INFO(Can)

const CanInfo_t* CanXToInfo(const CAN_TypeDef* const CANx) {
    CanInfo_t* Info = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(CanInfo);
    for(i = 0; i < cnt; i++) {
        if(CANx == CanInfo[i].CANx) {
            if(CanInfo[i].valid) {
                Info = (CanInfo_t*)&CanInfo[i];
                break;
            }
        }
    }
    return Info;
}

CanInfo_t* CanInterfaceToInfo(const InterfaceType_t interface_if) {
    CanInfo_t* Info = NULL;
    Info = CanGetInfo(interface_if.num);
    return Info;
}

StorageId_t can_nvran_id_get(const uint8_t num) {
    StorageId_t nvran_id = PAR_ID_NAN;
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        nvran_id = Info->nvram_id;
    }
    return nvran_id;
}

/*CAN filter activation register (CAN_FA1R)
 */
bool can_filter_is_active(const uint8_t num, const uint8_t filter_num) {
    bool on_off = false;
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        on_off = CHECK_BIT_NUM(Info->CANx->FA1R, filter_num);
    }
    return on_off;
}

/*
 CAN_FFA1R
 CAN filter FIFO assignment register (CAN_FFA1R)
 This register can be written only when the filter initialization mode is set (FINIT=1) in the
 CAN_FMR register.
 */
CanFFAxCode_t can_filter_fifo(const uint8_t num, const uint8_t filter_num) {
    CanFFAxCode_t fifo = CAN_FILTER_FIFO_UNDEF;
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        fifo = CHECK_BIT_NUM(Info->CANx->FFA1R, filter_num);
    }
    return fifo;
}

/**/
CanFilterScale_t can_filter_scale(const uint8_t num, const uint8_t filter_num) {
    CanFilterScale_t scale = CAN_FILTER_SCALE_UNDEF;
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        scale = CHECK_BIT_NUM(Info->CANx->FS1R, filter_num);
    }
    return scale;
}

/*CAN filter mode register (CAN_FM1R)*/
CanFilterMode_t can_filter_mode(const uint8_t num, const uint8_t filter_num) {
    CanFilterMode_t scale = CAN_FILTER_MODE_UNDEF;
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        scale = CHECK_BIT_NUM(Info->CANx->FM1R, filter_num);
    }
    return scale;
}

bool can_interrupt_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        res = true;
        res = interrupt_control(Info->irq_n_tx, on_off) && res;
        res = interrupt_control(Info->irq_n_rx0, on_off) && res;
        res = interrupt_control(Info->irq_n_rx1, on_off) && res;
        res = interrupt_control(Info->irq_n_sce, on_off) && res;
    }
    return res;
}

static bool can1_clock_ctrl(bool on_off) {
    bool res = true;
    if(on_off) {
        __HAL_RCC_CAN1_CLK_ENABLE();
    } else {
        __HAL_RCC_CAN1_CLK_DISABLE();
    }
    return res;
}

static bool can2_clock_ctrl(bool on_off) {
    bool res = true;
    if(on_off) {
        __HAL_RCC_CAN2_CLK_ENABLE();
    } else {
        __HAL_RCC_CAN2_CLK_DISABLE();
    }
    return res;
}

bool can_clock_ctrl(uint8_t num, bool on_off) {
    bool res = true;
    switch(num) {
    case 1:
        res = can1_clock_ctrl(on_off);
        break;
    case 2:
        res = can2_clock_ctrl(on_off);
        break;
    default:
        break;
    }
    return res;
}

bool can_priority_ctrl(uint8_t num, uint8_t preempt_priority) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        res = true;
        res = interrupt_set_priority(Info->irq_n_tx, preempt_priority) && res;
        res = interrupt_set_priority(Info->irq_n_rx0, preempt_priority) && res;
        res = interrupt_set_priority(Info->irq_n_rx1, preempt_priority) && res;
        res = interrupt_set_priority(Info->irq_n_sce, preempt_priority) && res;
    }
    return res;
}

CanTxFrame_t CanRTRtoFrameType(const uint32_t rtr) {
    CanTxFrame_t frame_type = CAN_TX_FRAME_UNDEF;
    switch(rtr) {
    case CAN_RTR_DATA:
        frame_type = CAN_TX_FRAME_DATA;
        break;
    case CAN_RTR_REMOTE:
        frame_type = CAN_TX_FRAME_REMOTE;
        break;
    default:
        break;
    }
    return frame_type;
}

bool CanCAN_BTRToSegment(CanReg_BTR_t* pBTR, CanSegmentInfo_t* const Segment) {
    bool res = false;
    if(pBTR) {
        if(Segment) {
            Segment->phase_1 = pBTR->TS1 + 1;   //     tBS1 = tq x (TS1[3:0] + 1)
            Segment->phase_2 = pBTR->TS2 + 1;   //     tBS2 = tq x (TS2[2:0] + 1)
            Segment->prescaler = pBTR->BRP + 1; //  tq = (BRP[9:0]+1) x tPCLK
            Segment->propagation = 0;
            Segment->synchronization = pBTR->SJW + 1; //     tRJW = tq x (SJW[1:0] + 1)
            res = true;
        }
    }
    return res;
}

/*CAN bit timing register (CAN_BTR)*/
bool can_segment_to_btr(const CanSegmentInfo_t* const Segment, CanReg_BTR_t* const pReg) {
    bool res = false;
    if(Segment) {
        if(pReg) {
            /* Bits 25:24 SJW[1:0]: Resynchronization jump width */
            pReg->SJW = (Segment->synchronization - 1);

            /* Bits 22:20 TS2[2:0]: Time segment 2 */
            pReg->TS2 = (Segment->phase_2 - 1);

            /* Bits 19:16 TS1[3:0]: Time segment 1 */
            pReg->TS1 = (Segment->phase_1 - 1);

            /* Bits 9:0 BRP[9:0]: Baud rate prescaler       */
            pReg->BRP = Segment->prescaler - 1;
            res = true;
        }
    }

    return res;
}

bool can_segments_get(uint8_t num, CanSegmentInfo_t* const SegmentInfo) {
    bool res = true;
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanReg_BTR_t BTR;
        BTR.dword = Info->CANx->BTR;
        res = CanCAN_BTRToSegment(&BTR, SegmentInfo);
        res = true;
    }
    return res;
}

/*
 Bits 23:16 TEC[7:0]: Least significant byte of the 9-bit transmit error counter
 The implementing part of the fault confinement mechanism of the CAN protocol.
 */
bool can_tec_get(uint8_t num, uint32_t* const tec) {
    bool res = true;
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanReg_ESR_t CAN_ESR;
        CAN_ESR.dword = Info->CANx->ESR;
        if(tec) {
            *tec = CAN_ESR.TEC;
            res = true;
        }
    }
    return res;
}

/*
 REC[7:0]: Receive error counter
 The implementing part of the fault confinement mechanism of the CAN protocol. In case of
 an error during reception, this counter is incremented by 1 or by 8 depending on the error
 condition as defined by the CAN standard. After every successful reception the counter is
 decremented by 1 or reset to 120 if its value was higher than 128. When the counter value
 exceeds 127, the CAN controller enters the error passive state
 */
bool can_rec_get(uint8_t num, uint32_t* const rec) {
    bool res = true;
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanReg_ESR_t CAN_ESR;
        CAN_ESR.dword = Info->CANx->ESR;
        if(rec) {
            *rec = CAN_ESR.REC;
            res = true;
        }
    }
    return res;
}

static bool can_wait_initialization_mode_ll(const CanInfo_t* const Info, const uint32_t timeout_ms) {
    bool res = false;
    bool loop = true;
    uint32_t start_ms = time_get_ms32();
    while(loop) {
        CanReg_MSR_t MSR;
        MSR.dword = Info->CANx->MSR;
        if(CAN_MSR_INAK_INITIALIZATION == MSR.INAK) {
            res = true;
            loop = false;
            break;
        }
        loop = time_wait_timeout(start_ms, timeout_ms);
    }
    return res;
}

bool can_mode_set_initialization(const uint8_t num) {
    bool res = false;
    can_phy_connect_ctrl(num, false);
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanReg_MCR_t MCR;
        MCR.dword = 0;
        MCR.dword = Info->CANx->MCR;
        MCR.INRQ = CAN_INRQ_INITIALIZATION;
        Info->CANx->MCR = MCR.dword;
        res = can_wait_initialization_mode_ll(Info, CAN_WAIT_INIT_MODE_TIMEOUT_MS);
    }
    return res;
}

uint32_t CanPhase1ToTimeSeg1(const uint32_t phase_1) {
    uint32_t time_seg1 = CAN_BS1_1TQ;
    switch(phase_1) {
    case 1:
        time_seg1 = CAN_BS1_1TQ;
        break;
    case 2:
        time_seg1 = CAN_BS1_2TQ;
        break;
    case 3:
        time_seg1 = CAN_BS1_3TQ;
        break;
    case 4:
        time_seg1 = CAN_BS1_4TQ;
        break;
    case 5:
        time_seg1 = CAN_BS1_5TQ;
        break;
    case 6:
        time_seg1 = CAN_BS1_6TQ;
        break;
    case 7:
        time_seg1 = CAN_BS1_7TQ;
        break;
    case 8:
        time_seg1 = CAN_BS1_8TQ;
        break;
    case 9:
        time_seg1 = CAN_BS1_9TQ;
        break;
    case 10:
        time_seg1 = CAN_BS1_10TQ;
        break;
    case 11:
        time_seg1 = CAN_BS1_11TQ;
        break;
    case 12:
        time_seg1 = CAN_BS1_12TQ;
        break;
    case 13:
        time_seg1 = CAN_BS1_13TQ;
        break;
    case 14:
        time_seg1 = CAN_BS1_14TQ;
        break;
    case 15:
        time_seg1 = CAN_BS1_15TQ;
        break;
    case 16:
        time_seg1 = CAN_BS1_16TQ;
        break;
    default:
        time_seg1 = CAN_BS1_8TQ;
        break;
    }
    return time_seg1;
}

uint32_t CanLoopBackToOperatingMode(const bool on_off) {
    uint32_t op_mode = CAN_MODE_NORMAL;
    if(on_off) {
        op_mode = CAN_MODE_LOOPBACK;
    } else {
        op_mode = CAN_MODE_NORMAL;
    }
    return op_mode;
}

uint32_t CanPhase2ToTimeSeg2(const uint32_t phase_2) {
    uint32_t time_seg_2 = CAN_BS2_1TQ;
    switch(phase_2) {
    case 1:
        time_seg_2 = CAN_BS2_1TQ; /* 1 time quantum */
        break;
    case 2:
        time_seg_2 = CAN_BS2_2TQ; /* 2 time quantum */
        break;
    case 3:
        time_seg_2 = CAN_BS2_3TQ; /* 3 time quantum */
        break;
    case 4:
        time_seg_2 = CAN_BS2_4TQ; /* 4 time quantum */
        break;
    case 5:
        time_seg_2 = CAN_BS2_5TQ; /* 5 time quantum */
        break;
    case 6:
        time_seg_2 = CAN_BS2_6TQ; /* 6 time quantum */
        break;
    case 7:
        time_seg_2 = CAN_BS2_7TQ; /* 7 time quantum */
        break;
    case 8:
        time_seg_2 = CAN_BS2_8TQ; /* 8 time quantum */
        break;
    default:
        time_seg_2 = CAN_BS2_1TQ;
        break;
    }
    return time_seg_2;
}

uint32_t CanCanTxFrameToRtr(const CanTxFrame_t frame_type) {
    uint32_t rtr = CAN_RTR_DATA;
    switch(frame_type) {
    case CAN_TX_FRAME_DATA:
        rtr = CAN_RTR_DATA;
        break;
    case CAN_TX_FRAME_REMOTE:
        rtr = CAN_RTR_REMOTE;
        break;
    default:
        break;
    }
    return rtr;
}

uint32_t CanSynchroToSyncJumpWidth(const uint32_t synchronization) {
    uint32_t sync_jump_width = CAN_SJW_1TQ;
    switch(synchronization) {
    case 1:
        sync_jump_width = CAN_SJW_1TQ;
        break;
    case 2:
        sync_jump_width = CAN_SJW_2TQ;
        break;
    case 3:
        sync_jump_width = CAN_SJW_3TQ;
        break;
    case 4:
        sync_jump_width = CAN_SJW_4TQ;
        break;
    default:
        break;
    }
    return sync_jump_width;
}

uint32_t can_segment_info_to_bitrate(const uint32_t base_clock_hz, const uint16_t brp, const uint8_t sjw,
                                     const uint8_t tseg1, const uint8_t tseg2) {
    uint32_t bit_rate = 0;
    CanReg_BTR_t CAN_BTR = {0};
    CAN_BTR.BRP = brp - 1;
    CAN_BTR.TS1 = tseg1 - 1;
    CAN_BTR.TS2 = tseg2 - 1;
    CAN_BTR.SJW = sjw - 1;
    can_mcal_baudrate_calc(base_clock_hz, CAN_BTR, &bit_rate);
    return bit_rate;
}

uint32_t CanIdTypeToFrameIDE(const CanIdentifier_t id_type) {
    uint32_t ide = CAN_ID_EXT;
    switch(id_type) {
    case CAN_FRAME_ID_STANDARD:
        ide = CAN_ID_STD;
        break;
    case CAN_FRAME_ID_EXTENDED:
        ide = CAN_ID_EXT;
        break;
    default:
        ide = CAN_ID_EXT;
        break;
    }
    return ide;
}

uint32_t CanModeToOperatingMode(const CanMode_t mode) {
    uint32_t op_mode = CAN_MODE_NORMAL;
    switch(mode) {
    case CAN_CFG_MODE_COMMUNICATE:
        op_mode = CAN_MODE_NORMAL;
        break;
    case CAN_CFG_MODE_LOOPBACK:
        op_mode = CAN_MODE_LOOPBACK;
        break;
    case CAN_CFG_MODE_LISTENONLY:
        op_mode = CAN_MODE_SILENT;
        break;
    case CAN_CFG_MODE_LISTENONLY_LOOPBACK:
        op_mode = CAN_MODE_SILENT_LOOPBACK;
        break;
    case CAN_CFG_MODE_FREEZE:
        op_mode = CAN_MODE_SILENT;
        break;
    default:
        op_mode = CAN_MODE_NORMAL;
        break;
    }
    return op_mode;
}

CanIdentifier_t CanIDEtoIdentifierType(const uint32_t ide) {
    CanIdentifier_t id_type = CAN_FRAME_ID_UNDEF;
    switch(ide) {
    case CAN_ID_STD:
        id_type = CAN_FRAME_ID_STANDARD;
        break;
    case CAN_ID_EXT:
        id_type = CAN_FRAME_ID_EXTENDED;
        break;
    default:
        break;
    }
    return id_type;
}

bool can_mode_set_normal(const uint8_t num) {
    bool res = false;
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanReg_MCR_t MCR;
        MCR.dword = Info->CANx->MCR;
        MCR.INRQ = CAN_INRQ_NORMAL;
        Info->CANx->MCR = MCR.dword;
        res = true;
    }
    return res;
}

/*see Figure 346. Bit timing*/
bool can_mcal_baudrate_calc(const uint32_t base_clock_hz, const CanReg_BTR_t CAN_BTR, uint32_t* const bit_rate) {
    bool res = false;
    if(base_clock_hz) {
        if(bit_rate) {
            float t_base_period_s = 1.0 / ((float)base_clock_hz);
            uint32_t baud_rate_prescaler = CAN_BTR.BRP + 1;
            float tq = ((float)baud_rate_prescaler) * t_base_period_s;
            float sync = tq * (CAN_BTR.SJW + 1);
            float t_bs1 = tq * (CAN_BTR.TS1 + 1);
            float t_bs2 = tq * (CAN_BTR.TS2 + 1);
            float bit_time_s = sync + t_bs1 + t_bs2;
            float bit_rate_hz = 1.0 / bit_time_s;
            *bit_rate = (uint32_t)bit_rate_hz;
            res = true;
        }
    }

    return res;
}

bool can_segment_to_baudrate(uint32_t base_clock_hz, CanSegmentInfo_t* const Segment, uint32_t* const bit_rate) {
    bool res = false;
    CanReg_BTR_t BTR;
    res = can_segment_to_btr(Segment, &BTR);
    res = can_mcal_baudrate_calc(base_clock_hz, BTR, bit_rate);
    return res;
}

/* Figure 346. Bit timing
 cs 1 0x355 0x5555555555555555
 *  */
bool can_stm32_segment_info_calc(uint32_t bus_freq_hz, const uint32_t bit_rate_hz, CanSegmentInfo_t* const Segment) {
    bool res = false;
    LOG_DEBUG(CAN, "busFreq:%u Hz,BitRate:%u Bit/s", bus_freq_hz, bit_rate_hz);
    if(Segment) {
        float tick_period_s = 1.0f / ((float)bus_freq_hz);
#ifdef HAS_FLOAT_DIAG
        LOG_DEBUG(CAN, "tick_period:%s s", FloatBigToStr(tick_period_s));
#endif
        float bit_duration_s = 1.0f / ((float)bit_rate_hz);
#ifdef HAS_FLOAT_DIAG
        LOG_DEBUG(CAN, "bit_duration_s:%s s", FloatBigToStr(bit_duration_s));
#endif
        float bit_precaler = (bit_duration_s) / tick_period_s;
        LOG_DEBUG(CAN, "bit_precaler:%7.3f", bit_precaler);
        float time_quanta_s = bit_duration_s / 16.0f; // 11-242424; 5-252631; 16-
#ifdef HAS_FLOAT_DIAG
        LOG_DEBUG(CAN, "time_quanta:%ss", FloatBigToStr(time_quanta_s));
#endif
        float tq_prescaler = time_quanta_s / tick_period_s;
        Segment->prescaler = ((uint32_t)roundf(tq_prescaler));
        // Segment->prescaler =( (uint32_t)tq_prescaler);
        LOG_DEBUG(CAN, "TqPrescaler:%7.3f->%u", tq_prescaler, Segment->prescaler);
        Segment->synchronization = 1; // 0    3
        Segment->propagation = 0;
        Segment->phase_1 = 8; // 0....15
        Segment->phase_2 = 7; // 0....7

        uint32_t bit_rate_get_hz = 0;
        res = can_segment_to_baudrate(bus_freq_hz, Segment, &bit_rate_get_hz);
#ifdef HAS_CAN_DIAG
        LOG_DEBUG(CAN, "CalcSeg:[%s]->%u Bit/s", CanSegmentInfoToStr(Segment), bit_rate_get_hz);
#endif

        CanBestBtr_t BestBtr;
        BestBtr.error = INT_MAX;
        uint32_t b, t1, t2;
        //  for (s = 0; s <= 3; s++) {
        // }
        for(b = 0; b <= 1023; b++) {
            for(t1 = 0; t1 <= 14; t1++) {
                for(t2 = 0; t2 <= 6; t2++) {
                    CanReg_BTR_t CAN_BTR = {0};
                    CAN_BTR.BRP = b;
                    CAN_BTR.TS1 = t1;
                    CAN_BTR.TS2 = t2;
                    CAN_BTR.SJW = 0;
                    bit_rate_get_hz = 0;
                    res = can_mcal_baudrate_calc(bus_freq_hz, CAN_BTR, &bit_rate_get_hz);
                    if(res) {
                        int32_t diff_hz = ((int32_t)bit_rate_hz) - ((int32_t)bit_rate_get_hz);
                        int32_t abs_diff_hz = abs(diff_hz);
                        if(abs_diff_hz < BestBtr.error) {
                            BestBtr.error = abs_diff_hz;
                            BestBtr.CAN_BTR.dword = CAN_BTR.dword;
                            res = true;
                            if(0 == abs_diff_hz) {
                                LOG_DEBUG(CAN, "SpotSol");
                                // CanDiagRegBTR(CAN_BTR.dword);
                            }
                        }
                    }
                }
            }
        }

        res = CanCAN_BTRToSegment(&BestBtr.CAN_BTR, Segment);

        bit_rate_get_hz = 0;
        res = can_segment_to_baudrate(bus_freq_hz, Segment, &bit_rate_get_hz);
#ifdef HAS_CAN_DIAG
        LOG_INFO(CAN, "SpotSeg:[%s]->%u Bit/s", CanSegmentInfoToStr(Segment), bit_rate_get_hz);
#endif
    }
    return res;
}

uint32_t CanIdTypeToFiltIDE(const CanIdentifier_t id_type) {
    uint32_t filt_ide = CAN_IDE_EXT;
    switch(id_type) {
    case CAN_FRAME_ID_STANDARD: {
        filt_ide = CAN_IDE_STD;
    } break;

    case CAN_FRAME_ID_EXTENDED: {
        filt_ide = CAN_IDE_EXT;
    } break;

    default:
        filt_ide = CAN_IDE_EXT;
        break;
    }
    return filt_ide;
}

uint32_t can_base_clock_get(const uint8_t num) {
    uint32_t bus_freq_hz = 0;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        clock_frequency_get(Info->clock_bus, &bus_freq_hz);
    }
    return bus_freq_hz;
}

bool can_mode_set(const uint8_t num, const CanStmMode_t mode) {
    bool res = false;
    LOG_INFO(CAN, "CAN%u,Mode,Set:%s", num, CanStmModeToStr(mode));
    switch(mode) {
    case CAN_STM_MODE_INITIALIZATION: {
        can_phy_connect_ctrl(num, false);
        res = can_mode_set_initialization(num);
    } break;
    case CAN_STM_MODE_NORMAL: {
        res = can_mode_set_normal(num);
        can_phy_connect_ctrl(num, true);
    } break;
    default: {
        res = false;
    } break;
    }
    return res;
}

uint32_t CanMailBoxNumToCode(const uint32_t mailbox_mum) {
    uint32_t tx_mailbox_code = CAN_TX_MAILBOX0;
    switch(mailbox_mum) {
    case 0:
        tx_mailbox_code = CAN_TX_MAILBOX0;
        break;
    case 1:
        tx_mailbox_code = CAN_TX_MAILBOX1;
        break;
    case 2:
        tx_mailbox_code = CAN_TX_MAILBOX2;
        break;
    default:
        tx_mailbox_code = CAN_TX_MAILBOX0;
        break;
    }
    return tx_mailbox_code;
}
