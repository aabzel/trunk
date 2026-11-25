#ifndef MAILBOX_CONFIG_H
#define MAILBOX_CONFIG_H

#include "mailbox_types.h"
#include "std_includes.h"

extern const MailBoxConfig_t MailBoxConfig[];
extern MailBoxHandle_t MailBoxInstance[];

uint32_t mailbox_get_cnt(void);

#endif /*MAILBOX_CONFIG_H*/
