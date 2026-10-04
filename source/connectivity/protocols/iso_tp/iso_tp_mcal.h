#ifndef ISO_TP_PROTOCOL_H
#define ISO_TP_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

#include "std_includes.h"
#include "iso_tp_config.h"
#include "iso_tp_types.h"
#include "system.h"

#ifdef HAS_ISO_TP_CUSTOM
#include "iso_tp_custom.h"
#endif

#ifdef HAS_CAN
#include "can_types.h"
#endif

#ifdef HAS_ISO_TP_DIAG
#include "iso_tp_diag.h"
#endif


/* API */
IsoTpHandle_t* IsoTpGetNode(uint8_t num);
IsoTpHandle_t* IsoTpIfToNode(InterfaceType_t interface_if);
const IsoTpConfig_t* IsoTpGetConfig(uint8_t num);

bool iso_tp_is_valid_config(const IsoTpConfig_t* const Config);

bool iso_tp_init_common(IsoTpHandle_t* Node, const IsoTpConfig_t* Config);
bool iso_tp_init_custom(void);
bool iso_tp_init_one(uint8_t num);
bool iso_tp_mcal_init(void);

bool iso_tp_tx_proc(void);
bool iso_tp_proc(void);
bool iso_tp_proc_rx(uint8_t num, uint16_t feame_id, IsoTpFrame_t* const RxFrame);
bool iso_tp_proc_one(uint8_t num);
bool iso_tp_tx_proc_one(uint8_t num);

/* Getters */
uint16_t iso_tp_rx_size_get(uint8_t num);
bool iso_tp_is_valid_id(const uint32_t id);
bool iso_tp_is_my_id(uint32_t id, IsoTpHandle_t* Node);
bool iso_tp_is_idle(uint8_t num);
bool iso_tp_is_valid_frame(const CanMessage_t* const RxMessage);
bool iso_tp_is_valid_separation_time_code(const uint8_t sep_time);
bool iso_tp_check(void);
int8_t iso_tp_can_num_to_iso_tp_num(uint8_t can_num);
float iso_tp_separation_time_code_to_seconds(const uint8_t sep_time);
float iso_tp_separation_time_get(uint8_t num);
uint8_t separation_time_s_to_sep_time_code(float separation_time_s);
uint8_t iso_tp_my_id_get(uint8_t num);
uint8_t* iso_tp_rx_data_get(uint8_t num, uint16_t* const size);
IsoTpState_t iso_tp_state_get(uint8_t num);

/* setters */
void iso_tp1_putc(void* stream_ptr, char ch);
void iso_tp1_puts(void* stream_ptr, const char* str, int32_t len);
bool iso_tp1_writer_transmit(void* base);

void iso_tp2_putc(void* stream_ptr, char ch);
void iso_tp2_puts(void* stream_ptr, const char* str, int32_t len);
bool iso_tp2_writer_transmit(void* base);

bool iso_tp_writer(const uint8_t num);
#ifdef HAS_CAN
bool iso_tp_rx_message(uint8_t num, const CanMessage_t* const RxMessage);
bool iso_tp_rx_message_naiv(uint8_t num, const CanMessage_t* const RxMessage);
#endif
uint32_t iso_tp_compose_normal_fixed_addr(const uint8_t source_address, const uint8_t target_address);
bool iso_tp_my_id_set(uint8_t num, uint8_t my_id);
bool iso_tp_busy_set(uint8_t num, bool on_off);
bool iso_tp_reset_ll(IsoTpHandle_t* Node);
bool iso_tp_if_sent_ll(IsoTpHandle_t* Node);
bool iso_tp_send_naiv(uint8_t num, uint8_t target_address, const uint8_t* const tx_data, const uint32_t size) ;
bool iso_tp_send(uint8_t num, uint8_t target_address, const uint8_t* const data, uint32_t size) ;

#ifdef __cplusplus
}
#endif

#endif /* ISO_TP_PROTOCOL_H */
