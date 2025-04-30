#ifndef UTILS_MATH_H
#define UTILS_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "math_dep.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#define M_2PI (M_PI*2.0)
#endif

#define D2R (M_PI / 180.0)
#define R2D (180 / M_PI)

#define DEG_2_RAD(DEG) ((DEG)*M_PI / 180.0)
#define RAD_2_DEG(RAD) ((RAD)*180.0 / M_PI)

#define POW_2(VALUE) ((VALUE) * (VALUE))

#ifndef MIN
#define MIN(n, m) (((n) < (m)) ? (n) : (m))
#endif

#ifndef MAX
#define MAX(n, m) (((n) < (m)) ? (m) : (n))
#endif

#define ABS(n) (((n) < 0) ? -(n) : (n))
#define AVERAGE_2(a, b) (((a) + (b)) / 2.0)

float calc_percent_s(size_t numerator, size_t denominator);
uint32_t calc_percent_uu(uint32_t numerator, uint32_t denominator);

float rad_2_deg(float  rad);
bool is_prime(uint32_t number);
bool is_power_of_two(uint32_t const val);


float math_sign(const float val);
float math_sign_f(const float val);


float lo_calc_cos_sample(float time_s,
		float frequency,
		float phase_rad,
		float des_amplitude, float in_offset);


float lo_calc_sin_sample(float time_s,
		float frequency,
		float phase_rad,
		float des_amplitude, float in_offset);


float calc_chirp_sample(uint64_t time_us,
                         float f_max,
                         float f_0,
                         float phase_rad,
                         float amplitude,
                         float signal_diration_s);

float math_calc_sin_sample(float time_s, float frequency, float phase_ms, float des_amplitude, float in_offset);
float rad_to_deg_f(float rad);
float deg_to_rad(float deg);
bool check_continuity(uint64_t new_val, uint64_t* out_prev_val);
bool spot_change(uint8_t val);
float calc_sin_sample(uint64_t time_us, float frequency, float phase_ms, float amplitude, float in_offset);
#ifdef HAS_AOA
float aoa_calc_deg(float phase, float wavelength, float dist);
#endif /*HAS_AOA*/
float calc_fence_sample(uint64_t time_us, float in_frequency, float in_phase_ms, float amplitude, float in_offset);
float calc_pwm_sample(uint64_t time_us, float freq, float cur_phase_ms, float des_amplitude, float duty_cycle,
                       float offset);
uint8_t calc_pwm_sample_num(uint64_t time_us, uint32_t period_ms, uint8_t duty, int32_t phase_ms);
uint32_t int_pow(uint32_t base, uint32_t exp);
uint64_t ipow(uint32_t base, uint32_t exponenta);
int8_t two_complement_to_decimal(uint8_t in_code, int significant_bits);
float calc_saw_sample(uint64_t time_us, float in_frequency, float in_phase_ms, float des_amplitude,
                       float in_offset);


uint32_t sum_calc_u8(uint8_t* arr, uint32_t size); /*TODO move to array*/
uint32_t freq2period_ms(float freq_hz);
uint8_t toggle_val(uint8_t val);

float calc_dtmf_sample(uint64_t time_us,
		                float frequency1,
		                float frequency2,
		                float phase_ms,
		                float des_amplitude,
                        float in_offset);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_MATH_H */
