#ifndef CAN_RX_HIST_MCAL_H
#define CAN_RX_HIST_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_rx_hist_config.h"
#include "can_rx_hist_types.h"
#ifdef HAS_CAN_RX_HIST_DIAG
#include "can_rx_hist_diag.h"
#endif

/* API */
CanRxHistHandle_t* CanRxHistGetNode(uint8_t num);
CanRxHistHandle_t* CanRxHistCanNumToNode(const uint8_t can_num);

const CanRxHistConfig_t* CanRxHistGetConfig(uint8_t num);
bool CanRxHistIsValidConfig(const CanRxHistConfig_t* const Config);

#ifdef HAS_CAN_RX_HIST_CUSTOM
const CanRxHistInfo_t* CanRxHistGetInfo(uint8_t num);
#endif

bool can_rx_hist_mcal_init(void);
bool can_rx_hist_init_custom(void);
bool can_rx_hist_init_common(const CanRxHistConfig_t* const Config, CanRxHistHandle_t* const Node);
bool can_rx_hist_init_node(CanRxHistHandle_t* const Node);
bool can_rx_hist_init_one(uint8_t num);

bool can_rx_hist_proc_one(uint8_t num);
bool can_rx_hist_proc(void);

/*setters*/
bool can_rx_hist_add_message(const uint8_t can_num, const CanMessage_t* const Message);

/*getters*/

#ifdef __cplusplus
}
#endif

#endif /* CAN_RX_HIST_MCAL_H */
