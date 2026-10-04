#ifndef CAN_MAILBOX_CONFIG_H
#define CAN_MAILBOX_CONFIG_H

#include "can_types.h"


extern const CanMessageBufferConfig_t CanMessageBufferConfig[];
//extern CanMessageBufferHandle_t CanMessageBufferInstance[];

uint32_t can_mailbox_get_cnt(void);


#endif /* CAN_MAILBOX_CONFIG_H  */
