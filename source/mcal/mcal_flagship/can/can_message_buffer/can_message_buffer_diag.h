#ifndef CAN_MESSAGE_BUFFER_DIAG_H
#define CAN_MESSAGE_BUFFER_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_types.h"
#include "mcal_types.h"

#include "can_message_buffer_types.h"


bool can_diag_mail_box(const uint8_t num, char* key_word1, char* key_word2);
bool can_diag_ram(const uint8_t num);
bool can_diag_wakeup_message_buffers(const uint8_t num);

const char* FlexCanMbSettingToStr(const FLEXCAN_MbSettingType* const MbSetting);
const char* CanTxMessageToStr(const FLEXCAN_TxMsgType* const TxMsg);

#if 0
const char* CanMessageBufferToStr(const  CanMessageBufferLayOut_t* const LayOut);
#endif

#ifdef __cplusplus
}
#endif

#endif /* CAN_MESSAGE_BUFFER_DIAG_H */


