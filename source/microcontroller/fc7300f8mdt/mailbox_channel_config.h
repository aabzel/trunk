#ifndef MAILBOX_CHANNEL_CONFIG_H
#define MAILBOX_CHANNEL_CONFIG_H

#include "mailbox_types.h"
#include "std_includes.h"

extern const MailBoxChannelConfig_t MailBoxChannelConfig[];
extern MailBoxChannelHandle_t MailBoxChannelInstance[];

uint32_t mailbox_channel_get_cnt(void);

#endif /*MAILBOX_CHANNEL_CONFIG_H*/
