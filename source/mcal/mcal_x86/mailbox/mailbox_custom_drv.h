#ifndef MAILBOX_CUSTOM_HAL_H
#define MAILBOX_CUSTOM_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "microcontroller_const.h"
#include "std_includes.h"
#ifdef HAS_MAILBOX_DIAG
#include "mailbox_custom_diag.h"
#endif

#include "module_driver_mb.h"

bool MailBoxStatusTypeToRes(const MB_StatusType ret) ;
bool mailbox_done_channel(uint8_t num, uint32_t channel, uint8_t target_core_index);

#ifdef __cplusplus
}
#endif

#endif /* MAILBOX_CUSTOM_HAL_H  */
