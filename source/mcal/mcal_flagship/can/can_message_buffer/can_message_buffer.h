#ifndef CAN_MESSAGE_BUFFER_H
#define CAN_MESSAGE_BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "module_driver_flexcan.h"
#include "can_message_buffer_types.h"
#include "can_message_buffer_diag.h"
#include "can_types.h"

CanMessageBufferConfig_t* CanMessageBufferConfigGet(const uint8_t num, const uint32_t can_id);
ConnectivitDir_t can_mailbox_direction_get(uint8_t num, uint8_t mailbox_num);
bool can_last_message_buffer_number_get(uint8_t num, uint8_t* const maxmb);
bool can_config_mail_box_init(const CanConfig_t* const Config, FLEXCAN_InitType* const Init);
bool can_init_mail_box_tx(const CanConfig_t *const Config, FLEXCAN_InitType *const Init);
bool can_is_mode_message_buffer(const uint8_t num);
bool can_mailbox_direction_set(uint8_t num, uint8_t mailbox_num, ConnectivitDir_t dir) ;
bool can_mailbox_interrupt_flag_clear(uint8_t num, uint8_t mailbox_num);
bool can_mailbox_interrupt_mask_set(uint8_t num, uint8_t mailbox_num, bool on_off);
bool can_mailbox_interrupt_mask_get(uint8_t num, uint8_t mailbox_num);
bool can_message_buffer_id_check(const uint8_t num, const uint32_t can_id);
bool can_message_buffer_to_mb_setting(const CanMessageBufferConfig_t* const MbConfig,
                                      FLEXCAN_MbSettingType* const MbSetting);
bool can_last_message_buffer_number_set(uint8_t num, uint8_t maxmb);
uint8_t can_message_buffer_to_size(const CanMessageBufferDataSize_t mbdsr0) ;
#ifdef __cplusplus
}
#endif

#endif /* CAN_MESSAGE_BUFFER_H  */








