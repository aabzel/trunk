#include "can_segments_stm32.h"

#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "can_mcal.h"
#include "float_diag.h"
#include "log.h"
#include "pll_types.h"

/*CAN bit timing register (CAN_BTR)*/
static bool can_segment_to_reg_btr(const CanSegmentInfo_t* const Segment, CanRegBTR_t* const pReg) {
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

/*see Figure 346. Bit timing*/
static bool bxcan_reg_btr_to_baudrate(const uint32_t base_clock_hz, const CanRegBTR_t CAN_BTR,
                                      uint32_t* const bit_rate) {
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

static bool bxCanRegBTRtoSegment(CanRegBTR_t* pBTR, CanSegmentInfo_t* const Segment) {
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

static bool can_segment_to_bxcan_baudrate(uint32_t base_clock_hz, CanSegmentInfo_t* const Segment,
                                          uint32_t* const bit_rate) {
    bool res = false;
    CanRegBTR_t BTR;
    res = can_segment_to_reg_btr(Segment, &BTR);
    res = bxcan_reg_btr_to_baudrate(base_clock_hz, BTR, bit_rate);
    return res;
}

/* Figure 346. Bit timing
 *  */
bool bxcan_segment_info_calc(const uint32_t bus_freq_hz, const uint32_t bit_rate_hz, CanSegmentInfo_t* const Segment) {
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
        res = can_segment_to_bxcan_baudrate(bus_freq_hz, Segment, &bit_rate_get_hz);
#ifdef HAS_CAN_DIAG
        LOG_DEBUG(CAN, "CalcSeg:[%s]->%u Bit/s", CanSegmentInfoToStr(Segment), bit_rate_get_hz);
#endif

        CanBestRegBtr_t BestBtr;
        BestBtr.error = INT_MAX;
        uint32_t b, t1, t2;
        // for (sjw = 0; sjw <= 3; sjw++) {
        // }
        for(b = 0; b <= 1023; b++) {
            for(t1 = 0; t1 <= 14; t1++) {
                for(t2 = 0; t2 <= 6; t2++) {
                    CanRegBTR_t CAN_BTR = {0};
                    CAN_BTR.BRP = b;
                    CAN_BTR.TS1 = t1;
                    CAN_BTR.TS2 = t2;
                    CAN_BTR.SJW = 0;
                    bit_rate_get_hz = 0;
                    res = bxcan_reg_btr_to_baudrate(bus_freq_hz, CAN_BTR, &bit_rate_get_hz);
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

        res = bxCanRegBTRtoSegment(&BestBtr.CAN_BTR, Segment);

        bit_rate_get_hz = 0;
        res = can_segment_to_bxcan_baudrate(bus_freq_hz, Segment, &bit_rate_get_hz);
#ifdef HAS_CAN_DIAG
        LOG_DEBUG(CAN, "SpotSeg:[%s]->%u Bit/s", CanSegmentInfoToStr(Segment), bit_rate_get_hz);
#endif
    }
    return res;
}

bool bxcan_segment_info_calc_all(const uint32_t bus_freq_hz) {
    bool res = false;
    LOG_INFO(CAN, "busFreq:%u Hz", bus_freq_hz);
    static const table_col_t cols[] = {
        {9, "RateSet"}, {9, "RateEff"}, {5, "psc"},   {5, "syn"},  {5, "pro"},
        {5, "ph1"},     {5, "ph2"},     {7, "SamPo"}, {6, "dDur"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t i = 0;
    uint32_t cnt = can_get_typical_bitrate_cnt();
    for(i = 0; i < cnt; i++) {
        uint32_t bit_rate_hz = CanTypicalBitRates[i];
        CanSegmentInfo_t SegmentInfo = {0};
        res = bxcan_segment_info_calc(bus_freq_hz, bit_rate_hz, &SegmentInfo);

        float sample_point = can_segment_to_fetch_present(&SegmentInfo);
        uint32_t bit_duration_tq = can_segment_to_bit_duration_tq(&SegmentInfo);

        uint32_t bit_rate_effective = 0;
        res = can_segment_to_bxcan_baudrate(bus_freq_hz, &SegmentInfo, &bit_rate_effective);

        char temp[300] = {0};
        strcpy(temp, TSEP);
        snprintf(temp, sizeof(temp), "%s %7u " TSEP, temp, bit_rate_hz);
        snprintf(temp, sizeof(temp), "%s %7u " TSEP, temp, bit_rate_effective);
        snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, SegmentInfo.prescaler);
        snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, SegmentInfo.synchronization);
        snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, SegmentInfo.propagation);
        snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, SegmentInfo.phase_1);
        snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, SegmentInfo.phase_2);
        snprintf(temp, sizeof(temp), "%s %5.2f " TSEP, temp, sample_point);
        snprintf(temp, sizeof(temp), "%s %4u " TSEP, temp, bit_duration_tq);
        cli_printf("%s" CRLF, temp);
        res = true;
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
