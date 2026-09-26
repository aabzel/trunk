#ifndef SEGGER_RTT_DIAG_H
#define SEGGER_RTT_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "segger_rtt_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_SEGGER_RTT
#error "+HAS_SEGGER_RTT"
#endif

#ifndef HAS_SEGGER_RTT_DIAG
#error "+HAS_SEGGER_RTT_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool segger_rtt_diag(void);
bool segger_rtt_diag_one(uint8_t num);
const char* SeggerRttConfigToStr(const SeggerRttConfig_t* const Config);
const char* SeggerRttNodeToStr(const SeggerRttHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* SEGGER_RTT_DIAG_H  */
