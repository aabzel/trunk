#include "float_utils.h"

#include <math.h>

#include "bit_utils.h"
#include "data_types.h"
#include "utils_math.h"
#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_MATH_EXT
bool is_floats_equal(float valA, float valB) { return is_float_equal_relative(valA, valB, (float)F_EPSILON); }
#endif

#ifdef HAS_MATH_EXT
bool is_float_equal_relative(float a__fife, float b__fife, float relative_epsilon__fife) {
    bool retval__fife;
    if(fabsf(a__fife - b__fife) <=
       fmaxf(fabsf(relative_epsilon__fife * b__fife), fabsf(relative_epsilon__fife * a__fife))) {
        retval__fife = true;
    } else {
        retval__fife = false;
    }
    return retval__fife;
}
#endif

#ifdef HAS_MATH_EXT
bool is_double_equal_relative(double value, double b__fide, double relative_epsilon__fide) {
    bool retval__fide;
    if(fabs(value - b__fide) <= fmax(fabs(relative_epsilon__fide * b__fide), fabs(relative_epsilon__fide * value))) {
        retval__fide = true;
    } else {
        retval__fide = false;
    }
    return retval__fide;
}
#endif

typedef union {
    float val;
    uint32_t num;
} Word_t;

typedef union {
    double val;
    uint64_t num;
} qWord_t;

bool is_float_equal_absolute(float f1, float f2, float precision) {
    bool res = false;
    Word_t w1;
    Word_t w2;
    w1.val = f1;
    w2.val = f2;
    if(w1.num == w2.num) {
        res = true;
    } else {
        if(((f1 - precision) < f2) && (f2 < (f1 + precision))) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

bool is_double_equal_absolute(double d1, double d2, double precision) {
    bool res = false;
    qWord_t w1;
    qWord_t w2;
    w1.val = d1;
    w2.val = d2;
    if(w1.num == w2.num) {
        res = true;
    } else {
        if(((d1 - precision) <= d2) && (d2 < (d1 + precision))) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

float float_max(float x1, float x2) {
    float out_val = x1;
    if(x1 < x2) {
        out_val = x2;
    }
    return out_val;
}

double double_max(double x1, double x2) {
    double out_val = x1;
    if(x1 < x2) {
        out_val = x2;
    }
    return out_val;
}

float float_min(float x1, float x2) {
    float out_val = x1;
    if(x2 < x1) {
        out_val = x2;
    }
    return out_val;
}

float float_limiter(float in_value, float up_limit) {
    float out_value = in_value;
    if(up_limit < in_value) {
        out_value = up_limit;
    }
    return out_value;
}

float float_limiter_down_up(float in_value, float down_limit, float up_limit) {
    float out_value = in_value;
    if(up_limit < in_value) {
        out_value = up_limit;
    }
    if(in_value < down_limit) {
        out_value = down_limit;
    }
    return out_value;
}

float float_limiter2(float down_limit, float in_value, float up_limit) {
    float out_value = in_value;
    if(up_limit < in_value) {
        out_value = up_limit - F_EPSILON;
    }
    if(in_value < down_limit) {
        out_value = down_limit + F_EPSILON;
    }
    return out_value;
}

// https://github.com/raisov/hsnr_to_float
/*
15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
|    Exponent   | S |                 Mantissa                  |
|_______________|___|___________________________________________|

To decode this format when
the exponent is non-zero, first create a 13-bit
signed integer in which bits zero through ten are copied from the Mantissa field,
and bits 11 and 12 are either 01 or 10 depending on whether
S = 0   01
S = 1   10
Then, multiply this by 2**(exponent�25),

where the exponent field is interpreted as an unsigned 4-bit integer.

To decode the High-SNR format when the exponent is zero
simply interpret the mantissa as a 12-bit signed integer and multiply by 2**-24.
*/
#ifdef HAS_MATH_EXT
double high_snr_decode(int snr) {
    TypeHighSnr_t HighSnr;
    double out_val = 0.0;
    HighSnr.u16 = (uint16_t)snr;
#ifdef HAS_LOG
    LOG_DEBUG(TEST, "%d |%d |%d", HighSnr.exponent, HighSnr.sign, HighSnr.mantissa);
#endif
    if(0 == HighSnr.exponent) {
#ifdef HAS_LOG
        LOG_DEBUG(TEST, "ExpZero");
#endif
        int32_t smantissa32b = parse_n_bit_signed(HighSnr.u16, 12);
#ifdef HAS_LOG
        LOG_DEBUG(TEST, "smantissa32 %d", smantissa32b);
#endif
        out_val = smantissa32b * pow(2.0, -24.0);
    } else {
#ifdef HAS_LOG
        LOG_DEBUG(TEST, "ExpVal");
#endif
        int16_t sman13 = 0;
        sman13 = HighSnr.mantissa;

        if(0 == HighSnr.sign) {
            SET_BIT_NUM(sman13, 11);
            RESET_BIT_NUM(sman13, 12);
        } else {
            RESET_BIT_NUM(sman13, 11);
            SET_BIT_NUM(sman13, 12);
        }
        int32_t smantissa32b = parse_n_bit_signed(sman13, 13);
#ifdef HAS_LOG
        LOG_DEBUG(TEST, "smantissa32 %d", smantissa32b);
#endif
        out_val = ((double)smantissa32b) * pow(2.0, (double)(HighSnr.exponent - 25));
    }
    return out_val;
}
#endif

bool double_is_zero(double value) {
    bool res = false;
    res = is_double_equal_absolute(0.0, value, D_EPSILON);
    return res;
}

bool float_is_zero(float value) {
    bool res = false;
    res = is_float_equal_absolute(0.0, value, F_EPSILON);
    return res;
}

/*Return the sign of float   number*/
int32_t float_sign(const float value) {
    int32_t sign = 0;
    if(0.0 <= value) {
        sign = 1;
    } else if(value < 0.0) {
        sign = -1;
    }
    return sign;
}

/*
 * value 1.25
 * digit -  number of decimal places
 *
 * TODO test float_to_integer_and_fractional
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
