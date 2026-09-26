#ifndef MAILBOX_CUSTOM_ISR_H
#define MAILBOX_CUSTOM_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "module_driver_mb.h"

bool CoreX_MB_IRQHandler(uint8_t num, uint8_t  core_num);
bool MailBoxIRQHandler(uint8_t num);
void MailBoxDoneCallBack(MB_HandleType *pHandle, uint32_t channel);
void MailBoxRequestCallback(MB_HandleType *pHandle, MB_ReceiveType *RxNode);

#ifdef __cplusplus
}
#endif

#endif /* MAILBOX_CUSTOM_ISR_H  */
