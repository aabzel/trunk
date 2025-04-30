#ifndef DELTA_SIGMA_DRV_H
#define DELTA_SIGMA_DRV_H

/*DELTA_SIGMA receiver invariant component*/
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

#include "delta_sigma_diag.h"
#include "delta_sigma_types.h"
#include "delta_sigma_config.h"

DeltaSigmaHandle_t* DeltaSigmaGetNode(uint8_t num);
const DeltaSigmaConfig_t* DeltaSigmaGetConfig(uint8_t num);

/*private*/
int8_t adc_1bit(double value, double comparator_middle) ;

double sign_v(double value);
bool delta_sigma_init_one(uint8_t num);
bool delta_sigma_mcal_init(void);
bool delta_sigma_proc(void);
bool delta_sigma_proc_one(uint8_t num);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*DELTA_SIGMA_DRV_H*/
