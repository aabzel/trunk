#include "local_oscillator_mcal.h"

#include "log.h"

int32_t cos4_int(int32_t n, int32_t phase) {
    static const int32_t cos4_table[4] = {1, 0, -1, 0};

    int32_t idx = n + phase;
    // Приводим к [0,3] через битовую маску (только для положительных idx)
    // Для отрицательных нужна дополнительная обработка
    int32_t rem = idx % 4;
    if(rem < 0) {
        rem += 4;
    }

    return cos4_table[rem];
}

int32_t pwm_cos4_int(int32_t n, int32_t phase) {
    static const int32_t cos4_table[4] = {1, -1, -1, 1};
    int32_t idx = n + phase;
    int32_t rem = idx % 4;
    if(rem < 0) {
        rem += 4;
    }

    return cos4_table[rem];
}

int32_t pwm_sin4_int(int32_t n, int32_t phase) {
    static const int32_t sin4_table[4] = {1, 1, -1, -1};

    int32_t idx = n + phase;
    // Приводим к [0,3] через битовую маску (только для положительных idx)
    // Для отрицательных нужна дополнительная обработка
    int32_t rem = idx % 4;
    if(rem < 0) {
        rem += 4;
    }

    return sin4_table[rem];
}

int32_t sin4_int(int32_t n, int32_t phase) {
    static const int32_t sin4_table[4] = {0, 1, 0, -1};

    int32_t idx = n + phase;
    // Приводим к [0,3] через битовую маску (только для положительных idx)
    // Для отрицательных нужна дополнительная обработка
    int32_t rem = idx % 4;
    if(rem < 0) {
        rem += 4;
    }

    return sin4_table[rem];
}

float lo_calc_sin_sample(float time_s, float frequency, float phase_rad, float des_amplitude, float in_offset) {
#ifdef HAS_LOG
    LOG_DEBUG(MATH, "Sin,Freq:%f,Phase:%f rad,Amp:%f,OffSet:%f", frequency, phase_rad, des_amplitude, in_offset);
#endif
    float argument = 2.0f * M_PI * time_s * frequency + phase_rad;
    float amplitude = (float)sinf((float)argument);
    float amplitude_scaled = (des_amplitude * amplitude) + in_offset;
#ifdef HAS_LOG
    LOG_DEBUG(MATH, "Time:%f,arg:%f,A:%f,SinSample: %7.3f", time_s, argument, amplitude, amplitude_scaled);
#endif
    return amplitude_scaled;
}

float lo_calc_cos_sample(float time_s, float frequency, float phase_rad, float des_amplitude, float in_offset) {
#ifdef HAS_LOG
    LOG_DEBUG(MATH, "Cos,Freq:%f,Phase:%f rad,Amp:%f,OffSet:%f", frequency, phase_rad, des_amplitude, in_offset);
#endif
    float argument = 2.0f * M_PI * time_s * frequency + phase_rad;
    float amplitude = (float)cosf((float)argument);
    float amplitude_scaled = (des_amplitude * amplitude) + in_offset;
#ifdef HAS_LOG
    LOG_DEBUG(MATH, "Time:%f,arg:%f,A:%f,SinSample: %7.3f", time_s, argument, amplitude, amplitude_scaled);
#endif
    return amplitude_scaled;
}
