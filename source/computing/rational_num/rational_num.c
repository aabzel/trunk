#include "rational_num.h"

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
 */
bool float_to_integer_and_fractional(const float real_value, const uint32_t digit, FloatFixPoint_t* const Node) {
    bool res = false;
    if(Node) {
        Node->integer = (int32_t)real_value;
        uint32_t precision_i = int_pow(10, digit);

        float precision = (float)precision_i;
        float value_mux = fabsf(real_value) * ((float)precision);

        Node->fractional = ((uint32_t)value_mux) % precision_i;
        res = true;
    }

    return res;
}
