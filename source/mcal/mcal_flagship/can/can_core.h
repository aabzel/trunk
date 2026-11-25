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

#ifdef HAS_CAN_FD
#include "can_fd_mcal.h"
#endif


#ifdef HAS_CAN_CUSTOM
const CanInfo_t* CanGetInfo(uint8_t num);
#endif

bool can_is_message_valid(const CanMessage_t* const Message);

/* API */
bool CanIsValidInfo(const CanInfo_t* const Info);
bool can_segment_info_calc(uint32_t bus_freq_hz, uint32_t baud_rate_hz, CanSegmentInfo_t* const SegmentInfo);
bool can_check(void);

bool can_is_valid_segment( const CanSegmentInfo_t* const Segment);
uint32_t can_time_seg_to_bit_rate(const uint32_t clk_freq_hz, const CanSegmentInfo_t* const Segment);
uint32_t can_segment_to_main_pre_scaler(const CanSegmentInfo_t* const Segment);
bool can_segment_info_calc_custom(uint32_t bus_freq_hz, uint32_t baud_rate_hz, CanSegmentInfo_t* const FoundSegment);

/* setter */
bool can_reset_error_counters(const uint8_t num);
bool can_clock_src_set(const uint8_t num, const CanClockSource_t clock_source );
bool can_interrupt_ctrl(uint8_t num, bool on_off);
bool can_mcal_transmit_buff(uint8_t num, uint32_t id, const uint8_t* const data, uint8_t size);
bool can_mcal_baudrate_set_v1(uint8_t num, uint32_t baud_rate_hz) ;
bool can_mcal_baudrate_set_v0(uint8_t num, uint32_t baud_rate_hz);
bool can_mcal_baudrate_set(uint8_t num, uint32_t baudrate);
bool can_mesg_buff_rx(uint8_t can_num, uint8_t mb_idx, uint32_t can_id) ;
bool can_clock_src_set_ll(uint8_t num, const Can_CTRL1_CLKSRC_t clk_src);

/* getter */
bool can_freeze_wait(volatile FLEXCAN_Type* CANx, uint32_t timeout_ms);
bool can_freeze_get(uint8_t num);
bool can_is_allowed(uint8_t num) ;
bool can_is_init(uint8_t num) ;
bool can_mcal_baudrate_get_v2(uint8_t num, uint32_t* const bit_rate);
bool can_mcal_baudrate_get(uint8_t num, uint32_t * const bit_rate);
bool can_module_get(uint8_t num);
bool can_rec_get(uint8_t num, uint32_t* const rec);
bool can_segments_get_v2(uint8_t num, CanSegmentInfo_t* const SegmentInfo);
bool can_segments_get(uint8_t num, CanSegmentInfo_t* const SegmentInfo);
bool can_tec_get(uint8_t num, uint32_t* const tec);
//bool CanBitRateToSegment(uint32_t clk_freq_hz, uint32_t bit_rate, FLEXCAN_BaudRegType* const TimeSeg);
CanInfo_t* CanInterfaceToInfo(const InterfaceType_t interface_if);
CanMacMode_t can_get_mac_mode(const uint8_t num) ;
Can_CTRL1_CLKSRC_t can_clock_src_get(uint8_t num);
Can_CTRL1_CLKSRC_t CanClockSourceToClkSrc(const CanClockSource_t clock_source) ;
CanClockSource_t can_get_clk_src(const uint8_t num);
CanIdentifier_t can_id_val_to_id_type(const uint32_t id_val);
float can_time_quanta_get(uint8_t num) ;
StorageId_t can_nvran_id_get(const uint8_t num);
uint32_t can_base_clock_get(uint8_t num) ;
uint8_t can_id_type_to_bit_len(const CanIdentifier_t id_type);
uint8_t can_interface_to_can_num(const InterfaceType_t interface_if) ;
uint8_t can_fd_dlc_to_size(const uint8_t dlc);
uint8_t CanDlcToSize(const CanDlc_t dlc) ;


#endif /* CAN_CORE_H  */
