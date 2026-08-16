#include "utils_math.h"

#include <math.h>
#include <stdlib.h>

#include "std_includes.h"
#include "time_mcal.h"

#ifdef HAS_FLOAT_UTILS
#include "float_utils.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_ZEPHYR
#include "arm_math.h"
#endif

#ifndef HAS_ZEPHYR
/*
 return 0 if value contains only 1 bit set
 1, 2 4 8 16 32 64 128 512 ....
 */
bool is_power_of_two(uint32_t const val) {
    bool outRetPt = false;
    /*check power of two*/
    if(0u == (val & (val - 1u))) {
        /*only one bit set in the value */
        outRetPt = true;
    }
    if(0u == val) {
        outRetPt = false;
    }
    return outRetPt;
}
#endif

float math_period_ms_to_freq_hz(const uint32_t period_ms) {
    float freq_hz = 0.0f;
    if(period_ms) {
        freq_hz = 1000.0f / ((float)period_ms);
    }
    return freq_hz;
}

float math_sign_f(const float val) {
    float out_val = 0.0f;
    if(0.0f < val) {
        out_val = 1.0f;
    }
    if(val < 0.0f) {
        out_val = -1.0f;
    }
    return out_val;
}

float math_sign(const float val) {
    float out_val = 0.0f;
    if(0.0f < val) {
        out_val = 1.0f;
    }
    if(val < 0.0f) {
        out_val = -1.0f;
    }
    return out_val;
}

int32_t math_sign_s32(const int32_t val) {
    int32_t out_val = 0;
    if(0 < val) {
        out_val = 1;
    }
    if(val < 0) {
        out_val = -1;
    }
    return out_val;
}

int32_t math_abs_s32(const int32_t value) {
    int32_t abs_s32 = value;
    if(value < 0) {
        abs_s32 = -value;
    }
    return abs_s32;
}

int64_t math_abs_s64(const int64_t value) {
    int64_t abs_s64 = value;
    if(value < 0) {
        abs_s64 = -value;
    }
    return abs_s64;
}

int8_t two_complement_to_decimal(uint8_t in_code, int significant_bits) {
    int power = (int)pow((float)2.0f, (float)(significant_bits - 1));
    int sum = 0;
    int i = 0;
    for(i = significant_bits - 1; 0 <= i; i--) {
        if((i == (significant_bits - 1)) && ((1 << i) == ((1 << i) & in_code))) {
            sum = power * -1;
        } else {
            if(in_code & (1 << i)) {
                sum += power;
            }
        }
        power /= 2;
    }

    return sum;
}

uint64_t ipow(uint32_t base, uint32_t exponenta) {
    uint64_t ret = 1, i = 0;
    if(0 != exponenta) {
        for(i = 1; i <= exponenta; i++) {
            ret *= base;
        }
    }
    return ret;
}

uint32_t sum_calc_u8(uint8_t* arr, uint32_t size) {
    uint32_t i = 0;
    uint32_t sum = 0;
    for(i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

float math_calc_sin_sample(float time_s, float frequency, float phase_ms, float des_amplitude, float in_offset) {
    float lineVal = 0.0;
#ifdef HAS_LOG
    LOG_DEBUG(MATH, "Sin,Time:%f,Freq:%f,Phase:%f,Amp:%f,OffSet:%f", time_s, frequency, phase_ms, des_amplitude,
              in_offset);
#endif
    float argument = 0.0f;
    float amplitude = 0.0f;
    float amplitude_scaled = 0.0f;
    float cur_time_ms = time_s * 1000.0f;
#ifdef HAS_LOG
    LOG_PARN(MATH, "T:%u ms", cur_time_ms);
#endif
    lineVal = ((cur_time_ms + phase_ms) / 1000.0f) * frequency; /*tune frequency*/
#ifdef HAS_LOG
    LOG_PARN(MATH, "lineVal:%f", lineVal);
#endif
    argument = 2.0f * M_PI * lineVal;
#ifdef HAS_LOG
    LOG_PARN(MATH, "arg:%f", argument);
#endif
#ifdef HAS_ZEPHYR
    amplitude = (float)arm_sin_f32((float32_t)argument);
#else
    amplitude = (float)sinf((float)argument);
#endif
#ifdef HAS_LOG
    LOG_PARN(MATH, "A:%f", amplitude);
#endif
    amplitude_scaled = (des_amplitude * amplitude) + in_offset;
#ifdef HAS_LOG
    LOG_DEBUG(MATH, "SinSample: %7.3f", amplitude_scaled);
#endif
    return amplitude_scaled;
}

float calc_sin_sample(uint64_t time_us, float frequency, float phase_ms, float des_amplitude, float in_offset,
                      float signal_diration_s) {
    float cur_time_s = USEC_2_SEC(time_us);
    float amplitude_scaled = 0.0f;
    if(cur_time_s < signal_diration_s) {
        float lineVal = 0.0f;
#ifdef HAS_LOG
        LOG_DEBUG(MATH, "Sin,T:%u,Freq:%f Hz,Pha:%f,Amp:%f,O:%f", time_us, frequency, phase_ms, des_amplitude, in_offset);
#endif

        float argument = 0.0f;
        float amplitude = 0.0f;
        float cur_time_ms = ((float)time_us) / 1000.0f;
#ifdef HAS_LOG
        LOG_PARN(MATH, "T:%u ms", cur_time_ms);
#endif
        lineVal = ((cur_time_ms + phase_ms) / 1000.0f) * frequency; /*tune frequency*/
#ifdef HAS_LOG
        LOG_PARN(MATH, "lineVal:%f", lineVal);
#endif
        argument = 2.0f * M_PI * lineVal;
#ifdef HAS_LOG
        LOG_PARN(MATH, "arg:%f", argument);
#endif

#ifdef HAS_ZEPHYR
        amplitude = (float)arm_sin_f32((float32_t)argument);
#else
        amplitude = (float)sinf((float)argument);
#endif
#ifdef HAS_LOG
        LOG_PARN(MATH, "A:%f", amplitude);
#endif
        amplitude_scaled = (des_amplitude * amplitude) + in_offset;
#ifdef HAS_LOG
        LOG_DEBUG(MATH, "SinSample: %7.3f", amplitude_scaled);
#endif
    }
    return amplitude_scaled;
}


#ifdef HAS_DTMF
float calc_dtmf_sample(uint64_t time_us, float frequency1, float frequency2, float phase_ms, float des_amplitude,
                       float in_offset) {
    // float lineVal = 0.0;
#ifdef HAS_LOG
    LOG_DEBUG(MATH, "DualTone T:%u,F1:%f, F2:%f, P:%f, A:%f, O:%f", time_us, frequency1, frequency2, phase_ms,
              des_amplitude, in_offset);
#endif
    float amplitude_scaled = 0.0f;
    float tone1 = calc_sin_sample(time_us, frequency1, phase_ms, des_amplitude, in_offset, FLT_MAX);
    float tone2 = calc_sin_sample(time_us, frequency2, phase_ms, des_amplitude, in_offset, FLT_MAX);
    amplitude_scaled = tone1 + tone2;

    return amplitude_scaled;
}
#endif

/*
  cur_time_s - up time in s
  signal_diration_s - signal duration
  f_2_hz - maximum value of signal frequency.
  f_1_hz - initial signal frequency
  des_amplitude - signal amplitude
  phase_rad -  initial phase.
 */
float calc_chirp_sample(float cur_time_s, float f_2_hz, float f_1_hz, float phase_rad, float amplitude,
                        float signal_diration_s) {
    float amplitude_scaled = 0.0f;
    float b = 0.0f;
    if(0.0f < signal_diration_s) {
        float bandwith_hz = f_2_hz - f_1_hz;
        b = bandwith_hz / signal_diration_s;

        // float cur_time_s = ((float)time_us) / 1000000.0f;

        float argument_rad = phase_rad;
        argument_rad += M_2PI * (f_1_hz * cur_time_s + (b * cur_time_s * cur_time_s) / 2.0f);

        if(signal_diration_s < cur_time_s) {
            amplitude = 0.0f;
        }
        amplitude_scaled = amplitude * sinf(argument_rad);
    }
    return amplitude_scaled;
}

float calc_chirp_sample_hamming_window(float cur_time_s, float f_2_hz, float f_1_hz, float phase_rad, float amplitude,
                                       float signal_diration_s) {
    float amplitude_scaled = 0.0f;
    float b = 0.0f;
    if(0.0f < signal_diration_s) {
        float bandwith_hz = f_2_hz - f_1_hz;
        b = bandwith_hz / signal_diration_s;

        // float cur_time_s = ((float)time_us) / 1000000.0f;

        float argument_rad = phase_rad;
        argument_rad += M_2PI * (f_1_hz * cur_time_s + (b * cur_time_s * cur_time_s) / 2.0f);

        if(signal_diration_s < cur_time_s) {
            amplitude = 0.0f;
        }

        float cos_arg = (M_2PI * cur_time_s) / signal_diration_s;
        float hamming_window = 0.46f - 0.46f * cosf(cos_arg);
        amplitude_scaled = amplitude * sinf(argument_rad) * hamming_window;
    }
    return amplitude_scaled;
}

float calc_pwm_sample(uint64_t time_us, float freq, float cur_phase_ms, float des_amplitude, float duty_cycle_percent,
                      float offset) {
    float line_val = 0.0f;
    float saw_val = 0.0f;

    if(100.0f < duty_cycle_percent) {
        duty_cycle_percent = 100.0f;
    }
    if(duty_cycle_percent < 0.0f) {
        duty_cycle_percent = 0.0f;
    }
    float cur_time_ms = ((float)time_us) / 1000.0f;
    line_val = ((((float)cur_time_ms) + ((float)cur_phase_ms)) / 1000.0f) * freq; /*tune frequency*/
    saw_val = fmodf(line_val, 1.0f);                                              /*tune DutyCycle*/

    float magnitude = offset;
    float val = (((1.0f - ((100.0f - duty_cycle_percent)) / 100.0f)) - saw_val); /*tune DutyCycle*/
    if(0.0 < val) {
        magnitude += des_amplitude;
    }

    return magnitude;
}

uint8_t calc_pwm_sample_num(uint64_t time_us, uint32_t period_ms, float duty, int32_t phase_ms) {
    uint8_t val = 0;
    if(100.0f < duty) {
        duty = 100.0f;
    }
    float cur_time_ms = ((float)time_us) / 1000.0f;
    int32_t time_saw = (phase_ms + ((int32_t)cur_time_ms)) % period_ms;
    int32_t treshold = (int32_t)(((float)(period_ms)*duty) / 100.0f);
    if(treshold < time_saw) {
        val = 0;
    } else {
        val = 1;
    }

    return val;
}

bool spot_change(uint8_t val) {
    bool res = false;
    static uint8_t prev_val = 0;
    if(val != prev_val) {
        res = true;
    }
    prev_val = val;
    return res;
}

uint32_t int_pow_slow(uint32_t base, uint32_t exp) {
    uint32_t result = base;
    uint32_t i = 0;
    if(0 == exp) {
        result = 1;
    } else {
        for(i = 0; i < (exp - 1); i++) {
            result *= base;
        }
    }
    return result;
}

/*
 see https://habr.com/ru/articles/851920/
  result = base^exponenta
 */
uint32_t int_pow_fast(const uint32_t base, const uint32_t exponenta) {
    uint32_t result = 0;
    uint32_t n = exponenta;
    if(0 == n) {
        result = 1;
    } else {
        result = 1;
        uint32_t current_product = base;
        /*run through all the exponenta bits*/
        while(0 < n) {
            if(1 & n) {
                /* found a factor of 2 different from 1 in our exponenta decomposition*/
                result *= current_product;
            }
            current_product *= current_product;
            n = n >> 1;
        }
    }

    return result;
}

uint32_t int_pow(const uint32_t base, const uint32_t exponenta) {
    uint32_t result = int_pow_fast(base, exponenta);
    return result;
}

#define PI_VAL 3.14159
#ifdef HAS_AOA
float aoa_calc_deg(float phase, float wavelength, float dist) {
    float angle_of_arrival_deg = 0.0f;
    float arg = (wavelength * phase) / (2.0f * M_PI * dist);
    angle_of_arrival_deg = RAD_2_DEG(asinf(arg));
    return angle_of_arrival_deg;
}
#endif /*HAS_AOA*/

bool is_prime(uint32_t number) {
    if(number < 2)
        return false;
    if(2 == number)
        return true;
    if(0 == (number % 2))
        return false;
    for(uint32_t i = 3; (i * i) <= number; i += 2) {
        if(0 == (number % i)) {
            return false;
        }
    }
    return true;
}

float calc_fence_sample(uint64_t time_us, float in_frequency, float in_phase_ms, float des_amplitude, float in_offset) {
    float argument = 0.0f;
    float amplitude = 0.0f;
    float amplitude_scaled = 0.0f;
    float cur_time_ms = ((float)time_us) / 1000.0f;
    argument = ((cur_time_ms + in_phase_ms) / 1000.0f) * in_frequency; /*tune frequency*/

    amplitude = 1.0f - fabsf(fmodf((float)argument * 2.0f, 2.0f) - 1.0f);
    amplitude_scaled = des_amplitude * amplitude + in_offset;

    return amplitude_scaled;
}

float calc_saw_sample(uint64_t time_us, float in_frequency, float in_phase_ms, float des_amplitude, float in_offset) {
    float argument = 0.0f;
    float amplitude = 0.0f;
    float amplitude_scaled = 0.0f;
    float cur_time_ms = ((float)time_us) / 1000.0f;
    argument = ((cur_time_ms + in_phase_ms) / 1000.0f) * in_frequency; /*tune frequency*/

    amplitude = (float)des_amplitude * fmodf((float)argument, (float)1.0f);
    amplitude_scaled = amplitude + in_offset;

    return amplitude_scaled;
}

bool check_continuity(uint64_t new_val, uint64_t* out_prev_val) {
    bool res = false;
    static uint64_t val_prev = 0;
    *out_prev_val = val_prev;
    if(val_prev <= new_val) {
        res = true;
    } else {
        res = false;
    }
    val_prev = new_val;
    return res;
}

uint32_t freq2period_ms(float freq_hz) {
    uint32_t period_ms = 0;
    bool res = true;
#ifdef HAS_FLOAT_UTILS
    res = is_float_equal_absolute(0.0f, freq_hz, 0.0001f);
#endif
    if(res) {
#ifdef HAS_LOG
        LOG_ERROR(MATH, "DivZero");
#endif
        period_ms = 100.0f;
    } else {
        period_ms = 1000.0f / freq_hz;
    }
    return period_ms;
}

uint8_t toggle_val(uint8_t val) {
    uint8_t out = 0;
    switch(val) {
    case 0:
        out = 1;
        break;
    case 1:
        out = 0;
        break;
    default:
        out = 0;
        break;
    }
    return out;
}

float calc_percent_s(size_t numerator, size_t denominator) {
    float percent = 0.0;
    if(denominator) {
        percent = (100.0 * ((float)numerator)) / ((float)denominator);
    } else {
#ifdef HAS_LOG
        LOG_ERROR(MATH, "DivZero");
#endif
    }
    return percent;
}

uint32_t calc_percent_uu(uint32_t numerator, uint32_t denominator) {
    uint32_t percent_u = 0.0;
    if(denominator) {
        percent_u = 100 * numerator / denominator;
    } else {
#ifdef HAS_LOG
        LOG_ERROR(MATH, "DivZero");
#endif
    }
    return percent_u;
}

float rad_2_deg(float rad) {
    float deg = 0.0;
    deg = ((rad * 180.0) / M_PI);
#ifdef HAS_LOG
    LOG_DEBUG(MATH, "%f_Rad=%f_Deg", rad, deg);
#endif
    return deg;
}

float rad_to_deg_f(float rad) {
    float deg = 0.0f;
    deg = ((rad * 180.0f) / M_PI);
#ifdef HAS_LOG
    LOG_DEBUG(MATH, "%f_Rad=%f_Deg", rad, deg);
#endif
    return deg;
}

float deg_to_rad(float deg) {
    float rad = 0.0f;
    rad = (deg * M_PI / 180.0f);
    return rad;
}

uint32_t math_calc_abs(const uint32_t a, const uint32_t b) {
    uint32_t abs_u32 = 0;
    int32_t diff_signed = ((int32_t)a) - ((int32_t)b);
    abs_u32 = (uint32_t)abs((int)diff_signed);
    return abs_u32;
}

int64_t math_diod_s64(const int64_t value) {
    int64_t out = 0;
    if(0 < value) {
        out = value;
    }
    return out;
}

bool math_sum4(const uint32_t sum) {
    bool res = false;
    uint32_t cnt = 0;
    uint32_t a = 0;
    for(a = 1; a <= sum; a++) {
        uint32_t b = 0;
        for(b = 1; b <= sum; b++) {
            uint32_t c = 0;
            for(c = 1; c <= sum; c++) {
                uint32_t d = 0;
                for(d = 1; d <= sum; d++) {
                    uint32_t cur_sum = a + b + c + d;
                    if(cur_sum == sum) {
                        cnt++;
#ifdef HAS_LOG
                        LOG_INFO(MATH, "%4u: %u=%u+%u+%u+%u", cnt, sum, a, b, c, d);
#endif
                        res = true;
                    }
                }
            }
        }
    }
    return res;
}

bool math_sum3(const uint32_t sum) {
    bool res = false;
    uint32_t cnt = 0;
    uint32_t a = 0;
    for(a = 1; a <= sum; a++) {
        uint32_t b = 0;
        for(b = 1; b <= sum; b++) {
            uint32_t c = 0;
            for(c = 1; c <= sum; c++) {
                uint32_t cur_sum = a + b + c;
                if(cur_sum == sum) {
                    cnt++;
#ifdef HAS_LOG
                    LOG_INFO(MATH, "%4u: %u=%u+%u+%u", cnt, sum, a, b, c);
#endif
                    res = true;
                }
            }
        }
    }
    return res;
}

static bool math_sum4_dynamic_ll(uint32_t target, uint32_t count, uint32_t start, uint32_t* result) {
    bool res = false;
    if(4 == count) {
        if(0 == target) {
#ifdef HAS_LOG
            LOG_INFO(SYS, "%u+%u+%u+%u=", result[0], result[1], result[2], result[3]);
#endif
            res = true;
        }
    } else {
        for(uint32_t i = start; i <= target; i++) {
            result[count] = i;
            math_sum4_dynamic_ll(target - i, count + 1, i, result);
        }
    }
    return res;
}

bool math_div_n_m(uint32_t n, uint32_t m, uint32_t lim) {
    bool res = false;
#ifdef HAS_LOG
    LOG_INFO(SYS, "N:%u,M:%u,Lim:%u", n, m, lim);
#endif

    uint32_t i = 0;
    for(i = 0; i < lim; i++) {
        if(0 == i % n) {
            if(0 == i % m) {
                cli_printf("%u,", i);
                res = true;
            }
        }
    }
    return res;
}

bool math_sum4_dynamic(uint32_t target) {
    bool res = false;
    uint32_t result[4] = {0};
    res = math_sum4_dynamic_ll(target, 0, 1, result);
    return res;
}

MathParity_t math_calc_parity(const uint32_t natural) {
    MathParity_t parity = MATH_PARITY_UNDEF;
    if(natural) {
        if(1 & natural) {
            parity = MATH_PARITY_ODD;
        } else {
            parity = MATH_PARITY_EVEN;
        }
    }
    return parity;
}

/*           q
 *           |
 *     2     |   1
 * -i-----------------i
 *     3     |   4
 *           |
 *         -q
 *TODO test it
 */
uint8_t calc_quadrant_num(const int32_t i, const int32_t q) {
    uint8_t quadrant_num = 1;
    if(0 < i) {
        if(0 < q) {
            quadrant_num = 1;
        } else {
            quadrant_num = 4;
        }
    } else {
        if(0 < q) {
            quadrant_num = 2;
        } else {
            quadrant_num = 3;
        }
    }
#ifdef HAS_MATH_DEBUG
#error ererer
    LOG_DEBUG(MATH, "I:%d,Q:%d,Quad:%u", i, q, quadrant_num);
#endif
    return quadrant_num;
}

float math_log10(const float value) {
    static float value_log10 = 0.0;
    if(1.0f < value) {
        value_log10 = logf(value) / logf(10.0f);
    } else {
    }
    return value_log10;
}

static uint8_t calc_octant_in_quadrant_1(const int32_t i, const int32_t q) {
    uint8_t octant_num = 0;
    if(abs(i) < abs(q)) {
        octant_num = 2;
    } else {
        octant_num = 1;
    }
    return octant_num;
}

static uint8_t calc_octant_in_quadrant_2(const int32_t i, const int32_t q) {
    uint8_t octant_num = 0;
    if(abs(i) < abs(q)) {
        octant_num = 3;
    } else {
        octant_num = 4;
    }
    return octant_num;
}

static uint8_t calc_octant_in_quadrant_3(const int32_t i, const int32_t q) {
    uint8_t octant_num = 0;
    if(abs(i) < abs(q)) {
        octant_num = 6;
    } else {
        octant_num = 5;
    }
    return octant_num;
}

static uint8_t calc_octant_in_quadrant_4(const int32_t i, const int32_t q) {
    uint8_t octant_num = 0;
    if(abs(i) < abs(q)) {
        octant_num = 7;
    } else {
        octant_num = 8;
    }
    return octant_num;
}

uint8_t calc_octant_num(const int32_t i, const int32_t q) {
    uint8_t octant_num = 0;
    uint8_t quadrant_num = calc_quadrant_num(i, q);
    switch(quadrant_num) {
    case 1: {
        octant_num = calc_octant_in_quadrant_1(i, q);
    } break;
    case 2: {
        octant_num = calc_octant_in_quadrant_2(i, q);
    } break;
    case 3: {
        octant_num = calc_octant_in_quadrant_3(i, q);
    } break;
    case 4: {
        octant_num = calc_octant_in_quadrant_4(i, q);
    } break;
    default:
        break;
    }
#ifdef HAS_MATH_DEBUG
    LOG_DEBUG(MATH, "I:%d,Q:%d,Oct:%u", i, q, octant_num);
#endif
    return octant_num;
}

/*
 See book
 Understanding Digital Signal Processing (Richard G. Lyons)
 13.21
 */
float atan2f_approximate(const float q, const float i) {
    float deg_rad = 0.0f;
    uint8_t octant_num = calc_octant_num(i, q);
    switch(octant_num) {
    case 1:
    case 8: {
        deg_rad = (i * q) / ((i * i) + 0.28125f * q * q);
        // deg_rad = (q / i) / (1.0f + 0.28125f * (q / i) * (q / i));
    } break;

    case 2:
    case 3: {
        deg_rad = PI_DIV2 - (i * q) / ((q * q) + 0.28125f * i * i);
    } break;

    case 4:
    case 5: {
        deg_rad = M_PI_F + (i * q) / ((i * i) + 0.28125f * q * q);
    } break;

    case 6:
    case 7: {
        deg_rad = -PI_DIV2 - (i * q) / ((q * q) + 0.28125f * i * i);
    } break;

    default: {

    } break;
    }
#ifdef HAS_MATH_DEBUG
    LOG_DEBUG(MATH, "I:%f,Q:%f,Oct:%u,Ang:%f Rad", i, q, octant_num, deg_rad);
#endif
    // deg_rad = (i*q)/((i*i)+0.28125f*q*q);
    return deg_rad;
}

float logistic_function(float L, float k, float x) {
    float y = L / (1.0f + expf(-k * x));
    return y;
}
