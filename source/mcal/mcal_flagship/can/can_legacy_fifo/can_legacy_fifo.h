#ifndef CAN_LEGACY_FIFO_H
#define CAN_LEGACY_FIFO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "module_driver_flexcan.h"
#include "can_types.h"

bool can_is_mode_legacy_fifo(const uint8_t num);
bool can_init_rx_fifo_legacy_default(FLEXCAN_InitType* const pInit);
bool can_config_legacy_fifo_init(const CanConfig_t* const Config, FLEXCAN_InitType* const Init);
bool can_legacy_fifo_id_check(const uint8_t num, const  uint32_t can_id);

#ifdef __cplusplus
}
#endif

#endif /* CAN_LEGACY_FIFO_H  */




