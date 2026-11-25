#ifndef CAN_RX_HIST_CONFIG_H
#define CAN_RX_HIST_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_rx_hist_types.h"
#include "can_rx_hist_dep.h"

extern const CanRxHistConfig_t CanRxHistConfig[];
extern CanRxHistHandle_t CanRxHistInstance[];

uint32_t can_rx_hist_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* CAN_RX_HIST_CONFIG_H */
