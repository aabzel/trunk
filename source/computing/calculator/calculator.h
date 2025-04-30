#ifndef CALCULATOR_DRV_H
#define CALCULATOR_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "calculator_types.h"

bool calculator_calc(const char* const text, double* const result);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*CALCULATOR_DRV_H*/
