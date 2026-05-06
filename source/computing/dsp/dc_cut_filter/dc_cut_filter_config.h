#ifndef DC_CUT_FILTER_CONFIG_H
#define DC_CUT_FILTER_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dc_cut_filter_types.h"
#include "dc_cut_filter_dep.h"

extern const DcCutFilterConfig_t DcCutFilterConfig[];
extern DcCutFilterHandle_t DcCutFilterInstance[];

uint32_t dc_cut_filter_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* DC_CUT_FILTER_CONFIG_H */
