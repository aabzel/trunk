#ifndef DC_CUT_FILTER_MCAL_H
#define DC_CUT_FILTER_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dc_cut_filter_config.h"
#include "dc_cut_filter_types.h"

#ifdef HAS_DC_CUT_FILTER_DIAG
#include "dc_cut_filter_diag.h"
#endif

/* API */
DcCutFilterHandle_t* DcCutFilterGetNode(uint8_t num);
const DcCutFilterConfig_t* DcCutFilterGetConfig(uint8_t num);
bool DcCutFilterIsValidConfig(const DcCutFilterConfig_t* const Config);

#ifdef HAS_DC_CUT_FILTER_CUSTOM
const DcCutFilterInfo_t* DcCutFilterGetInfo(uint8_t num);
#endif

bool dc_cut_filter_mcal_init(void);
bool dc_cut_filter_init_custom(void);
bool dc_cut_filter_init_common(const DcCutFilterConfig_t* const Config, DcCutFilterHandle_t* const Node);
bool dc_cut_filter_init_node(DcCutFilterHandle_t* const Node);
bool dc_cut_filter_init_one(uint8_t num);

bool dc_cut_filter_proc_one(uint8_t num);
bool dc_cut_filter_proc(void);

/*setters*/
bool dc_cut_filter_proc_sample(uint8_t num, const int32_t x,int32_t * const y);

/*getters*/

#ifdef __cplusplus
}
#endif

#endif /* DC_CUT_FILTER_MCAL_H */
