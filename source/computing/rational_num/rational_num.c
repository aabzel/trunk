#include "rational_num.h"

#include <float.h>
#include <math.h>
//#include <ieeefp.h>

#include "std_includes.h"
#include "utils_math.h"

/*
 Example:xxxx(238500,16384,5,...) ->  14.55688
*/
bool fraction_to_fixed_point_float(int32_t numerator, int32_t denominator, uint32_t after_dot_digit,
                                   FloatFixPoint_t* const Node) {
    bool res = false;
    if(Node) {
        if(denominator) {
            Node->accurancy = after_dot_digit;
            int32_t sign = math_sign_s32(numerator / denominator);
            int32_t numerator_abs = math_abs_s32(numerator);
            int32_t denominator_abs = math_abs_s32(denominator);
            uint64_t scale = ipow(10, after_dot_digit);

            int32_t integer_abs = numerator_abs / denominator_abs;
            uint64_t val1 = (scale * numerator_abs) / denominator_abs;
            uint64_t val2 = integer_abs * scale;
            uint64_t fractional_u64 = val1 - val2;
            Node->fractional = (uint32_t)fractional_u64;
            Node->integer = sign * integer_abs;
            res = true;
        }
    }
    return res;
}

/*
  value 1.25
  digit -  number of decimal places
  TODO test float_to_integer_and_fractional

  float_to_integer_and_fractional(0.05, const uint32_t digit, FloatFixPoint_t* const Node)

 */
bool float_to_integer_and_fractional(const float real_value, const uint32_t digit, FloatFixPoint_t* const Node) {
    bool res = false;
    if(Node) {
        Node->integer = (int32_t)real_value;
        uint32_t precision_i = int_pow(10, digit);

        float precision = (float)precision_i;
        float value_mux = fabsf(real_value) * ((float)precision);

        Node->fractional = ((uint32_t)value_mux) % precision_i;
        Node->accurancy = digit;
        res = true;
    }

    return res;
}

/*TODO Test it! and add to CLI */
bool float_to_rational_number_v0(const float real_value, int32_t* const numerator, int32_t* const denominator) {
    bool result = false;
    float remaining = real_value;
    int32_t prev_num = 0;
    int32_t prev_den = 1;
    int32_t curr_num = 1;
    int32_t curr_den = 0;
    int32_t temp_num = 0;
    int32_t temp_den = 0;
    int32_t integer_part = 0;
    float fractional_part = 0.0f;
    float error = 0.0f;
    float best_error = FLT_MAX;
    int32_t best_num = 0;
    int32_t best_den = 1;
    const float epsilon = 1e-6f;
    uint32_t max_iterations = 100u;
    uint32_t iteration = 0u;

    if((NULL != numerator) && (NULL != denominator)) {
        if(fabsf(real_value) <= (float)INT32_MAX) {
            remaining = fabsf(real_value);

            do {
                integer_part = (int32_t)remaining;
                fractional_part = remaining - (float)integer_part;

                temp_num = integer_part * curr_num + prev_num;
                temp_den = integer_part * curr_den + prev_den;

                if((temp_num > INT32_MAX) || (temp_den > INT32_MAX)) {
                    break;
                }

                prev_num = curr_num;
                prev_den = curr_den;
                curr_num = temp_num;
                curr_den = temp_den;

                error = fabsf(((float)curr_num / (float)curr_den) - fabsf(real_value));

                if(error < best_error) {
                    best_error = error;
                    best_num = curr_num;
                    best_den = curr_den;
                }

                if(fabsf(fractional_part) < epsilon) {
                    break;
                }

                remaining = 1.0f / fractional_part;
                iteration++;

            } while((iteration < max_iterations) && (remaining > epsilon));

            if(real_value < 0.0f) {
                best_num = -best_num;
            }

            *numerator = best_num;
            *denominator = best_den;
            result = true;
        }
    }

    return result;
}

bool float_to_rational_number(const float real_value, int32_t* const numerator, int32_t* const denominator) {
    bool result = false;

    if((numerator != NULL) && (denominator != NULL)) {
        /* Handle special cases: NaN and infinity */
        if(isinf(real_value)) {
            *numerator = 0;
            *denominator = 1;
            result = false;
        } else {
            float value = real_value;
            int32_t sign = 1;

            /* Get absolute value and sign */
            if(value < 0.0f) {
                sign = -1;
                value = -value;
            }

            /* Very small values: best approximation is 0/1 */
            if(value < 1.0e-8f) {
                *numerator = 0;
                *denominator = 1;
                result = true;
            }
            /* Values too large to fit into int32_t numerator */
            else if(value > (float)INT32_MAX) {
                *numerator = 0;
                *denominator = 1;
                result = false;
            } else {
                /* Continued fraction approximation */
                const uint32_t max_iter = 20U;
                const float eps = 1.0e-7f;

                int64_t prev_num = 0LL;
                int64_t prev_den = 1LL;
                int64_t curr_num = 1LL;
                int64_t curr_den = 0LL;

                float x = value;
                uint32_t iter = 0U;
                int32_t a = 0;
                bool found = false;
                bool overflow = false;

                while((!found) && (!overflow) && (iter < max_iter)) {
                    /* Get integer part, ensure it does not overflow int32_t */
                    if(x > (float)INT32_MAX) {
                        a = INT32_MAX;
                    } else {
                        a = (int32_t)x;
                    }

                    /* Compute next convergent using 64-bit arithmetic */
                    int64_t next_num = (int64_t)a * curr_num + prev_num;
                    int64_t next_den = (int64_t)a * curr_den + prev_den;

                    /* Check overflow of int32_t for numerator and denominator */
                    if((next_num > (int64_t)INT32_MAX) || (next_num < (int64_t)INT32_MIN) ||
                       (next_den > (int64_t)INT32_MAX) || (next_den < 1LL)) {
                        /* Would overflow - keep current convergent */
                        overflow = true;
                    } else {
                        /* Check if this convergent is accurate enough */
                        float approx = (float)next_num / (float)next_den;
                        float error = fabsf(approx - value);

                        if(error < eps) {
                            *numerator = (int32_t)next_num * sign;
                            *denominator = (int32_t)next_den;
                            result = true;
                            found = true;
                        } else {
                            /* Prepare for next iteration */
                            float remainder = x - (float)a;
                            if(fabsf(remainder) < FLT_EPSILON) {
                                /* Exact fraction found */
                                *numerator = (int32_t)next_num * sign;
                                *denominator = (int32_t)next_den;
                                result = true;
                                found = true;
                            } else {
                                /* Update recurrence */
                                prev_num = curr_num;
                                prev_den = curr_den;
                                curr_num = next_num;
                                curr_den = next_den;

                                /* Next term of continued fraction */
                                x = 1.0f / remainder;
                                iter++;
                            }
                        }
                    }
                }

                /* If no accurate fraction found, return the last safe convergent */
                if(!found) {
                    if((curr_num >= (int64_t)INT32_MIN) && (curr_num <= (int64_t)INT32_MAX) && (curr_den >= 1LL) &&
                       (curr_den <= (int64_t)INT32_MAX)) {
                        *numerator = (int32_t)curr_num * sign;
                        *denominator = (int32_t)curr_den;
                        result = true;
                    } else if((prev_num >= (int64_t)INT32_MIN) && (prev_num <= (int64_t)INT32_MAX) &&
                              (prev_den >= 1LL) && (prev_den <= (int64_t)INT32_MAX)) {
                        *numerator = (int32_t)prev_num * sign;
                        *denominator = (int32_t)prev_den;
                        result = true;
                    } else {
                        /* Fallback: simple rounding with denominator 1 */
                        int32_t rounded = (int32_t)(value + 0.5f);
                        if((rounded >= 0) && (rounded <= INT32_MAX)) {
                            *numerator = rounded * sign;
                            *denominator = 1;
                            result = true;
                        } else {
                            *numerator = 0;
                            *denominator = 1;
                            result = false;
                        }
                    }
                }
            }
        }
    }

    return result;
}
