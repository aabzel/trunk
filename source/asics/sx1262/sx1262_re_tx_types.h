#ifndef SX1262_RETX_TYPES_H
#define SX1262_RETX_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "sx1262_re_tx_const.h"

typedef struct xReTxFsm_t {
    uint8_t retx_cnt_max;
    uint8_t retx_cnt;
    uint8_t TxFrame[SX1262_MAX_TX_FRAME_SIZE];
    uint16_t tx_frame_len;
}ReTxFsm_t;


#ifdef __cplusplus
}
#endif

#endif /* SX1262_RETX_TYPES_H */
