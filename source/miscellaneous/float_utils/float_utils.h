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

#define F_EPSILON 1E-10f
#define D_EPSILON 1E-10

#define CALC_PRECENT(numerator, denominator) (100.0f * ((float)numerator / (float)denominator))

/*on STM32 float values distorted when passed by value*/
#define IS_FLOAT_EQUAL_ABSOLUTE(f1, f2, precision) ((((f1 - precision) < f2) && (f2 < (f1 + precision))) ? true : false)



int32_t float_sign(const float value);
bool float_to_integer_and_fractional(const float value,
                                     const uint32_t precision,
                                     FloatFixPoint_t* const Node );

bool double_is_zero(double a__fide);
bool is_double_equal_absolute(double a__fide, double b__fide, double absolute_epsilon__fide);
bool is_double_equal_relative(double a__fide, double b__fide, double relative_epsilon__fide);
bool is_float_equal_absolute(float a__fife, float b__fife, float absolute_epsilon__fife);
bool is_float_equal_relative(float a__fife, float b__fife, float relative_epsilon__fife);
bool is_floats_equal(float valA, float valB);
bool float_is_zero(float value);
float float_limiter(float in_value, float up_limit);
float  float_limiter2( float down_limit, float in_value, float up_limit);
float float_limiter_down_up(float in_value, float down_limit, float up_limit);

float float_max(float x1, float x2);
float float_min(float x1, float x2);
double double_max(double x1, double x2);
double high_snr_decode(int snr);

#ifdef __cplusplus
}
#endif

#endif /* FLOAT_UTILS_H */
