#ifndef MAILBOX_COMMON_TYPES_H
#define MAILBOX_COMMON_TYPES_H

#include "std_includes.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "mailbox_const.h"
#include "fifo_char_types.h"

#ifdef HAS_MAILBOX_CUSTOM
#include "mailbox_custom_types.h"
#else
#define MAILBOX_CUSTOM_VARIABLES
#endif

#ifndef HAS_MAILBOX
#error "+HAS_MAILBOX"
#endif /*HAS_MAILBOX*/

#define MAILBOX_COMMON_VARIABLES                                            \
    uint8_t num;                                                            \
    uint8_t* TxData;                                                        \
    uint32_t tx_data_size;                                                  \
    uint8_t* RxData;                                                        \
    uint32_t rx_data_size;                                                  \
    uint32_t channel;                                                       \
    bool interrupt_on;                                                      \
    bool auto_release;                                                      \
    char* name;                                                             \
    bool valid;



#define MAILBOX_CHANNEL_COMMON_VARIABLES                                    \
    uint8_t num;                                                            \
    uint32_t channel;                                                       \
    char* name;                                                             \
    bool valid;

typedef struct {
    MAILBOX_COMMON_VARIABLES
    /* irq_priority*/
} MailBoxConfig_t;


typedef struct {
    MAILBOX_CHANNEL_COMMON_VARIABLES
} MailBoxChannelConfig_t;


#define MAILBOX_ISR_COMMON_IT_VARIABLES          \
        volatile bool it_done;                   \
        volatile uint32_t it_cnt;

#define MAILBOX_ISR_COMMON_RX_VARIABLES          \
        volatile bool rx_done;                   \
        volatile uint32_t rx_cnt;

#define MAILBOX_ISR_COMMON_VARIABLES             \
        MAILBOX_ISR_COMMON_RX_VARIABLES          \
        MAILBOX_ISR_COMMON_IT_VARIABLES          \
        volatile bool done_done;                 \
        volatile uint32_t done_cnt;              \
        volatile uint8_t it_core_num;            \
        volatile uint32_t done_flags;

typedef struct {
    MAILBOX_COMMON_VARIABLES
    MAILBOX_ISR_COMMON_VARIABLES
    MAILBOX_CUSTOM_VARIABLES
    bool init;
    bool new_data;
    FifoChar_t RxFifo;
    uint32_t spin;
    uint32_t wait_cnt;
} MailBoxHandle_t;

typedef struct {
    MAILBOX_CHANNEL_COMMON_VARIABLES
    bool init;
} MailBoxChannelHandle_t;


#ifdef __cplusplus
}
#endif

#endif /* MAILBOX_COMMON_TYPES_H */
