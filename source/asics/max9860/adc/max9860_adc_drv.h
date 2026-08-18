#ifndef MAX9860_ADC_DRV_H
#define MAX9860_ADC_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "i2s_types.h"
#include "max9860_const.h"
#include "max9860_dep.h"
#include "max9860_types.h"

AdcGain_t AdcCode2Gain(uint8_t code);
AdcGain_t max9860_adc_output_level_get(MicChannel_t mic_channel);
Gain_t AdcOutputLevel2Gain(uint8_t adc_out_lev);
Gain_t PamCode2Gain(uint8_t pam_code);
Gain_t MicrophoneProgrammableGainAmplifierCode2Gain(uint8_t pga);
Gain_t PgamCode2Gain(uint8_t pgam_code);
Gain_t max9860_microphone_preamp_get(void);
Gain_t max9860_microphone_programmable_gain_amplifier_get(void);
SideToneGain_t Code2SideToneGain(uint8_t code);
SideToneGain_t max9860_sidetone_level_get(void);
bool is_valid_adc_gain(AdcGain_t adc_gain);
bool max9860_adc_get(MicChannel_t mic_channel);
bool max9860_adc_output_level_set(MicChannel_t mic_channel, AdcGain_t adc_gain);
bool max9860_adc_set(MicChannel_t mic_channel, bool on_off);
bool max9860_digital_audio_level_set(Gain_t gain);
bool max9860_microphone_preamp_set(Gain_t gain);
bool max9860_microphone_programmable_gain_amplifier_set(Gain_t gain);
bool max9860_sidetone_level_set(SideToneGain_t side_tone_gain);
bool max9860_sidetone_set(bool on_off);
uint8_t AdcGain2Code(AdcGain_t adc_gain);
uint8_t Gain2DvstCode(Gain_t side_tone_gain);
uint8_t Gain2PamCode(Gain_t gain);
uint8_t Gain2PgamCode(Gain_t gain);

#endif /* MAX9860_ADC_DRV_H */
