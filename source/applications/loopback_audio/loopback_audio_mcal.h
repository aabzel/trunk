#ifndef LOOPBACK_AUDIO_MCAL_H
#define LOOPBACK_AUDIO_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "loopback_audio_config.h"
#include "loopback_audio_types.h"

#ifdef HAS_LOOPBACK_AUDIO_DIAG
#include "loopback_audio_diag.h"
#endif

/* API */
LoopbackAudioHandle_t* LoopbackAudioGetNode(uint8_t num);
const LoopbackAudioConfig_t* LoopbackAudioGetConfig(uint8_t num);
bool LoopbackAudioIsValidConfig(const LoopbackAudioConfig_t* const Config);

#ifdef HAS_LOOPBACK_AUDIO_CUSTOM
const LoopbackAudioInfo_t* LoopbackAudioGetInfo(uint8_t num);
#endif

bool loopback_audio_mcal_init(void);
bool loopback_audio_init_custom(void);
bool loopback_audio_init_common(const LoopbackAudioConfig_t* const Config, LoopbackAudioHandle_t* const Node);
bool loopback_audio_init_node(LoopbackAudioHandle_t* const Node);
bool loopback_audio_init_one(uint8_t num);

bool loopback_audio_proc_one(uint8_t num);
bool loopback_audio_proc(void);

/*setters*/
bool loopback_audio_rec_test(const uint8_t num, const float rec_duration_s);
bool loopback_audio_rec_file(const uint8_t num, const char* const RecFileName, const float rec_duration_s);
bool loopback_audio_play_file(const uint8_t num, const char* const PlayFileName);
bool loopback_audio_play_rec_file(uint8_t num, char* PlayFileName, char* RecFileName) ;
bool loopback_audio_i2s_num_set(uint8_t num, uint8_t i2s_num) ;

/*getters*/
bool loopback_audio_is_valid_num(uint8_t num);
uint8_t loopback_audio_i2s_num_get(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* LOOPBACK_AUDIO_MCAL_H */
