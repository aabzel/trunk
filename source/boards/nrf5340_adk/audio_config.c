#include "audio_config.h"

#include "sw_codec_select.h"
#include "lc3_config.h"

struct sw_codec_config sw_codec_cfg={
		.sw_codec=SW_CODEC_LC3,
		.decoder={
				.enabled=true,
				.channel_mode=SW_CODEC_MONO,
				.audio_ch=AUDIO_CH_L,
		},
		.encoder={
				.enabled=true,
				.bitrate=CONFIG_LC3_BITRATE,
				.channel_mode=SW_CODEC_MONO,
				.audio_ch=AUDIO_CH_L,
		},
		.initialized=false,
};
