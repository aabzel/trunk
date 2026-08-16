#include "barker_code.h"

#include "float_diag.h"
#include "log.h"
#include "math_const.h"

/*  Length                       Codes                   Sidelobe level ratio[15][16] */
const int8_t BarkerCode_2[2] = {1, -1};    /*  â6 dB   */
const int8_t BarkerCode_2_2[2] = {1, 1};   /*  â6 dB   */
const int8_t BarkerCode_3[3] = {1, 1, -1}; /*   â9.5 dB  */
const int8_t BarkerCode_4[4] = {
    1,
    1,
    -1,
    1,
};
const int8_t BarkerCode_4_2[4] = {1, 1, 1, -1};                               /*   -12 dB  */
const int8_t BarkerCode_5[5] = {1, 1, 1, -1, 1};                              /*  -14 dB  */
const int8_t BarkerCode_7[7] = {1, 1, 1, -1, -1, 1, -1};                      /*    -16.9 dB  */
const int8_t BarkerCode_11[11] = {1, 1, 1, -1, -1, -1, 1, -1, -1, 1, -1};     /*     20.8 dB  */
const int8_t BarkerCode_13[13] = {1, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, -1, 1}; /*    22.3 dB  */

int8_t barker_code_13_modilator(float time_s, float carrier_period_s, uint32_t periods_per_chip) {
    int8_t modulator = 0;
    float time_part_s = carrier_period_s * ((float)periods_per_chip);
    uint32_t part = (uint32_t)(time_s / time_part_s);
    if(part <= 12) {
        modulator = BarkerCode_13[part];
    } else {
        modulator = 0;
    }
    LOG_DEBUG(BARKER_CODE, "UpTime:%s,Part:%u,modulator:%d", FloatToStr(time_s, 2), part, modulator);
    return modulator;
}

float barker13_signal_duration(float carrier_frequency_hz, uint32_t periods_per_chip) {
    float carrier_period_s = 1.0f / carrier_frequency_hz;
    float signal_diration_s = ((float)(13 * periods_per_chip)) * carrier_period_s;
    return signal_diration_s;
}

float calc_barker13_sample(float time_s, float amplitude, float carrier_frequency_hz, uint32_t periods_per_chip) {
    float amplitude_scaled = 0.0f;
    float argument = 0.0;
    float signal_diration_s = barker13_signal_duration(carrier_frequency_hz, periods_per_chip);
    if(time_s <= signal_diration_s) {
        float signal = 0.0;
        float carrier_period_s = 1.0f / carrier_frequency_hz;
        float modulator = (float)barker_code_13_modilator(time_s, carrier_period_s, periods_per_chip);
        float lineVal = (time_s)*carrier_frequency_hz; /*tune frequency*/
        argument = 2.0f * M_PI * lineVal;
        signal = (float)sinf((float)argument);
        amplitude_scaled = amplitude * signal * modulator;
    } else {
        amplitude_scaled = 0.0;
    }

    return amplitude_scaled;
}
