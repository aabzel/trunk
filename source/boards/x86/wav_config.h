#ifndef WAV_CONFIG_H
#define WAV_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "wav_types.h"

extern const WavConfig_t WavConfig[];
extern WavHandle_t WavInstance[];

uint32_t wav_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /*WAV_CONFIG_H*/
