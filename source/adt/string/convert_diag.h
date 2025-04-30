#ifndef CONVERT_DIAG_H
#define CONVERT_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "convert_types.h"

const char* SymbolToStr(char symbol);
const char* Sign2Str(int8_t sign) ;
const char* NumberParserState2Str(ParseNumberStates_t state) ;
char* NumberParserFsm2Str(const Text2NumberFsm_t * const Node);

#ifdef __cplusplus
}
#endif

#endif /* CONVERT_DIAG_H */
