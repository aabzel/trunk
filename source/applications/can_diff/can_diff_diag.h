#ifndef CAN_DIFF_DIAG_H
#define CAN_DIFF_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_diff_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_CAN_DIFF
#error "+HAS_CAN_DIFF"
#endif

#ifndef HAS_CAN_DIFF_DIAG
#error "+HAS_CAN_DIFF_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool can_diff_diag(void);
bool can_diff_diag_one(uint8_t num);
const char* CanDiffConfigToStr(const CanDiffConfig_t* const Config);
const char* CanDiffNodeToStr(const CanDiffHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* CAN_DIFF_DIAG_H  */
