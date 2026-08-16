#ifndef BARKER_CODE_H
#define BARKER_CODE_H

#include <stdint.h>

extern const int8_t BarkerCode_2[2];
extern const int8_t BarkerCode_2_2[2];
extern const int8_t BarkerCode_3[3];
extern const int8_t BarkerCode_4[4];
extern const int8_t BarkerCode_5[5];
extern const int8_t BarkerCode_7[7];
extern const int8_t BarkerCode_11[11];
extern const int8_t BarkerCode_13[13];

float barker13_signal_duration(float carrier_frequency_hz, uint32_t periods_per_chip);
int8_t barker_code_13_modilator(float time_s, float carrier_period_s, uint32_t periods_per_chip);
float calc_barker13_sample(float time_s, float amplitude, float carrier_frequency_hz, uint32_t periods_per_chip) ;

#endif /* BARKER_CODE_H */
