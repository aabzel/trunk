#ifndef MEDIAN_FILTER_FAST_DIAG_H
#define MEDIAN_FILTER_FAST_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "median_filter_fast_types.h"

bool median_filter_fast_diag(void);
bool median_filter_fast_diag_one(uint8_t num);
bool MedianFilterFastDiagCoefficient(uint8_t num);


const char* DirToStr(const MedianFilterBalanceDir_t balance_dir);

const char* MedianFilterVirtSizeToStr(const  MedianFilterFastHandle_t* const Node);
const char* MedianFilterFastNodeToStr(const  MedianFilterFastHandle_t* const Node);
const char* MedianFilterFastConfigToStr(const  MedianFilterFastConfig_t* const Config);
bool median_filter_fast_calc_frequency_response_norm(uint8_t num);
bool median_filter_fast_calc_frequency_response(uint8_t num);

#endif /* MEDIAN_FILTER_FAST_DIAG_H */
