#ifndef CAN_MCAL_H
#define CAN_MCAL_H

/*
 https://en.wikipedia.org/wiki/CAN_bus
 */

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

extern const uint32_t CanTypicalBitRates[];

CanHandle_t* CanGetNode(uint8_t num);
const CanConfig_t* CanGetConfig(uint8_t num);

#ifdef HAS_CAN_CUSTOM
const CanInfo_t* CanGetInfo(uint8_t num);
#endif

bool can_is_message_valid(const CanMessage_t* const Message);

/* API */
bool can_mcal_init(void);
bool can_init_one(uint8_t num);
bool can_init_custom(void);
bool can_init_common(const CanConfig_t * const Config, CanHandle_t * const Node);
bool can_init_node(CanHandle_t * const Node);
bool CanIsValidConfig(const CanConfig_t* const Config);

bool can_segment_info_calc(uint32_t bus_freq_hz, uint32_t baud_rate_hz, CanSegmentInfo_t* const SegmentInfo);
bool can_check(void);
bool can_wait_tx_done_ll(CanHandle_t* const Node);

bool can_is_valid_segment( const CanSegmentInfo_t* const Segment);
uint32_t can_time_seg_to_bit_rate(const uint32_t clk_freq_hz, const CanSegmentInfo_t* const Segment);
uint32_t can_segment_to_main_pre_scaler(const CanSegmentInfo_t* const Segment);

/* proc */
bool can_health_monitor_proc(void);
bool can_health_monitor_proc_one(uint8_t num);

bool can_proc(void);
bool can_proc_custom(void);
bool can_proc_one(uint8_t num);

bool can_heartbeat_proc(void);
bool can_heartbeat_proc_one(uint8_t num);

/* setter */
bool can_rx_all(const uint8_t can_num);
bool can_tx_indication(CanHandle_t* const Node);
bool can_mcal_baudrate_set(const uint8_t num, const uint32_t baudrate) ;
bool can_std_send_hi_load(const uint8_t num, const uint32_t frame_cnt,uint32_t pause_ms, uint32_t id);
bool can_filter_allow_id(uint8_t num, const uint32_t id);
bool can_filter_ban_id(uint8_t num, const uint32_t id);
bool can_interrupt_ctrl(uint8_t num, bool on_off);
bool can_loopback_set(const uint8_t num, const bool on_off);
bool can_mcal_transmit_buff(uint8_t num, uint32_t id, const uint8_t* const data, uint8_t size);
bool can_mcal_transmit_message(uint8_t num, const CanMessage_t* const Message);
bool can_mesg_buff_rx(uint8_t can_num, uint8_t mb_idx, uint32_t can_id) ;
bool can_tx_done_reset(const uint8_t num);
bool can_phy_disconnect(uint8_t num);
bool can_phy_connect_ctrl(const uint8_t num, const bool on_off);
bool can_phy_connect(uint8_t num);
bool can_rx_frame_manual(const uint8_t num, const CanMessage_t* const Message);
bool can_mcal_filter_id_mask_set(const uint8_t can_num, const uint8_t filt_num, const CanIdentifier_t format,
                                 const uint32_t filt_id, const uint32_t filt_mask);
bool can_init_notivications(CanHandle_t* const Node);
bool can_init_filters(const CanConfig_t* const Config, CanHandle_t* const Node);
//bool can_config_to_init(const CanConfig_t* const Config, CAN_InitTypeDef* const Init);

/* getter */
//CanFFAxCode_t can_filter_fifo(const uint8_t num, const uint8_t filter_num);
bool can_segment_to_baudrate(uint32_t base_clock_hz, CanSegmentInfo_t* const Segment, uint32_t* const bit_rate);
bool can_filter_is_active(const uint8_t num, const uint8_t filter_num);
bool can_loopback_get(const uint8_t num, bool* const on_off);
bool can_mcal_baudrate_get(uint8_t num, uint32_t * const bit_rate);
bool can_is_my_id(const uint8_t num, const uint32_t can_id);
bool can_is_allowed(uint8_t num);
bool can_is_ext_id(const uint32_t can_id) ;
bool can_is_init(uint8_t num) ;
bool can_is_my_can(const Cans_t Cans, const uint8_t num);
bool can_is_std_id(const uint32_t can_id) ;
bool can_is_tx_done(const uint8_t num);
bool can_rec_get(uint8_t num, uint32_t* const rec);
bool can_tec_get(uint8_t num, uint32_t* const tec);
bool can_segments_get(uint8_t num, CanSegmentInfo_t* const SegmentInfo);
CanClockSource_t can_get_clk_src(const uint8_t num);
CanMacMode_t can_get_mac_mode(const uint8_t num);
CanIdentifier_t can_id_val_to_id_type(const uint32_t id_val);
InterfaceType_t can_num_to_interface(const uint8_t num);
float can_time_quanta_get(uint8_t num) ;
float can_segment_to_fetch_present(const CanSegmentInfo_t* const Info) ;
uint32_t can_get_typical_bitrate_cnt(void);
uint32_t can_base_clock_get(const uint8_t num);
uint32_t can_get_alien_rx_id(const uint8_t num);
uint32_t can_get_first_allowed_id(const uint8_t num );
uint8_t can_fd_dlc_to_size(const uint8_t dlc);
uint8_t can_id_type_to_bit_len(const CanIdentifier_t id_type);
uint32_t can_segment_to_bit_duration_tq(const CanSegmentInfo_t* const Info);
uint8_t can_interface_to_can_num(const InterfaceType_t interface_if) ;
uint8_t CanDlcToSize(const CanDlc_t dlc) ;


#endif /* CAN_MCAL_H  */
