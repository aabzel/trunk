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

double calc_percent_s(size_t numerator, size_t denominator);
uint32_t calc_percent_uu(uint32_t numerator, uint32_t denominator);

double rad_2_deg(double  rad);
bool is_prime(uint32_t number);
bool is_power_of_two(uint32_t const val);


double math_sign(const double val);
float math_sign_f(const float val);


double lo_calc_cos_sample(double time_s,
		double frequency,
		double phase_rad,
		double des_amplitude, double in_offset);


double lo_calc_sin_sample(double time_s,
		double frequency,
		double phase_rad,
		double des_amplitude, double in_offset);


double calc_chirp_sample(uint64_t time_us,
                         double f_max,
                         double f_0,
                         double phase_rad,
                         double amplitude,
                         double signal_diration_s);

double math_calc_sin_sample(double time_s, double frequency, double phase_ms, double des_amplitude, double in_offset);
float rad_to_deg_f(float rad);
double deg_to_rad(double deg);
bool check_continuity(uint64_t new_val, uint64_t* out_prev_val);
bool spot_change(uint8_t val);
double calc_sin_sample(uint64_t time_us, double frequency, double phase_ms, double amplitude, double in_offset);
#ifdef HAS_AOA
double aoa_calc_deg(double phase, double wavelength, double dist);
#endif /*HAS_AOA*/
double calc_fence_sample(uint64_t time_us, double in_frequency, double in_phase_ms, double amplitude, double in_offset);
double calc_pwm_sample(uint64_t time_us, double freq, double cur_phase_ms, double des_amplitude, double duty_cycle,
                       double offset);
uint8_t calc_pwm_sample_num(uint64_t time_us, uint32_t period_ms, uint8_t duty, int32_t phase_ms);
uint32_t int_pow(uint32_t base, uint32_t exp);
uint64_t ipow(uint32_t base, uint32_t exponenta);
int8_t two_complement_to_decimal(uint8_t in_code, int significant_bits);
double calc_saw_sample(uint64_t time_us, double in_frequency, double in_phase_ms, double des_amplitude,
                       double in_offset);


uint32_t sum_calc_u8(uint8_t* arr, uint32_t size); /*TODO move to array*/
uint32_t freq2period_ms(double freq_hz);
uint8_t toggle_val(uint8_t val);

double calc_dtmf_sample(uint64_t time_us,
		                double frequency1,
		                double frequency2,
		                double phase_ms,
		                double des_amplitude,
                        double in_offset);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_MATH_H */
