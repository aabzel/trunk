#ifndef NAU8814_DAC_H
#define NAU8814_DAC_H

#include <stdbool.h>
#include <stdint.h>

#include "nau8814_types.h"

#ifndef HAS_NAU8814_DAC
#error "+HAS_NAU8814_DAC"
#endif

/*API*/
bool nau8814_init_dac(uint8_t num);

/*mappers*/
uint16_t NauSpkGainToCode(Gain_t gain);
Gain_t NauSpkGainCodeToGain(uint8_t code);

fGain_t NauDacGainCodeToGain(uint16_t code);
uint8_t NauGainToGainCode(fGain_t gain);


/*setters*/
bool nau8814_dac_gain_set(uint8_t num, fGain_t gain);
bool nau8814_spk_gain_set(uint8_t num, Gain_t gain);
bool nau8814_mute(uint8_t num);
bool nau8814_play_1khz(uint8_t num, SampleType_t amplitude, uint32_t duratin_ms);
bool nau8814_play_tone(uint8_t num, double freq, SampleType_t amplitude, uint32_t duration_ms);
bool nau8814_play_1khz_con(uint8_t num, SampleType_t amplitude);


/*getters*/
bool nau8814_dac_gain_get(uint8_t num, fGain_t* const gain);
bool nau8814_spk_gain_get(uint8_t num, Gain_t* const gain);

#endif /* NAU8814_DAC_H */
