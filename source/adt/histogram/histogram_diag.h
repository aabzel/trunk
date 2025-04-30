#ifndef HISTOGRAM_DIAG_H
#define HISTOGRAM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

#include "histogram_types.h"


const char* HistogramItemToStr(const HistogramItem_t* const Node);
const char* HistogramNodeToStr(const HistogramHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* HISTOGRAM_DIAG_H */
