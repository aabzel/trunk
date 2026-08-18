#ifndef MAX9860_SPEAKER_DRV_H
#define MAX9860_SPEAKER_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "audio_types.h"
#include "max9860_const.h"
#include "max9860_dep.h"
#include "max9860_types.h"

#ifndef HAS_MAX9860_DAC
#error "+HAS_MAX9860_DAC"
#endif

bool max9860_voice_filter_set(Converter_t converter, DigitalFilter_t digital_filter);
bool is_valid_voice_filter(DigitalFilter_t digital_filter);
bool max9860_dac_set(bool on_off);
bool max9860_dac_get(void);
bool max9860_attenuation_set(Gain_t gain);
bool max9860_play_1kHz_tone(double amplitude, double phase_ms);
bool max9860_play_1kHz_tone_limited(double amplitude, double phase_ms, uint32_t duratin_ms);
bool max9860_dac_gain_set(Gain_t gain);
bool max9860_volume_set(Gain_t volume);
bool max9860_play_infinite(double freq, int16_t amp);
bool max9860_stereo_get();
bool max9860_stereo_set(bool on_off);
DigitalFilter_t max9860_voice_filter_get(Converter_t converter);
Gain_t AdcSideToneCode2Gain(uint8_t dvst_code);
Gain_t GvgCode2Gain(DacGainCode_t dvg);
Gain_t max9860_attenuation_get(void);
Gain_t max9860_volume_get(void);
Gain_t max9860_dac_gain_get(void);
Gain_t DacLevelAttenuation2Gain(uint8_t code);
uint8_t DvaGain2Code(Gain_t gain);
uint8_t Gain2DvstCode(Gain_t side_tone_gain);

#endif /* MAX9860_SPEAKER_DRV_H */
