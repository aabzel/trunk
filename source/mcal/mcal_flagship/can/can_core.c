#include "can_core.h"

#include <limits.h>

#include "can_enhanced_fifo.h"
#include "can_legacy_fifo.h"
#include "can_mcal.h"
#include "can_message_buffer.h"
#include "clock_mcal.h"
#include "code_generator.h"
#include "common_diag.h"
#include "float_utils.h"
#include "interrupt_mcal.h"

bool CanIsValidInfo(const CanInfo_t* const Info) {
    bool res = false;
    if(Info) {
        res = true;

        ifn(Info->pCanNode) {
            LOG_ERROR(CAN, "CAN%u,pCanNode,Error", Info->num);
            res = false;
        }

        ifn(Info->CANx) {
            LOG_ERROR(CAN, "CAN%u,CANx,Error", Info->num);
            res = false;
        }

        ifn(Info->pHandle) {
            LOG_ERROR(CAN, "CAN%u,pHandle,Error", Info->num);
            res = false;
        }

        ifn(Info->irq_n) {
            LOG_ERROR(CAN, "CAN%u,irq_n,Error", Info->num);
            res = false;
        }

        // ifn(Info->pTxSlots) {
        //     LOG_ERROR(CAN, "CAN%u,pTxSlots,Error", Info->num);
        //     res = false ;
        // }
    }
    return res;
}

#define CAN_INFO_ONE(NUM)                                                                                              \
    {                                                                                                                  \
        .num = NUM,                                                                                                    \
        .pCanNode = &canNodes.n##NUM,                                                                                  \
        .nvram_id = PAR_ID_CAN##NUM##_BITRATE_HZ,                                                                      \
        .CANx = FLEXCAN##NUM,                                                                                          \
        .e_clock_name = PCC_CLK_FLEXCAN##NUM,                                                                          \
        .e_instance = FLEXCAN_INSTANCE_##NUM,                                                                          \
        .irq_n = FlexCAN##NUM##_IRQn,                                                                                  \
        .pHandle = &hCan##NUM,                                                                                         \
        .valid = true,                                                                                                 \
    },

//        .pTxSlots = &TxSlotsCAN##NUM,

#ifdef HAS_CAN0
#define CAN_INFO_CAN0 CAN_INFO_ONE(0)
#else
#define CAN_INFO_CAN0
#endif

#ifdef HAS_CAN1
#define CAN_INFO_CAN1 CAN_INFO_ONE(1)
#else
#define CAN_INFO_CAN1
#endif

#ifdef HAS_CAN2
#define CAN_INFO_CAN2 CAN_INFO_ONE(2)
#else
#define CAN_INFO_CAN2
#endif

#ifdef HAS_CAN3
#define CAN_INFO_CAN3 CAN_INFO_ONE(3)
#else
#define CAN_INFO_CAN3
#endif

#ifdef HAS_CAN4
#define CAN_INFO_CAN4 CAN_INFO_ONE(4)
#else
#define CAN_INFO_CAN4
#endif

#ifdef HAS_CAN5
#define CAN_INFO_CAN5 CAN_INFO_ONE(5)
#else
#define CAN_INFO_CAN5
#endif

#ifdef HAS_CAN6
#define CAN_INFO_CAN6 CAN_INFO_ONE(6)
#else
#define CAN_INFO_CAN6
#endif

#ifdef HAS_CAN7
#define CAN_INFO_CAN7 CAN_INFO_ONE(7)
#else
#define CAN_INFO_CAN7
#endif

#ifdef HAS_CAN8
#define CAN_INFO_CAN8 CAN_INFO_ONE(8)
#else
#define CAN_INFO_CAN8
#endif

#ifdef HAS_CAN9
#define CAN_INFO_CAN9 CAN_INFO_ONE(9)
#else
#define CAN_INFO_CAN9
#endif

#define CAN_INFO_ALL                                                                                                   \
    CAN_INFO_CAN0                                                                                                      \
    CAN_INFO_CAN1                                                                                                      \
    CAN_INFO_CAN2                                                                                                      \
    CAN_INFO_CAN3                                                                                                      \
    CAN_INFO_CAN4                                                                                                      \
    CAN_INFO_CAN5                                                                                                      \
    CAN_INFO_CAN6                                                                                                      \
    CAN_INFO_CAN7                                                                                                      \
    CAN_INFO_CAN8                                                                                                      \
    CAN_INFO_CAN9

static const CanInfo_t CanInfo[] = {CAN_INFO_ALL};

COMPONENT_GET_INFO(Can)

Can_CTRL1_CLKSRC_t CanClockSourceToClkSrc(const CanClockSource_t clock_source) {
    Can_CTRL1_CLKSRC_t clk_src = CAN_CTRL1_CLKSRC_UNDEF;
    switch(clock_source) {
    case CAN_CLOCK_SOURCE_PERIPHERAL:
        clk_src = CAN_CTRL1_CLKSRC_PERIPHERAL;
        break;
    case CAN_CLOCK_SOURCE_OSCILLATOR:
        clk_src = CAN_CTRL1_CLKSRC_OSCILLATOR;
        break;
    default:
        clk_src = CAN_CTRL1_CLKSRC_UNDEF;
        break;
    }

    return clk_src;
}

CanInfo_t* CanInterfaceToInfo(const InterfaceType_t interface_if) {
    CanInfo_t* Info = NULL;
    if(INTERFACE_NAME_CAN==interface_if.interface_name){
        Info = CanGetInfo(interface_if.num);
    }
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

CanClockSource_t can_get_clk_src(const uint8_t num) {
    CanClockSource_t clock_source = CAN_CLOCK_SOURCE_UNDEF;
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegCTRL1_t CTRL1;
        CTRL1.dword = Info->CANx->CTRL1;
        switch(CTRL1.CLKSRC) {
        case CAN_CTRL1_CLKSRC_OSCILLATOR: {
            clock_source = CAN_CLOCK_SOURCE_OSCILLATOR;
        } break;
        case CAN_CTRL1_CLKSRC_PERIPHERAL: {
            clock_source = CAN_CLOCK_SOURCE_PERIPHERAL;
        } break;
        default:
            break;
        }
    }
    return clock_source;
}

uint32_t can_base_clock_get(uint8_t num) {
    uint32_t clk_freq_hz = 0;
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanClockSource_t clk_src = can_get_clk_src(num);
        switch(clk_src) {
        case CAN_CLOCK_SOURCE_OSCILLATOR: {
            clk_freq_hz = SCG_GetScgClockFreq(SCG_FOSC_CLK);
        } break;
        case CAN_CLOCK_SOURCE_PERIPHERAL: {
            clk_freq_hz = PCC_GetPccFunctionClock(Info->e_clock_name);
        } break;
        default:
            break;
        }
    }
    return clk_freq_hz;
}

bool can_module_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    LOG_DEBUG(CAN, "CAN%u,Module:%s", num, OnOffToStr(on_off));
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegMCR_t MCR;
        MCR.dword = FLEXCAN_HWA_GetMCR(Info->CANx);
        if(on_off) {
            MCR.MDIS = CAN_MCR_MDIS_ENABLE;
        } else {
            MCR.MDIS = CAN_MCR_MDIS_DISABLE;
        }

        FLEXCAN_HWA_SetMCR(Info->CANx, MCR.dword);
        res = true;
    }
    return res;
}

bool can_module_get(uint8_t num) {
    bool res = false;
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegMCR_t MCR;
        MCR.dword = FLEXCAN_HWA_GetMCR(Info->CANx);
        if(CAN_MCR_MDIS_ENABLE == MCR.MDIS) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

/*
  In Freeze mode MAC ignores the Rx input pin and drives the Tx pin as recessive.
  Stops the prescaler, thus halting all CAN protocol activities.
  Grants write access to the Error Counters register, which is read-only in other modes.
 */
bool can_freeze_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    LOG_DEBUG(CAN, "CAN%u,Freeze:%s", num, OnOffToStr(on_off));
    can_module_ctrl(num, true);

    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegMCR_t MCR;
        MCR.dword = FLEXCAN_HWA_GetMCR(Info->CANx);
        if(on_off) {
            MCR.MDIS = CAN_MCR_MDIS_ENABLE;
            MCR.FRZ = CAN_MCR_FRZ_ENTER_FREEZE_MODE;
            MCR.HALT = CAN_MCR_HALT_ENTERS_FREEZE_MODE;
            FLEXCAN_HWA_SetMCR(Info->CANx, MCR.dword);
            res = can_freeze_wait(Info->CANx, CAN_WAIT_FREEZE_TIMEOUT_MS);
            /*
             In Freeze mode, no transmission or reception of frames is done and synchronicity to the FLEXCAN
             bus is lost.
             */
        } else {
            MCR.MDIS = CAN_MCR_MDIS_ENABLE;
            MCR.FRZ = CAN_MCR_FRZ_FLEE_FREEZE_MODE;
            FLEXCAN_HWA_SetMCR(Info->CANx, MCR.dword);
            res = true;
        }
    }
    return res;
}

bool can_freeze_get(uint8_t num) {
    bool res = false;
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegMCR_t MCR;
        MCR.dword = Info->CANx->MCR;
        if(MCR.FRZACK) {
            res = true;
        }
    }
    return res;
}

float can_time_quanta_get(uint8_t num) {
    float time_quanta_s = -1.0;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        uint32_t freq_hz = 0;
        freq_hz = PCC_GetPccFunctionClock(Info->e_clock_name);
        time_quanta_s = 1.0f / ((float)freq_hz);
    }
    return time_quanta_s;
}

bool can_tec_get(uint8_t num, uint32_t* const tec) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegECR_t Reg;
        Reg.dword = FLEXCAN_HWA_GetErrorCount(Info->CANx);
        if(tec) {
            *tec = Reg.TXERRCNT;
            res = true;
        }
    }
    return res;
}

bool can_rec_get(uint8_t num, uint32_t* const rec) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegECR_t Reg;
        Reg.dword = FLEXCAN_HWA_GetErrorCount(Info->CANx);
        if(rec) {
            *rec = Reg.RXERRCNT;
            res = true;
        }
    }
    return res;
}

Can_CTRL1_CLKSRC_t can_clock_src_get(uint8_t num) {
    Can_CTRL1_CLKSRC_t clock_src = CAN_CTRL1_CLKSRC_UNDEF;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegCTRL1_t CTRL1;
        CTRL1.dword = FLEXCAN_HWA_GetCtrl1(Info->CANx);
        clock_src = CTRL1.CLKSRC;
    }
    return clock_src;
}

bool can_clock_src_set_ll(uint8_t num, const Can_CTRL1_CLKSRC_t clk_src) {
    bool res = false;
    /*In order to guarantee reliable operation, this bit can be written only in Disable
      mode because it is blocked by hardware in other modes.*/
    res = can_module_ctrl(num, false);
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegCTRL1_t CTRL1;
        CTRL1.dword = FLEXCAN_HWA_GetCtrl1(Info->CANx);
        CTRL1.CLKSRC = clk_src;
        FLEXCAN_HWA_SetCtrl1(Info->CANx, CTRL1.dword);
        res = true;
    }

    res = can_module_ctrl(num, true);

    return res;
}

static bool can_segment_to_reg_cbt(const CanSegmentInfo_t* const Segment, CanRegCBT_t* const Reg) {
    bool res = false;
    if(Segment) {
        if(Reg) {
            Reg->dword = 0;
            Reg->BTF = 0; /*Bit Timing Format Enable*/
            Reg->EPRESDIV = Segment->prescaler - 1;
            Reg->EPROPSEG = Segment->propagation - 1;
            Reg->ERJW = Segment->synchronization - 1;
            Reg->EPSEG1 = Segment->phase_1 - 1;
            Reg->EPSEG2 = Segment->phase_2 - 1;
            res = true;
        }
    }
    return res;
}

static bool can_segment_to_reg_ctrl1(const CanSegmentInfo_t* const Segment, CanRegCTRL1_t* Reg) {
    bool res = false;
    if(Segment) {
        if(Reg) {
            Reg->PROPSEG = Segment->propagation - 1;
            Reg->RJW = Segment->synchronization - 1;
            Reg->PSEG1 = Segment->phase_1 - 1;
            Reg->PSEG2 = Segment->phase_2 - 1;
            Reg->PRESDIV = Segment->prescaler - 1;
            res = true;
        }
    }
    return res;
}

bool can_segment_info_calc_custom(uint32_t bus_freq_hz, uint32_t baud_rate_hz, CanSegmentInfo_t* const FoundSegment) {
    bool res = false;
    LOG_INFO(CAN, "Bus:%u Hz,BitRate:%u Hz", bus_freq_hz, baud_rate_hz);

    uint32_t cnt = 0;
    uint32_t min_err = INT_MAX;
    CanSegmentInfo_t SegmentBest = {0};

    if(FoundSegment) {
        bool spot_segment = false;
        uint32_t presdiv = 0;
        for(presdiv = 1; presdiv <= 256; presdiv++) {
            uint32_t resync = 0;
            for(resync = 1; resync <= 4; resync++) {
                uint32_t propseg = 0;
                for(propseg = 1; propseg <= 8; propseg++) {
                    uint32_t seg1 = 0;
                    for(seg1 = 1; seg1 <= 8; seg1++) {
                        uint32_t seg2 = 0;
                        for(seg2 = 1; seg2 <= 8; seg2++) {
                            CanSegmentInfo_t Segment = {0};
                            Segment.prescaler = presdiv;
                            Segment.synchronization = resync;
                            Segment.propagation = propseg;
                            Segment.phase_1 = seg1;
                            Segment.phase_2 = seg2;

                            res = can_is_valid_segment(&Segment);
                            if(res) {
                                uint32_t cur_rate = can_time_seg_to_bit_rate(bus_freq_hz, &Segment);

                                uint32_t diff = math_calc_abs(baud_rate_hz, cur_rate);
                                if(diff < min_err) {
                                    min_err = diff;
                                    SegmentBest = Segment;
                                    spot_segment = true;
                                    cnt++;
                                    LOG_INFO(CAN, "N:%u,Spot:Err:%7u Hz,%10s", cnt, diff,
                                             CanSegmentInfoToStr(&SegmentBest));
                                }
                            }
                        }
                    }
                }
            }
        }
        res = false;
        uint32_t baud_rate_hz = 0;
        if(spot_segment) {
            *FoundSegment = SegmentBest;
            baud_rate_hz = can_time_seg_to_bit_rate(bus_freq_hz, &SegmentBest);
            res = true;
        }

        float bit_duration_s = 1.0f / ((float)baud_rate_hz);
        LOG_INFO(CAN, "BitTime:%s s", FloatBigToStr(bit_duration_s));
    }
    return res;
}

bool can_segments_get(uint8_t num, CanSegmentInfo_t* const SegmentInfo) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegCBT_t CBT;
        CBT.dword = Info->CANx->CBT;
        if(SegmentInfo) {
            SegmentInfo->prescaler = CBT.EPRESDIV + 1;
            SegmentInfo->phase_1 = CBT.EPSEG1 + 1;
            SegmentInfo->phase_2 = CBT.EPSEG2 + 1;
            SegmentInfo->propagation = CBT.EPROPSEG + 1;
            SegmentInfo->synchronization = CBT.ERJW + 1;
            res = true;
        }
    }
    return res;
}

bool can_segments_get_v2(uint8_t num, CanSegmentInfo_t* const SegmentInfo) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegCTRL1_t CTRL1;
        CTRL1.dword = Info->CANx->CTRL1;
        if(SegmentInfo) {
            SegmentInfo->prescaler = CTRL1.PRESDIV + 1;
            SegmentInfo->phase_1 = CTRL1.PSEG1 + 1;
            SegmentInfo->phase_2 = CTRL1.PSEG2 + 1;
            SegmentInfo->propagation = CTRL1.PROPSEG + 1;
            SegmentInfo->synchronization = CTRL1.RJW + 1;
            res = true;
        }
    }
    return res;
}

bool can_clock_src_set(const uint8_t num, const CanClockSource_t clock_source) {
    bool res = false;
    res = can_module_ctrl(num, false);
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegCTRL1_t CTRL1;
        CTRL1.dword = Info->CANx->CTRL1;
        CTRL1.CLKSRC = CanClockSourceToClkSrc(clock_source);
        Info->CANx->CTRL1 = CTRL1.dword;
        res = true;
    }
    res = can_module_ctrl(num, true);
    return res;
}

bool can_mcal_baudrate_set_v0(uint8_t num, uint32_t baud_rate_hz) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        uint32_t bus_freq_hz = can_base_clock_get(num);
        CanSegmentInfo_t Segment = {0};
        res = can_segment_info_calc(bus_freq_hz, baud_rate_hz, &Segment);
        if(res) {
            CanRegCTRL1_t CTRL1 = {0};
            CTRL1.dword = FLEXCAN_HWA_GetCtrl1(Info->CANx);

            res = can_segment_to_reg_ctrl1(&Segment, &CTRL1);
            if(res) {
                res = can_freeze_ctrl(num, true);
                if(res) {
                    LOG_INFO(CAN, "CAN%u,SetBitRate:%u Bps,BusFreq:%u Hz,Seg:%s,CTRL1:0x%08x", num, baud_rate_hz,
                             bus_freq_hz, CanSegmentInfoToStr(&Segment), CTRL1.dword);
                    FLEXCAN_HWA_SetCtrl1(Info->CANx, CTRL1.dword);
                    can_freeze_ctrl(num, false);
                }
            }
        }
    }
    return res;
}

bool can_mcal_baudrate_set_v1(uint8_t num, uint32_t baud_rate_hz) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        uint32_t bus_freq_hz = can_base_clock_get(num);
        CanSegmentInfo_t Segment = {0};
        res = can_segment_info_calc(bus_freq_hz, baud_rate_hz, &Segment);
        if(res) {
            CanRegCBT_t CBT = {0};
            res = can_segment_to_reg_cbt(&Segment, &CBT);
            if(res) {
                LOG_INFO(CAN, "CAN%u,SetBitRate:%u Bps,BusFreq:%u Hz,Seg:%s,CBT:0x%08x", num, baud_rate_hz, bus_freq_hz,
                         CanSegmentInfoToStr(&Segment), CBT.dword);
                FLEXCAN_HWA_SetCBT(Info->CANx, CBT.dword);
            }
        }
    }
    return res;
}

bool can_mcal_baudrate_get(uint8_t num, uint32_t* const bit_rate) {
    bool res = false;
    uint32_t calc_bps = 0;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        float time_quanta_s = can_time_quanta_get(num);
        CanRegENCBT_t Reg = {0};
        Reg.dword = Info->CANx->ENCBT;
        uint32_t tc = (Reg.NRJW + 1) + (Reg.NTSEG1 + 1) + (Reg.NTSEG2 + 1) + 1;
        float bit_duration_s = ((float)tc) * time_quanta_s;
        calc_bps = (uint32_t)(1.0 / bit_duration_s);
        if(bit_rate) {
            *bit_rate = calc_bps;
            res = true;
        }
    }
    return res;
}

/*can be called from ISR*/
bool can_interrupt_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        // LOG_INFO(CAN, "CAN%u,INT:%u,EN:%u", num, Info->irq_n, on_off);
        res = interrupt_control(Info->irq_n, on_off);
    }
    return res;
}

bool can_mcal_baudrate_get_v2(uint8_t num, uint32_t* const bit_rate) {
    bool res = false;
    uint32_t calc_bps = 0;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegCBT_t Reg = {0};
        Reg.dword = Info->CANx->CBT;
        uint32_t freq_hz = PCC_GetPccFunctionClock(Info->e_clock_name);

        float time_quanta_s = ((float)(Reg.EPRESDIV + 1)) / ((float)freq_hz);
        uint32_t bit_dur_tq = ((Reg.ERJW + 1) + (Reg.EPROPSEG + 1) + (Reg.EPSEG1 + 1) + (Reg.EPSEG2 + 1));
        float bit_duration_s = ((float)bit_dur_tq) * time_quanta_s;
        calc_bps = (uint32_t)(1.0 / bit_duration_s);
        if(bit_rate) {
            *bit_rate = calc_bps;
            res = true;
        }
    }
    return res;
}

bool can_freeze_wait(volatile FLEXCAN_Type* CANx, uint32_t timeout_ms) {
    bool res = false;
    uint32_t start_ms = time_get_ms32();
    bool cycle = true;
    while(cycle) {
        CanRegMCR_t MCR;
        MCR.dword = FLEXCAN_HWA_GetMCR(CANx);
        if(MCR.FRZACK) {
            res = true;
            break;
        }
        cycle = time_wait_timeout(start_ms, timeout_ms);
    }

    if(!res) {
        LOG_ERROR(CAN, "FreeseEnterError");
    }
    return res;
}

bool can_loopback_get(const uint8_t num, bool* const on_off) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        if(on_off) {
            CanRegCTRL1_t CTRL1;
            CTRL1.dword = Info->CANx->CTRL1;
            *on_off = CTRL1.LPB;
            res = true;
        }
    }
    return res;
}

bool can_reset_error_counters(const uint8_t num) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        can_freeze_ctrl(num, true);
        if(Info->CANx) {
            Info->CANx->ECR = 0x00000000;
            res = true;
        }
        can_freeze_ctrl(num, false);
    }
    return res;
}

static CanMCR_SRXDIS_t can_on_off_to_mcr_srxdis(const bool on_off) {
    CanMCR_SRXDIS_t mcr_srxdis = CAN_MCR_SRXDIS_UNDEF;
    if(on_off) {
        mcr_srxdis = CAN_MCR_SRXDIS_SELF_RECEPTION_ON;
    } else {
        mcr_srxdis = CAN_MCR_SRXDIS_SELF_RECEPTION_OFF;
    }
    return mcr_srxdis;
}

/* SRXDIS bit can be written only in Freeze mode because it is blocked by hardware in other
   modes*/
static bool can_self_rx_set_ll(const CanInfo_t* Info, const bool on_off) {
    bool res = true;
    CanRegMCR_t MCR;
    MCR.dword = Info->CANx->MCR;
    MCR.SRXDIS = can_on_off_to_mcr_srxdis(on_off);
    /* In Loop Back mode, MCR[SRXDIS] cannot be asserted because this will impede the
       self-reception of a transmitted message
     */
    Info->CANx->MCR = MCR.dword;

    return res;
}

/*
 Configures FLEXCAN to operate in Loop-Back mode. This bit can be written only in Freeze mode
 because it is blocked by hardware in other modes
*/
bool can_loopback_set(const uint8_t num, const bool on_off) {
    bool res = false;
    LOG_INFO(CAN, "CAN%u,LoopBack:%s", num, OnOffToStr(on_off));
    can_freeze_ctrl(num, true);
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        can_self_rx_set_ll(Info, on_off);

        CanRegFDCTRL_t FDCTRL;
        FDCTRL.dword = Info->CANx->FDCTRL;
        FDCTRL.TDCEN = FDCTRL_TDCEN_DISABLE;
        Info->CANx->FDCTRL = FDCTRL.dword;

        CanRegETDC_t ETDC;
        ETDC.dword = Info->CANx->ETDC;
        ETDC.ETDCEN = ETDC_ETDCEN_TDC_DISABLE;
        Info->CANx->ETDC = ETDC.dword;

        CanRegCTRL1_t CTRL1;
        CTRL1.dword = Info->CANx->CTRL1;
        CTRL1.LPB = (uint32_t)on_off;
        Info->CANx->CTRL1 = CTRL1.dword;
        res = true;
    }
    can_freeze_ctrl(num, false);
    return res;
}

CanMacMode_t can_get_mac_mode(const uint8_t num) {
    CanMacMode_t mac_mode = CAN_MAC_MODE_UNDEF;
    bool res = false;

#ifdef HAS_CAN_MESSAGE_BUFFER
    res = can_is_mode_message_buffer(num);
    if(res) {
        mac_mode = CAN_MAC_MODE_MESSAGE_BUFFER;
    }
#endif

#ifdef HAS_CAN_LEGACY_FIFO
    res = can_is_mode_legacy_fifo(num);
    if(res) {
        mac_mode = CAN_MAC_MODE_LEGACY_FIFO;
    }
#endif

#ifdef HAS_CAN_ENHANCED_FIFO
    res = can_is_mode_enhanced_fifo(num);
    if(res) {
        mac_mode = CAN_MAC_MODE_ENHANCED_FIFO;
    }
#endif
    return mac_mode;
}
