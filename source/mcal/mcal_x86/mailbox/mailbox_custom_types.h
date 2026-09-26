#ifndef MAILBOX_CUSTOM_TYPES_H
#define MAILBOX_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mailbox_custom_const.h"
#include "microcontroller_types.h"
#include "module_driver_mb.h"

#define MAILBOX_CUSTOM_VARIABLES              \
    volatile MB_ReceiveType Rx;               \
    volatile MB_HandleType Handle;

typedef struct {
    uint8_t num;
    bool valid;
    uint32_t * MAILBOXx;
    IRQn_Type irq_n;
}MailBoxInfo_t;





#ifdef __cplusplus
}
#endif

#endif /* MAILBOX_CUSTOM_TYPES_H  */
