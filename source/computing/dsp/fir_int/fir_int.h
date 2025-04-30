#ifndef FIR_INT_H
#define FIR_INT_H

#include <stdbool.h>
#include <stdint.h>

#include "fir_int_config.h"
#include "fir_int_diag.h"
#include "fir_int_types.h"

// API
FirIntHandle_t* FirIntGetNode(uint8_t num);
const FirIntConfig_t* FirIntGetConfig(uint8_t num);
bool fir_int_init_one(uint8_t num);
bool fir_int_reset_one(uint8_t num);
/*
 https://en.wikipedia.org/wiki/Finite_impulse_response
 */
bool fir_int_calc_frequency_response(uint8_t num, double f_step) ;
bool fir_int_impulse_response(uint8_t num);

bool fir_int_proc_in_out(uint8_t num, FirIntSample_t in, FirIntSample_t* const out);
bool fir_int_push(uint8_t num, FirIntSample_t in);
bool fir_int_set_b(uint8_t num, uint32_t k, FirIntSample_t b);
bool fir_int_mcal_init(void);
bool fir_int_synthesize(uint8_t num, uint32_t order, float cutoff_frequency_hz,
                    float sample_frequency_hz);

bool fir_int_pop(uint8_t num, FirIntSample_t in, FirIntSample_t* const out);

#endif
