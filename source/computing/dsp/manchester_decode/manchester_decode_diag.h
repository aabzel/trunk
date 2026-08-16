#ifndef MANCHESTER_DECODE_DIAG_H
#define MANCHESTER_DECODE_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "manchester_decode_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_MANCHESTER_DECODE
#error "+HAS_MANCHESTER_DECODE"
#endif

#ifndef HAS_MANCHESTER_DECODE_DIAG
#error "+HAS_MANCHESTER_DECODE_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool manchester_decode_diag(void);
bool manchester_decode_diag_one(uint8_t num);
const char* ManchesterDecodeConfigToStr(const ManchesterDecodeConfig_t* const Config);
const char* ManchesterDecodeActionToStr(const ManchesterDecodeAction_t action);
const char* ManchesterDecodeNodeToStr(const ManchesterDecodeHandle_t* const Node);
const char* ManchesterDecodeStateToStr(const ManchesterDecodeState_t state);
const char* ManchesterDecodeActionToStr(const ManchesterDecodeAction_t action);

#ifdef __cplusplus
}
#endif

#endif /* MANCHESTER_DECODE_DIAG_H  */
