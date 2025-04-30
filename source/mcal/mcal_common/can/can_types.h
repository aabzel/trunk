#ifndef CAN_MCAL_TYPES_H
#define CAN_MCAL_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "can_const.h"
#include "can_custom_types.h"
#include "sys_config.h"

typedef union{
    uint32_t standard;   /* specifies the 11 bits standard identifier. value between 0 to 0x7FF. */
    uint32_t extended;                  /* specifies the 29 bits extended identifier. value between 0 to 0x1FFFFFFF. */
}CanId_t;

typedef struct{
    CanId_t identifier;
    CanIdentifier_t id_type;           /* specifies identifier type for the transmit message.*/
    CanTxFrame_t frame_type;       /* specifies frame type for the transmit message.*/
    uint8_t dlc;                           /* Data Length Code. specifies frame data length that will be transmitted.
                                              this parameter can be a value between 0 to 8 */
    uint8_t data[8];                       /* contains the transmit data. it ranges from 0 to 0xFF. */
} CanMessage_t;

#define CAN_COMMON_VARIABLES     \
    bool valid;                  \
    uint8_t num;                 \
    uint32_t bit_rate;           \
    CanMode_t mode;              \
    bool re_tx;

typedef struct {
    CAN_COMMON_VARIABLES
    char *name;
}CanConfig_t;

typedef struct {
    CAN_COMMON_VARIABLES
    volatile uint32_t rx_bytes;  // Total rx byte
    volatile uint32_t tx_bytes;  // Total tx byte
    volatile bool unproc_rx_message;
    volatile bool tx_done;
    volatile bool rx_done;
    volatile uint32_t isr_cnt;
    volatile uint32_t err_code;
    volatile uint32_t isr_rx_cnt;
    volatile uint32_t isr_tx_cnt;
    volatile uint32_t isr_err_cnt;
    CanMessage_t RxMessage;
    bool init_done;
    CAN_CUSTOM_VARIABLES
} CanHandle_t;

#endif /* CAN_MCAL_TYPES_H */
