#ifndef NAU8814_ADC_H
#define NAU8814_ADC_H

#include <stdbool.h>
#include <stdint.h>

#include "nau8814_const.h"
#include "nau8814_dep.h"
#include "nau8814_types.h"

/*misc*/
float PgaGainCodeToValue(uint8_t code);
uint8_t NauGainToPgaGainCode(float gain);
BoostGainCode_t NauGainToPmicGainCode(Gain_t p_mic_gain);
Gain_t BstGainCodeToValue(BoostGainCode_t code);
bool nau8814_init_adc(uint8_t num);

/*setters*/
bool nau8814_adc_ctrl(uint8_t num, bool adc_on);
bool nau8814_aux_gain_set(uint8_t num, Gain_t aux_gain);
bool nau8814_pga_gain_set(uint8_t num, float pga_gain);
bool nau8814_p_mic_gain_set(uint8_t num, Gain_t p_mic_gain);

/*getters*/
bool nau8814_listen(uint8_t num, uint32_t des_duration_ms);
bool nau8814_adc_get(uint8_t num, bool* const adc_on);
bool nau8814_p_mic_gain_get(uint8_t num, Gain_t* const p_mic_gain);
bool nau8814_pga_gain_get(uint8_t num, float* const pga_gain);
bool nau8814_aux_gain_get(uint8_t num, Gain_t* const aux_gain);

#endif /* NAU8814_ADC_H */
