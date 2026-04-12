#ifndef HIST_FILTER_MCAL_H
#define HIST_FILTER_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "hist_filter_config.h"
#include "hist_filter_types.h"

#ifdef HAS_HIST_FILTER_DIAG
#include "hist_filter_diag.h"
#endif

/* API */
HistFilterHandle_t* HistFilterGetNode(uint8_t num);
const HistFilterConfig_t* HistFilterGetConfig(uint8_t num);
bool HistFilterIsValidConfig(const HistFilterConfig_t* const Config);


bool hist_filter_mcal_init(void);
bool hist_filter_init_one(uint8_t num);
bool hist_filter_init_custom(void);
bool hist_filter_init_common(const HistFilterConfig_t* const Config, HistFilterHandle_t* const Node);

/*setters*/
int32_t hist_filter_proc_sample(uint8_t num, const float in_sample);



#ifdef __cplusplus
}
#endif

#endif /* HIST_FILTER_MCAL_H */
