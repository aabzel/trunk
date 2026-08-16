#ifndef BACK_COUNT_DIAG_H
#define BACK_COUNT_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "back_count_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_BACK_COUNT
#error "+HAS_BACK_COUNT"
#endif

#ifndef HAS_BACK_COUNT_DIAG
#error "+HAS_BACK_COUNT_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool back_count_diag(void);
bool back_count_diag_one(uint8_t num);
bool back_count_raw_reg_diag(uint8_t num);
const char* BackCountConfigToStr(const BackCountConfig_t* const Config);
const char* BackCountNodeToStr(const BackCountHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* BACK_COUNT_DIAG_H  */
