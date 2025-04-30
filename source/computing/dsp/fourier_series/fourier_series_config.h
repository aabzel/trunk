#ifndef FOURIER_SERIES_CONFIG_GENERAL_H
#define FOURIER_SERIES_CONFIG_GENERAL_H

#include <stdbool.h>
#include <stdint.h>

#include "fourier_series_types.h"

extern const FourierSeriesConfig_t FourierSeriesConfig[];
extern FourierSeriesHandle_t FourierSeriesItem[];

uint32_t fourier_series_get_cnt(void);

#endif /* FOURIER_SERIES_CONFIG_GENERAL_H  */
