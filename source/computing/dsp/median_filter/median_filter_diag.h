#ifndef MEDIAN_FILTER_DIAG_H
#define MEDIAN_FILTER_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "median_filter_types.h"

bool median_filter_diag(void);
bool median_filter_diag_one(uint8_t num);
bool MedianFilterDiagCoefficient(uint8_t num);
const char* MedianFilterNodeToStr(const  MedianFilterHandle_t* const Node);
const char* MedianFilterConfigToStr(const  MedianFilterConfig_t* const Config);
bool median_filter_calc_frequency_response_norm(uint8_t num);
bool median_filter_calc_frequency_response(uint8_t num);

#endif /* MEDIAN_FILTER_DIAG_H */
