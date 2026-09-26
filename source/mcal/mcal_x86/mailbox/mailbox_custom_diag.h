#ifndef MAILBOX_CUSTOM_DIAG_H
#define MAILBOX_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "mailbox_custom_types.h"
#include "module_driver_mb.h"

char* MailBoxStatusTypeToStr(const MB_StatusType code);
const char* MailBoxInitTypeToStr(const MB_InitType* const Init) ;
const char* MailBoxReceiveTypeToStr(const MB_ReceiveType* const Receive);
uint32_t mailbox_reg_cnt(void);
bool MailBoxDiagHandle(const MB_HandleType* const Handle);
bool mailbox_diag_custon_one(const uint8_t num);
bool mailbox_raw_reg_diag(uint8_t num, uint32_t channel);
bool mailbox_diag_low_level(uint8_t num, const char* const keyword);
bool MailBoxStatusTypeDiagPrefix(const MB_StatusType ret, const char * const prefix) ;
bool MailBoxStatusTypeDiag(const MB_StatusType ret);
bool MailBoxDiagRequest(const MB_ReceiveType* const Receive) ;
bool mailbox_diag_channel(uint8_t num);
bool mailbox_diag_channel_done(uint8_t num);
bool mailbox_diag_channel_req(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* MAILBOX_CUSTOM_DIAG_H */
