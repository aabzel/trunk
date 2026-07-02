#ifndef WAV_PLAYER_DIAG_H
#define WAV_PLAYER_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "wav_player_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_WAV_PLAYER
#error "+HAS_WAV_PLAYER"
#endif

#ifndef HAS_WAV_PLAYER_DIAG
#error "+HAS_WAV_PLAYER_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool wav_player_diag(void);
bool wav_player_diag_one(uint8_t num);
const char* WavPlayerConfigToStr(const WavPlayerConfig_t* const Config);
const char* WavPlayerNodeToStr(const WavPlayerHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* WAV_PLAYER_DIAG_H  */
