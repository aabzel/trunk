#ifndef IOMUX_GENERAL_DIAG_H
#define IOMUX_GENERAL_DIAG_H

#include <stdbool.h>

#include "iomux_types.h"

#ifdef HAS_IOMUX_CUSTOM
#include "iomux_custom_diag.h"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

#ifndef HAS_IOMUX_DIAG
#error "+HAS_IOMUX_DIAG"
#endif

bool IoMuxConfigDiag(const IoMuxConfig_t* const Config);
const char* IoMuxConfToStr(const IoMuxConfig_t* Config);

#endif /* IOMUX_GENERAL_DIAG_H  */
