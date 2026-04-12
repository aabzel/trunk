#ifndef HIST_FILTER_CONFIG_H
#define HIST_FILTER_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "hist_filter_types.h"
#include "hist_filter_dep.h"

extern const HistFilterConfig_t HistFilterConfig[];
extern HistFilterHandle_t HistFilterInstance[];

uint32_t hist_filter_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* HIST_FILTER_CONFIG_H */
