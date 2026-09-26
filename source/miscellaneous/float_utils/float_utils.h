#ifndef FLOAT_UTILS_H
#define FLOAT_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "float_types.h"
#include "float_diag.h"

#ifndef HAS_FLOAT_UTILS
#error "+HAS_FLOAT_UTILS"
#endif

#ifndef MAX
#define MAX(n, m) (((n) < (m)) ? (m) : (n))
#endif


#define F_EPSILON 1E-10f
#define D_EPSILON 1E-10

#define CALC_PRECENT(numerator, denominator) (100.0f * ((float)numerator / (float)denominator))

/*on STM32 float values distorted when passed by value*/
#define IS_FLOAT_EQUAL_ABSOLUTE(f1, f2, precision) ((((f1 - precision) < f2) && (f2 < (f1 + precision))) ? true : false)


/*getter*/
float float_array_get_min(const float* const arr, const uint32_t size) ;
float float_array_get_max(const float* const arr, const uint32_t size) ;
bool double_is_zero(double a__fide);
int32_t float_sign(const float value);
bool is_double_equal_absolute(double a__fide, double b__fide, double absolute_epsilon__fide);
bool is_double_equal_relative(double a__fide, double b__fide, double relative_epsilon__fide);
bool is_float_equal_absolute(float a__fife, float b__fife, float absolute_epsilon__fife);
bool is_float_equal_relative(float a__fife, float b__fife, float relative_epsilon__fife);
bool is_floats_equal(float valA, float valB);
bool float_is_zero(float value);
float float_limiter(float in_value, float up_limit);
float float_limiter2( float down_limit, float in_value, float up_limit);
float float_limiter_down_up(const float in_value, const float down_limit, const float up_limit);
float float_limiter_down(const float in_value, const float down_limit);
float float_limiter_up(float in_value, float up_limit) ;
float float_max(float x1, float x2);
float float_min(float x1, float x2);
float float_normalize(const float in_value, const float min_val, const float max_val);
double high_snr_decode(int snr);
float float_binary_coded_decimal_to_float(const uint8_t* const data, const uint32_t size);
double double_max(double x1, double x2);

/*setter*/
bool float_array_init_pattern(float* const arr, const uint32_t size, const float patt) ;
bool float_array_zero(float* const arr, const uint32_t size) ;
bool float_decimator2_max(float* const array, const uint32_t size);


#ifdef __cplusplus
}
#endif

#endif /* FLOAT_UTILS_H */
