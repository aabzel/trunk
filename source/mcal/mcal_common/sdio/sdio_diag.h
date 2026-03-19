#ifndef SDIO_DIAG_H
#define SDIO_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "sdio_types.h"
#include "sdio_custom_diag.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /**/

#ifndef HAS_SDIO
#error "+HAS_SDIO"
#endif /**/

#ifndef HAS_SDIO_DIAG
#error "+HAS_SDIO_DIAG"
#endif /**/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /**/

const char* SdioConfigToStr(const SdioConfig_t* const Config);
const char* SdioNodeToStr(const SdioHandle_t* const Node);
bool sdio_diag(void);
bool sdio_raw_reg_diag(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* SDIO_DIAG_H  */
