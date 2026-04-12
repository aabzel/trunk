#ifndef IR_RECEIVER_DIAG_H
#define IR_RECEIVER_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "ir_receiver_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /**/

#ifndef HAS_IR_RECEIVER
#error "+HAS_IR_RECEIVER"
#endif /**/

#ifndef HAS_IR_RECEIVER_DIAG
#error "+HAS_IR_RECEIVER_DIAG"
#endif /**/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /**/

bool ir_receiver_diag(void);
const char* IrReceiverConfigToStr(const IrReceiverConfig_t* const Config);
const char* IrReceiverNodeToStr(const IrReceiverHandle_t* const Node);
bool IrReceiverFrameRisingDiag(const IrReceiverHandle_t* const Node);
bool IrReceiverFrameDiag(const IrReceiverHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* IR_RECEIVER_DIAG_H  */
