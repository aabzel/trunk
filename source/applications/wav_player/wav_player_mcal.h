#ifndef WAV_PLAYER_MCAL_H
#define WAV_PLAYER_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "wav_player_config.h"
#include "wav_player_types.h"

#ifdef HAS_WAV_PLAYER_DIAG
#include "wav_player_diag.h"
#endif

/* API */
WavPlayerHandle_t* WavPlayerGetNode(uint8_t num);
const WavPlayerConfig_t* WavPlayerGetConfig(uint8_t num);
bool WavPlayerIsValidConfig(const WavPlayerConfig_t* const Config);

#ifdef HAS_WAV_PLAYER_CUSTOM
const WavPlayerInfo_t* WavPlayerGetInfo(uint8_t num);
#endif

bool wav_player_mcal_init(void);
bool wav_player_init_custom(void);
bool wav_player_init_common(const WavPlayerConfig_t* const Config, WavPlayerHandle_t* const Node);
bool wav_player_init_node(WavPlayerHandle_t* const Node);
bool wav_player_init_one(uint8_t num);

bool wav_player_proc_one(uint8_t num);
bool wav_player_proc(void);

/*setters*/
bool wav_player_play_file(const uint8_t num, const char * const file_name);
bool wav_player_stop(const uint8_t num);

/*getters*/

#ifdef __cplusplus
}
#endif

#endif /* WAV_PLAYER_MCAL_H */
