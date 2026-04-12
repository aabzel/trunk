#ifndef HIST_FILTER_DIAG_H
#define HIST_FILTER_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "hist_filter_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_HIST_FILTER
#error "+HAS_HIST_FILTER"
#endif

#ifndef HAS_HIST_FILTER_DIAG
#error "+HAS_HIST_FILTER_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool hist_filter_diag(void);
bool hist_filter_diag_one(uint8_t num);
const char* HistFilterConfigToStr(const HistFilterConfig_t* const Config);
const char* HistFilterNodeToStr(const HistFilterHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* HIST_FILTER_DIAG_H  */
