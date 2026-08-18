
#ifndef MIC2026_DIAG_H
#define MIC2026_DIAG_H

#include "mic2026_const.h"

#ifndef HAS_MIC2026
#error "+HAS_MIC2026"
#endif

const char* Mic2026ChanToStr(Mic2026Channel_t chan);

#endif /* MIC2026_DIAG_H */
