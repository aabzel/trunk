#ifndef RATIONAL_NUM_H
#define RATIONAL_NUM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rational_num_types.h"
#include "rational_num_diag.h"

bool float_to_integer_and_fractional(const float real_value, const uint32_t digit, FloatFixPoint_t* const Node);

bool fraction_to_fixed_point_float(int32_t numerator, int32_t denominator, uint32_t after_dot_digit,
                                   FloatFixPoint_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* RATIONAL_NUM_H */
