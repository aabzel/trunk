#ifndef CAN_CUSTOM_DIAG_H
#define CAN_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_types.h"
#include "mcal_types.h"

extern const Reg32_t CanReg[];


uint32_t can_reg_cnt(void);
bool can_diag_low_level(uint8_t num, char* const keyword);
bool can_diag_mail_box(uint8_t num, char* key_word1, char* key_word2);
bool can_diag_wakeup_message_buffers(uint8_t num);
bool CanDiagRegCAN_FDCTRL(uint8_t num, const CAN_Type* const CANx);
bool CanDiagRegCBT(uint8_t num, CAN_Type* const CANx);
bool CanDiagRegCTRL1(uint8_t num, CAN_Type* const CANx);
bool can_diag_ram(uint8_t num);
bool can_raw_reg_diag(uint8_t num);
const char* ESR1ToStr(uint32_t error_status);

const char* CanMessageBufferToStr(const  CanMessageBufferLayOut_t* const LayOut);
const char* FlexCanMessageToStr(const flexcan_msgbuff_t* const MsgBuff);
const char* FlaxCanBitRateStr(const flexcan_time_segment_t* const bitrate);

#ifdef __cplusplus
}
#endif

#endif /* CAN_CUSTOM_DIAG_H */


