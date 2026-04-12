#ifndef SW_SD_CARD_DIAG_H
#define SW_SD_CARD_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "sw_sd_card_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_SW_SD_CARD
#error "+HAS_SW_SD_CARD"
#endif /*HAS_SW_SD_CARD*/

#ifndef HAS_SW_SD_CARD_DIAG
#error "+HAS_SW_SD_CARD_DIAG"
#endif /*HAS_DIAG_SW_SD_CARD*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

bool sw_sd_card_diag(void);
const char* SwSdCardConfigToStr(const SwSdCardConfig_t* const Config);
const char* SwSdCardNodeToStr(const SwSdCardHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* SW_SD_CARD_DIAG_H  */
