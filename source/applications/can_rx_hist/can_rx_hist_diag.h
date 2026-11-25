#ifndef CAN_RX_HIST_DIAG_H
#define CAN_RX_HIST_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_rx_hist_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_CAN_RX_HIST
#error "+HAS_CAN_RX_HIST"
#endif

#ifndef HAS_CAN_RX_HIST_DIAG
#error "+HAS_CAN_RX_HIST_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool can_rx_hist_diag(void);
bool can_rx_hist_diag_one(uint8_t num);
const char* CanRxHistConfigToStr(const CanRxHistConfig_t* const Config);
const char* CanRxHistNodeToStr(const CanRxHistHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* CAN_RX_HIST_DIAG_H  */
