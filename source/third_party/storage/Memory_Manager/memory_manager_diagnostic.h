#ifndef MEMORY_MANAGER_DIAGNOSTIC_H
#define MEMORY_MANAGER_DIAGNOSTIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "general_types.h"
#include "memory_manager_types.h"

const MEMORY_MANAGER_BANK_INFO* MEMORY_MANAGER_GetBankInfo(U8 deviceNumber) ;

const char* MemManPermissionsToStr(U8 permissions);
STD_RESULT MEMORY_MANAGER_Diag(U8 memoryBankCnt);
STD_RESULT MEMORY_MANAGER_BankDiag(void);

#ifdef __cplusplus
}
#endif

#endif /* MEMORY_MANAGER_DIAGNOSTIC_H */



