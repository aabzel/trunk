#ifndef CAN_DIAG_H
#define CAN_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "can_types.h"

const char* CanIdTypeToStr(CanIdentifier_t id_type);
const char* CanFrameTypeToStr(CanTxFrame_t frame_type);
const char* CanMessage2Str(const CanMessage_t* const Message);
bool can_diag(void );

#ifdef __cplusplus
}
#endif

#endif /* CAN_DIAG_H */
