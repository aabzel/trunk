#ifndef CAN_CUSTOM_DIAG_H
#define CAN_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_types.h"

//extern const Reg32_t CanReg[];

bool can_raw_reg_diag(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* CAN_CUSTOM_DIAG_H */


