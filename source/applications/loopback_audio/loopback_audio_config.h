#ifndef LOOPBACK_AUDIO_CONFIG_H
#define LOOPBACK_AUDIO_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "loopback_audio_types.h"
#include "loopback_audio_dep.h"

#define LOOPBACK_MEM_SAM_CNT 4096

extern const LoopbackAudioConfig_t LoopbackAudioConfig[];
extern LoopbackAudioHandle_t LoopbackAudioInstance[];

uint32_t loopback_audio_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* LOOPBACK_AUDIO_CONFIG_H */
