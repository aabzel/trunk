#ifndef IR_RECEIVER_CONFIG_H
#define IR_RECEIVER_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "ir_receiver_types.h"
#include "ir_receiver_dep.h"

extern const IrReceiverConfig_t IrReceiverConfig[];
extern IrReceiverHandle_t IrReceiverInstance[];

uint32_t ir_receiver_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* IR_RECEIVER_CONFIG_H */
