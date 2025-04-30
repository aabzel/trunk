#ifndef STATISTICS_TYPES_H
#define STATISTICS_TYPES_H

#include <stdint.h>
#include <stddef.h>

#include "statistics_const.h"

typedef struct {
    double* value;
    uint32_t* bar_chart;
    size_t size;
    uint32_t interanl_cnt;
    double expected_value;
    double standard_deviation;
    double variance;
    double sum;
    double min;
    double max;
    double spread;
    double histogram_step;
}RandomVariable_t;

#endif
