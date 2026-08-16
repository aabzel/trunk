#ifndef LOCAL_OSCILLATOR_MCAL_H
#define LOCAL_OSCILLATOR_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "local_oscillator_types.h"

#ifdef HAS_LOCAL_OSCILLATOR_DIAG
#include "local_oscillator_diag.h"
#endif

/* API */

/*setters*/

/*getters*/
int32_t cos4_int(int32_t n, int32_t phase);
int32_t sin4_int(int32_t n, int32_t phase);

int32_t pwm_cos4_int(int32_t n, int32_t phase);
int32_t pwm_sin4_int(int32_t n, int32_t phase);


float lo_calc_cos_sample(float time_s,
                         float frequency,
                         float phase_rad,
                         float des_amplitude,
                         float in_offset);

float lo_calc_sin_sample(float time_s,
                         float frequency,
                         float phase_rad,
                         float des_amplitude,
                         float in_offset);

#ifdef __cplusplus
}
#endif

#endif /* LOCAL_OSCILLATOR_MCAL_H */
