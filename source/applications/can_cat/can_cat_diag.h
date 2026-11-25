#ifndef CAN_CAT_DIAG_H
#define CAN_CAT_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_cat_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_CAN_CAT
#error "+HAS_CAN_CAT"
#endif /*HAS_CAN_CAT*/

#ifndef HAS_CAN_CAT_DIAG
#error "+HAS_CAN_CAT_DIAG"
#endif /*HAS_DIAG_CAN_CAT*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

bool can_cat_diag(void);
const char* CanCatConfigToStr(const CanCatConfig_t* const Config);
const char* CanCatNodeToStr(const CanCatHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* CAN_CAT_DIAG_H  */
