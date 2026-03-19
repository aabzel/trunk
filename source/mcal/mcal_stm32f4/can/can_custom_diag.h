#ifndef CAN_CUSTOM_DIAG_H
#define CAN_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_types.h"
#include "mcal_types.h"

extern const Reg32_t CanReg[];

const char* CanFilterScaleToStr(const CanFilterScale_t scale);
const char* CanLastErrorCodeToStr (const CanLastErrorCode_t lec);
const char* CanFilterModeToStr(const CanFilterMode_t mode);
const char* CanStmModeToStr(const CanStmMode_t mode);
const char* HalCanErrorToStr(const uint32_t err);

bool CanDiagRegBTR(const uint32_t dword);
bool CanDiagRegFA1R(const uint32_t dword);
bool CanDiagRegIER(const uint32_t dword);
bool can_diag_filters(const uint32_t num);
bool can_diag_custom(void);
bool can_diag_tx_mailbox(void);
bool can_diag_low_level(uint8_t num, char* const keyword);
bool can_diag_ram(uint8_t num);
bool can_raw_reg_diag(uint8_t num);
uint32_t can_reg_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* CAN_CUSTOM_DIAG_H */


