#ifndef LOOPBACK_AUDIO_DIAG_H
#define LOOPBACK_AUDIO_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "loopback_audio_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_LOOPBACK_AUDIO
#error "+HAS_LOOPBACK_AUDIO"
#endif

#ifndef HAS_LOOPBACK_AUDIO_DIAG
#error "+HAS_LOOPBACK_AUDIO_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool loopback_audio_diag(void);
bool loopback_audio_diag_one(uint8_t num);
bool loopback_audio_raw_reg_diag(uint8_t num);
const char* LoopbackAudioConfigToStr(const LoopbackAudioConfig_t* const Config);
const char* LoopbackAudioNodeToStr(const LoopbackAudioHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* LOOPBACK_AUDIO_DIAG_H  */
