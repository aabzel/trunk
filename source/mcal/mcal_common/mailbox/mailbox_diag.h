#ifndef MAILBOX_DIAG_H
#define MAILBOX_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_MAILBOX
#error "+HAS_MAILBOX"
#endif /*HAS_MAILBOX*/

#include <stdint.h>

#include "mailbox_types.h"

bool mailbox_diag_one(uint32_t num);
bool mailbox_diag(void);
bool MailBoxDiagConfig(const MailBoxConfig_t* const Config);
const char* MailBoxConfigToStr(const MailBoxConfig_t* const Config);

#ifdef __cplusplus
}
#endif

#endif /* MAILBOX_DIAG_H */
