#ifndef FIR_H
#define FIR_H

#include "std_includes.h"
#include "fir_config.h"
#include "fir_types.h"
#include "fir_isr.h"
#ifdef HAS_FIR_DIAG
#include "fir_diag.h"
#endif

// API
FirHandle_t* FirGetNode(uint8_t num);
const FirConfig_t* FirGetConfig(uint8_t num);
bool fir_init_one(uint8_t num);
bool fir_reset_one(uint8_t num);
bool fir_mcal_init(void);
int32_t fir_order_get(uint8_t num);
/*
 https://en.wikipedia.org/wiki/Finite_impulse_response
 */
bool fir_calc_frequency_response(uint8_t num, double f_step) ;
bool fir_impulse_response(uint8_t num);

//bool fir_proc_in_out(uint8_t num, FirSample_t in, FirSample_t* const out);
//bool fir_push(uint8_t num, FirSample_t in);
bool fir_proc_file(uint8_t num, char* file_name, uint16_t column_x, uint16_t column_y);
bool fir_set_b(uint8_t num, uint32_t k, FirSample_t b);
bool fir_set_mode(uint8_t num, FirMode_t mode);
bool fir_synthesize(uint8_t num,
		uint32_t order,
		FirSample_t cutoff_frequency_hz,
        FirSample_t sample_frequency_hz);

//bool fir_pop(uint8_t num, FirSample_t in, FirSample_t* const out);

#endif
