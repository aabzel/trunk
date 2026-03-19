#ifndef TRNG_DIAG_H
#define TRNG_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "trng_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_TRNG
#error "+HAS_TRNG"
#endif

#ifndef HAS_TRNG_DIAG
#error "+HAS_TRNG_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool trng_diag(void);
bool trng_diag_one(uint8_t num);
const char* tRngConfigToStr(const tRngConfig_t* const Config);
const char* tRngNodeToStr(const tRngHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* TRNG_DIAG_H  */
