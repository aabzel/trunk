#include "utils_math.h"

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

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

float math_sign_f(const float val) {
    float out_val = 0.0;
    if(0.0 < val) {
        out_val = 1.0;
    }
    if(val < 0.0) {
        out_val = -1.0;
    }
    return out_val;
}

float math_sign(const float val) {
    float out_val = 0.0;
    if(0.0 < val) {
        out_val = 1.0;
    }
    if(val < 0.0) {
        out_val = -1.0;
    }
    return out_val;
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

float lo_calc_cos_sample(float time_s, float frequency, float phase_rad, float des_amplitude, float in_offset) {
#ifdef HAS_LOG
    LOG_DEBUG(MATH, "Cos,Freq:%f,Phase:%f rad,Amp:%f,OffSet:%f", frequency, phase_rad, des_amplitude, in_offset);
#endif
    float argument = 2.0 * M_PI * time_s * frequency + phase_rad;
    float amplitude = (float)cos((float)argument);
    float amplitude_scaled = (des_amplitude * amplitude) + in_offset;
#ifdef HAS_LOG
    LOG_DEBUG(MATH, "Time:%f,arg:%f,A:%f,SinSample: %7.3f", time_s, argument, amplitude, amplitude_scaled);
#endif
    return amplitude_scaled;
}

float lo_calc_sin_sample(float time_s, float frequency, float phase_rad, float des_amplitude, float in_offset) {
#ifdef HAS_LOG
    LOG_DEBUG(MATH, "Sin,Freq:%f,Phase:%f rad,Amp:%f,OffSet:%f", frequency, phase_rad, des_amplitude, in_offset);
#endif
    float argument = 2.0 * M_PI * time_s * frequency + phase_rad;
    float amplitude = (float)sin((float)argument);
    float amplitude_scaled = (des_amplitude * amplitude) + in_offset;
#ifdef HAS_LOG
    LOG_DEBUG(MATH, "Time:%f,arg:%f,A:%f,SinSample: %7.3f", time_s, argument, amplitude, amplitude_scaled);
#endif
    return amplitude_scaled;
}

float math_calc_sin_sample(float time_s, float frequency, float phase_ms, float des_amplitude, float in_offset) {
    float lineVal = 0.0;
#ifdef HAS_LOG
    LOG_DEBUG(MATH, "Sin,Time:%f,Freq:%f,Phase:%f,Amp:%f,OffSet:%f", time_s, frequency, phase_ms, des_amplitude,
              in_offset);
#endif
    float argument = 0.0;
    float amplitude = 0.0;
    float amplitude_scaled = 0.0;
    float cur_time_ms = time_s * 1000.0;
#ifdef HAS_LOG
    LOG_PARN(MATH, "T:%u ms", cur_time_ms);
#endif
    lineVal = ((cur_time_ms + phase_ms) / 1000.0) * frequency; /*tune frequency*/
#ifdef HAS_LOG
    LOG_PARN(MATH, "lineVal:%f", lineVal);
#endif
    argument = 2.0 * M_PI * lineVal;
#ifdef HAS_LOG
    LOG_PARN(MATH, "arg:%f", argument);
#endif
#ifdef HAS_ZEPHYR
    amplitude = (float)arm_sin_f32((float32_t)argument);
#else
    amplitude = (float)sin((float)argument);
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

float calc_sin_sample(uint64_t time_us, float frequency, float phase_ms, float des_amplitude, float in_offset) {
    float lineVal = 0.0;
#ifdef HAS_LOG
    LOG_DEBUG(MATH, "Sin T:%u F:%f P:%f A:%f O:%f", time_us, frequency, phase_ms, des_amplitude, in_offset);
#endif
    float argument = 0.0;
    float amplitude = 0.0;
    float amplitude_scaled = 0.0;
    float cur_time_ms = ((float)time_us) / 1000.0;
#ifdef HAS_LOG
    LOG_PARN(MATH, "T:%u ms", cur_time_ms);
#endif
    lineVal = ((cur_time_ms + phase_ms) / 1000.0) * frequency; /*tune frequency*/
#ifdef HAS_LOG
    LOG_PARN(MATH, "lineVal:%f", lineVal);
#endif
    argument = 2.0 * M_PI * lineVal;
#ifdef HAS_LOG
    LOG_PARN(MATH, "arg:%f", argument);
#endif
#ifdef HAS_ZEPHYR
    amplitude = (float)arm_sin_f32((float32_t)argument);
#else
    amplitude = (float)sin((float)argument);
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

float calc_dtmf_sample(uint64_t time_us, float frequency1, float frequency2, float phase_ms, float des_amplitude,
                        float in_offset) {
    // float lineVal = 0.0;
#ifdef HAS_LOG
    LOG_DEBUG(MATH, "DualTone T:%u,F1:%f, F2:%f, P:%f, A:%f, O:%f", time_us, frequency1, frequency2, phase_ms,
              des_amplitude, in_offset);
#endif
    float amplitude_scaled = 0.0;
    float tone1 = calc_sin_sample(time_us, frequency1, phase_ms, des_amplitude, in_offset);
    float tone2 = calc_sin_sample(time_us, frequency2, phase_ms, des_amplitude, in_offset);
    amplitude_scaled = tone1 + tone2;

    return amplitude_scaled;
}

/*
  time_us - up time in us
  signal_diration_s - signal duration
  f_2_hz - maximum value of signal frequency.
  f_1_hz - initial signal frequency
  des_amplitude - signal amplitude
  phase_rad -  initial phase.
 */
float calc_chirp_sample(uint64_t time_us, float f_2_hz, float f_1_hz, float phase_rad, float amplitude,
                         float signal_diration_s) {
    float amplitude_scaled = 0.0;
    float b = 0;
    if(0.0 < signal_diration_s) {
        float bandwith_hz = f_2_hz - f_1_hz;
        b = bandwith_hz / signal_diration_s;
    }

    float cur_time_s = ((float)time_us) / 1000000.0;

    float argument_rad = phase_rad;
    argument_rad += M_2PI * (f_1_hz * cur_time_s + (b * cur_time_s * cur_time_s) / 2.0);

    if(signal_diration_s < cur_time_s) {
        amplitude = 0.0;
    }

    float cos_arg = (M_2PI * cur_time_s) / signal_diration_s;
    float hamming_window = 0.46 - 0.46 * cos(cos_arg);
    amplitude_scaled = amplitude * sin(argument_rad) * hamming_window;
    return amplitude_scaled;
}

float calc_pwm_sample(uint64_t time_us, float freq, float cur_phase_ms, float des_amplitude,
                       float duty_cycle_percent, float offset) {
    float line_val = 0.0;
    float saw_val = 0.0;

    if(100.0 < duty_cycle_percent) {
        duty_cycle_percent = 100.0;
    }
    if(duty_cycle_percent < 0.0) {
        duty_cycle_percent = 0.0;
    }
    float cur_time_ms = ((float)time_us) / 1000.0;
    line_val = ((((float)cur_time_ms) + ((float)cur_phase_ms)) / 1000.0) * freq; /*tune frequency*/
    saw_val = fmodf(line_val, 1.0);                                                /*tune DutyCycle*/

    float magnitude = offset;
    float val = (((1.0 - ((100.0 - duty_cycle_percent)) / 100.0)) - saw_val); /*tune DutyCycle*/
    if(0.0 < val) {
        magnitude += des_amplitude;
    }

    return magnitude;
}

uint8_t calc_pwm_sample_num(uint64_t time_us, uint32_t period_ms, uint8_t duty, int32_t phase_ms) {
    uint8_t val = 0;
    if(100 < duty) {
        duty = 100;
    }
    float cur_time_ms = ((float)time_us) / 1000.0;
    int32_t time_saw = (phase_ms + ((int32_t)cur_time_ms)) % period_ms;
    int32_t treshold = (period_ms * ((uint32_t)duty)) / 100;
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

uint32_t int_pow(uint32_t base, uint32_t exp) {
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

#define PI_VAL 3.14159
#ifdef HAS_AOA
float aoa_calc_deg(float phase, float wavelength, float dist) {
    float angle_of_arrival_deg = 0.0;
    float arg = (wavelength * phase) / (2 * M_PI * dist);
    angle_of_arrival_deg = RAD_2_DEG(asin(arg));
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

float calc_fence_sample(uint64_t time_us, float in_frequency, float in_phase_ms, float des_amplitude,
                         float in_offset) {
    float argument = 0.0f;
    float amplitude = 0.0f;
    float amplitude_scaled = 0.0f;
    float cur_time_ms = ((float)time_us) / 1000.0f;
    argument = ((cur_time_ms + in_phase_ms) / 1000.0f) * in_frequency; /*tune frequency*/

    amplitude = 1.0f - fabs(fmod((float)argument * 2.0f, 2.0f) - 1.0f);
    amplitude_scaled = des_amplitude * amplitude + in_offset;

    return amplitude_scaled;
}

float calc_saw_sample(uint64_t time_us, float in_frequency, float in_phase_ms, float des_amplitude,
                       float in_offset) {
    float argument = 0.0f;
    float amplitude = 0.0f;
    float amplitude_scaled = 0.0f;
    float cur_time_ms = ((float)time_us) / 1000.0f;
    argument = ((cur_time_ms + in_phase_ms) / 1000.0f) * in_frequency; /*tune frequency*/

    amplitude = (float)des_amplitude * fmod((float)argument, (float)1.0f);
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
    res = is_float_equal_absolute(0.0, freq_hz, 0.0001);
#endif
    if(res) {
        LOG_ERROR(MATH, "DivZero");
        period_ms = 100.0;
    } else {
        period_ms = 1000.0 / freq_hz;
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
        LOG_ERROR(MATH, "DivZero");
    }
    return percent;
}

uint32_t calc_percent_uu(uint32_t numerator, uint32_t denominator) {
    uint32_t percent_u = 0.0;
    if(denominator) {
        percent_u = 100 * numerator / denominator;
    } else {
        LOG_ERROR(MATH, "DivZero");
    }
    return percent_u;
}

float rad_2_deg(float rad) {
    float deg = 0.0;
    deg = ((rad * 180.0) / M_PI);
    LOG_DEBUG(MATH, "%f_Rad=%f_Deg", rad, deg);
    return deg;
}

float rad_to_deg_f(float rad) {
    float deg = 0.0;
    deg = ((rad * 180.0) / M_PI);
    LOG_DEBUG(MATH, "%f_Rad=%f_Deg", rad, deg);
    return deg;
}

float deg_to_rad(float deg) {
    float rad = 0.0;
    rad = (deg * M_PI / 180.0);
    return rad;
}
