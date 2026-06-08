#ifndef IR_RECEIVER_MCAL_H
#define IR_RECEIVER_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "ir_receiver_config.h"
#include "ir_receiver_types.h"

#ifdef HAS_IR_RECEIVER_DIAG
#include "ir_receiver_diag.h"
#endif

/* API */
const IrReceiverConfig_t* IrReceiverGetConfig(uint8_t num);
IrReceiverHandle_t* IrReceiverGetNode(uint8_t num);
bool IrReceiverIsValidConfig(const IrReceiverConfig_t* const Config);

bool ir_receiver_mcal_init(void);
bool ir_receiver_init_custom(void);
bool ir_receiver_init_one(uint8_t num);
bool ir_receiver_init_common(const IrReceiverConfig_t* const Config,
                             IrReceiverHandle_t* const Node);

bool ir_receiver_proc_one(uint8_t num);
bool ir_receiver_proc(void);

/*setters*/
bool ir_receiver_proc_event(const uint8_t num, const PinIntEdge_t event );


#ifdef __cplusplus
}
#endif

#endif /* IR_RECEIVER_MCAL_H */
