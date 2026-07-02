#ifndef CAN_REGISTERS_DIAG_H
#define CAN_REGISTERS_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_types.h"
#include "mcal_types.h"

extern const Reg32_t CanReg[];

bool can_diag_low_level(uint8_t num, char* const keyword);
bool can_raw_reg_diag(uint8_t num);

uint32_t can_reg_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* CAN_REGISTERS_DIAG_H */


