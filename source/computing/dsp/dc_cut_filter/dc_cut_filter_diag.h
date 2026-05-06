#ifndef DC_CUT_FILTER_DIAG_H
#define DC_CUT_FILTER_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dc_cut_filter_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_DC_CUT_FILTER
#error "+HAS_DC_CUT_FILTER"
#endif

#ifndef HAS_DC_CUT_FILTER_DIAG
#error "+HAS_DC_CUT_FILTER_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool dc_cut_filter_diag(void);
bool dc_cut_filter_diag_one(uint8_t num);
const char* DcCutFilterConfigToStr(const DcCutFilterConfig_t* const Config);
const char* DcCutFilterNodeToStr(const DcCutFilterHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* DC_CUT_FILTER_DIAG_H  */
