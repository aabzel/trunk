#ifndef ACC_DIAG_H
#define ACC_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "acc_types.h"
#include "diag_dep.h"

#ifndef HAS_ACC
#error "+HAS_ACC"
#endif /*HAS_ACC*/

#ifndef HAS_ACC_DIAG
#error "+HAS_ACC_DIAG"
#endif /*HAS_DIAG_ACC*/

bool acc_diag(void);
const char* AccConfigToStr(const AccConfig_t* const Config);
const char* AccNodeToStr(const AccHandle_t* const Node);
bool acc_raw_reg_diag(uint8_t num) ;

#ifdef __cplusplus
}
#endif

#endif /* ACC_DIAG_H  */
