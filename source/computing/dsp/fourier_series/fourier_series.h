#ifndef FOURIER_SERIES_H
#define FOURIER_SERIES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "fourier_series_dep.h"
#include "fourier_series_types.h"
#include "fourier_series_config.h"

FourierSeriesHandle_t* FourierSeriesGetNode(uint8_t num);
const FourierSeriesConfig_t* FourierSeriesGetConfNode(uint8_t num);
bool fourier_series_init(void);
bool fourier_series_calc_coefficient(uint8_t num, uint8_t order, const char* const file_name);

#ifdef __cplusplus
}
#endif

#endif /* FOURIER_SERIES_H */
