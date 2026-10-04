#ifndef WAV_CONFIG_H
#define WAV_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "wav_types.h"

typedef enum{
    WAV_NUM_READ,
    WAV_NUM_WRITE,
    WAV_NUM_GENERATE,
    WAV_NUM_CNT,
}WavLegalNums_t;

extern const WavConfig_t WavConfig[];
extern WavHandle_t WavInstance[];

uint32_t wav_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /*WAV_CONFIG_H*/
