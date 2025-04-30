#ifndef AUDIO_CONFIG_H
#define AUDIO_CONFIG_H

#ifdef HAS_SW_AUDIO_CODEC
#include "sw_codec_select.h"
#endif

#define CONFIG_AUDIO_SAMPLE_RATE_HZ 48000
#define CONFIG_AUDIO_BIT_DEPTH_OCTETS 2
#define CONFIG_AUDIO_FRAME_DURATION_US 10000
#define CONFIG_AUDIO_BIT_DEPTH_BITS 16
#define CONFIG_SW_CODEC_OVERRIDE_PLC 0
#define CONFIG_AUDIO_HEADSET_CHANNEL 0

extern struct sw_codec_config sw_codec_cfg;

#endif /* AUDIO_CONFIG_H */
