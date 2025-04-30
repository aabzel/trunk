#ifndef FIR_ISR_H
#define FIR_ISR_H

#include <stdbool.h>
#include <stdint.h>

#include "fir_types.h"

bool fir_pop_ll(FirHandle_t *Node, FirSample_t x0, FirSample_t *const out) ;

bool fir_proc_in_out_ll(FirHandle_t *Node, FirSample_t x, FirSample_t *const y);
bool fir_proc_in_out(uint8_t num, FirSample_t x0, FirSample_t* const y);

bool fir_proc_in_out_array(uint8_t num,
                           uint32_t size,
                           const FirSample_t* const x,
                           FirSample_t* const y);

#endif
