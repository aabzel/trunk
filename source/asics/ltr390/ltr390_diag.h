#ifndef LTR390_DIAG_H
#define LTR390_DIAG_H

#include "std_includes.h"
#include "ltr390_types.h"

#ifndef HAS_LTR390
#error "+HAS_LTR390"
#endif

const char* Ltr390DiagToStr(Ltr390Handle_t* Node);
const char* Ltr390ConfigToStr(const Ltr390Config_t* const Config);
const char* Ltr390AlsDiagToStr(Ltr390Handle_t* Node);
const char* Ltr390UvsDiagToStr(Ltr390Handle_t* Node);
const char* SourceToStr(DataSource_t source);
const char* RegAccessToStr(RegAccess_t access);
const char* Ltr390AddrToName(uint8_t reg_addr);
bool Ltr390DiagNode( Ltr390Handle_t* Node );
bool ltr390_diag(char* key_word1, char* key_word2);
bool ltr390_diag_registers(uint8_t num, char* key_word1, char* key_word2);
bool ltr390_diag_registers_undoc(uint8_t num);

#endif /* LTR390_DIAG_H  */
