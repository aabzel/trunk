#ifndef EEPROM_EMULATION_DIAG_H
#define EEPROM_EMULATION_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "general_types.h"

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

#ifndef HAS_EEPROM_EMULATION_DIAGNOSTIC
#error "+HAS_EEPROM_EMULATION_DIAG"
#endif

#ifndef HAS_EEPROM_EMULATION
#error "+HAS_EEPROM_EMULATION"
#endif

const char* MemoryStatusToStr(U32 code) ;
const char* MemJobResToStr(U8 code);

STD_RESULT EEPROM_EMULATION_Diag(void);
STD_RESULT EEPROM_EMULATION_Dump(U8 bank_num);

#ifdef __cplusplus
}
#endif

#endif /* EEPROM_EMULATION_DIAG_H */
