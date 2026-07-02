#ifndef CAN_CORE_H
#define CAN_CORE_H

#include "can_types.h"
#include "can_config.h"

#ifdef HAS_CAN_CUSTOM
#include "can_custom.h"
#endif

#ifdef HAS_CAN_DIAG
#include "can_diag.h"
#endif

#ifdef HAS_CAN_CUSTOM
const CanInfo_t* CanGetInfo(uint8_t num);
#endif

uint32_t CanPhase1ToTimeSeg1(const uint32_t phase_1) ;
uint32_t CanLoopBackToOperatingMode(const bool on_off) ;
uint32_t CanPhase2ToTimeSeg2(const uint32_t phase_2) ;
uint32_t CanCanTxFrameToRtr(const CanTxFrame_t frame_type) ;
uint32_t CanSynchroToSyncJumpWidth(const uint32_t synchronization) ;
uint32_t can_segment_info_to_bitrate(const uint32_t base_clock_hz,
                                     const uint16_t brp,
                                     const uint8_t sjw,
                                     const uint8_t tseg1,
                                     const uint8_t tseg2);

uint32_t CanIdTypeToFrameIDE(const CanIdentifier_t id_type) ;
uint32_t CanModeToOperatingMode(const CanMode_t mode);
uint32_t CanIdTypeToFiltIDE(const CanIdentifier_t id_type);
bool can_segment_to_baudrate(uint32_t base_clock_hz, CanSegmentInfo_t* const Segment, uint32_t* const bit_rate) ;
bool can_is_message_valid(const CanMessage_t* const Message);
/* API */
bool CanIsValidInfo(const CanInfo_t* const Info);
bool can_segment_info_calc(uint32_t bus_freq_hz, uint32_t baud_rate_hz, CanSegmentInfo_t* const SegmentInfo);
bool can_check(void);

bool can_is_valid_segment( const CanSegmentInfo_t* const Segment);
uint32_t can_time_seg_to_bit_rate(const uint32_t clk_freq_hz, const CanSegmentInfo_t* const Segment);
uint32_t can_segment_to_main_pre_scaler(const CanSegmentInfo_t* const Segment);

/* setter */
bool can_priority_ctrl(uint8_t num, uint8_t preempt_priority);
bool can_mode_set(const uint8_t num, const CanStmMode_t mode);
bool can_clock_src_set(const uint8_t num, const CanClockSource_t clock_source );
bool can_clock_ctrl(uint8_t num, bool on_off);
bool can_interrupt_ctrl(uint8_t num, bool on_off);
bool can_mcal_transmit_buff(uint8_t num, uint32_t id, const uint8_t* const data, uint8_t size);
bool can_mcal_baudrate_set(uint8_t num, uint32_t baudrate);
bool can_mesg_buff_rx(uint8_t can_num, uint8_t mb_idx, uint32_t can_id) ;
bool CanCAN_BTRToSegment(CanReg_BTR_t* pBTR, CanSegmentInfo_t* const Segment) ;
bool can_segment_to_btr(const CanSegmentInfo_t *const Segment, CanReg_BTR_t *const pReg);

/* getter */
bool can_stm32_segment_info_calc(uint32_t bus_freq_hz, const uint32_t bit_rate_hz,
                                        CanSegmentInfo_t* const Segment);
bool can_mcal_baudrate_calc(const uint32_t base_clock_hz, const CanReg_BTR_t CAN_BTR, uint32_t* const bit_rate) ;
uint32_t CanMailBoxNumToCode(const uint32_t mailbox_mum);
uint32_t can_base_clock_get(const uint8_t num);
CanFFAxCode_t can_filter_fifo(const uint8_t num, const uint8_t filter_num) ;
CanFilterMode_t can_filter_mode(const uint8_t num, const uint8_t filter_num);
CanFilterScale_t can_filter_scale(const uint8_t num, const uint8_t filter_num);
CanTxFrame_t CanRTRtoFrameType(const uint32_t rtr);
CanIdentifier_t CanIDEtoIdentifierType(const uint32_t ide);


#endif /* CAN_CORE_H  */
