#ifndef CAN_REGISTERS_DIAG_H
#define CAN_REGISTERS_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_types.h"
#include "mcal_types.h"

extern const Reg32_t CanReg[];

bool CanDiagRegEPRS(const uint32_t dword);
bool CanDiagRegCBT(const uint32_t dword);
bool CanDiagRegCTRL1(const uint32_t dword);
bool CanDiagRegCTRL2(const uint32_t dword);
bool CanDiagRegECR(const uint32_t dword);
bool CanDiagRegENCBT(const uint32_t dword);
bool CanDiagRegERFCR(const uint32_t dword);
bool CanDiagRegERFSR(const uint32_t dword);
bool CanDiagRegESR1(const uint32_t dword);
bool CanDiagRegFDCTRL(const uint32_t dword);
bool CanDiagRegIMASK1(const uint32_t dword);
bool CanDiagRegMCR( const uint32_t dword);
bool CanDiagRegIFLAG1(const uint32_t dword);
bool CanDiagRegTIMER(const uint32_t dword);
bool can_diag_low_level(uint8_t num, char* const keyword);
bool can_raw_reg_diag(uint8_t num);

uint32_t can_reg_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* CAN_REGISTERS_DIAG_H */


