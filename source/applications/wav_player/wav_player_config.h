#ifndef WAV_PLAYER_CONFIG_H
#define WAV_PLAYER_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "wav_player_types.h"
#include "wav_player_dep.h"

//#define PLAYER_MEM_SIZE 2048
#define PLAYER_MEM_HALF_SIZE (PLAYER_MEM_SIZE/2)

extern const WavPlayerConfig_t WavPlayerConfig[];
extern WavPlayerHandle_t WavPlayerInstance[];

uint32_t wav_player_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* WAV_PLAYER_CONFIG_H */
