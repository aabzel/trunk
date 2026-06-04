#ifndef MX25L6433F_DIAG_H
#define MX25L6433F_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "mx25l6433f_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_MX25L6433F_DIAG
#error "+HAS_MX25L6433F_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool mx25l6433f_diag(void);
bool mx25l6433f_diag_one(uint8_t num);
const char* Mx25l6433fConfigToStr(const Mx25l6433fConfig_t* const Config);
const char* Mx25l6433fNodeToStr(const Mx25l6433fHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* MX25L6433F_DIAG_H  */
