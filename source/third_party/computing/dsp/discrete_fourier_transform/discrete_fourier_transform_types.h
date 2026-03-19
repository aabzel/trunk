#ifndef DISCRETE_FOURIER_TRANSFORM_TYPES_H
#define DISCRETE_FOURIER_TRANSFORM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "discrete_fourier_transform_const.h"

typedef struct {
    double freq;
    double amplitude;
}Spectr_t;

#ifdef __cplusplus
}
#endif

#endif /* DISCRETE_FOURIER_TRANSFORM_TYPES_H */
