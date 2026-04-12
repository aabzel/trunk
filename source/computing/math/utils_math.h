#ifndef UTILS_MATH_H
#define UTILS_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stddef.h>

#include "std_includes.h"
#include "math_types.h"
#include "math_dep.h"



#define D2R (M_PI / 180.0)
#define R2D (180 / M_PI)

#define DEG_2_RAD(DEG) ((DEG)*M_PI / 180.0)
#define RAD_2_DEG(RAD) ((RAD)*180.0 / M_PI)

#define POW_2(VALUE) ((VALUE) * (VALUE))

#define MATH_MIN(n, m) (((n) < (m)) ? (n) : (m))
#define MATH_MAX(n, m) (((n) < (m)) ? (m) : (n))

#define ABS(n) (((n) < 0) ? -(n) : (n))
#define AVERAGE_2(a, b) (((a) + (b)) / 2.0)

float calc_percent_s(size_t numerator, size_t denominator);
uint32_t calc_percent_uu(uint32_t numerator, uint32_t denominator);

uint32_t int_pow_fast(const uint32_t base, const uint32_t exponenta) ;
float rad_2_deg(float rad);
bool is_prime(uint32_t number);
bool is_power_of_two(uint32_t const val);

uint32_t math_calc_abs(const uint32_t a, const uint32_t b);
int32_t math_sign_s32(const int32_t val);
int32_t math_abs_s32(const int32_t val);
MathParity_t math_calc_parity(const uint32_t natural);

float math_sign(const float val);
float math_sign_f(const float val);
uint32_t int_pow_slow(uint32_t base, uint32_t exp) ;

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

float math_period_ms_to_freq_hz(const uint32_t period_ms);
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
uint8_t calc_pwm_sample_num(uint64_t time_us, uint32_t period_ms, float duty, int32_t phase_ms);
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

bool math_sum3(const uint32_t sum);
bool math_sum4(const uint32_t sum);
bool math_sum4_dynamic(const uint32_t sum);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_MATH_H */
