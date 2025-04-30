#ifndef HISTOGRAM_CONFIG_H
#define HISTOGRAM_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "histogram_types.h"

#ifndef HAS_HISTOGRAM
#error " +HAS_HISTOGRAM"
#endif

extern const HistogramConfig_t HistogramConfig[];
extern HistogramHandle_t HistogramInstance[];

uint32_t histogram_get_cnt(void);

#endif /* HISTOGRAM_CONFIG_H */
