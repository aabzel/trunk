#ifndef SOUND_RECORDER_MCAL_H
#define SOUND_RECORDER_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "sound_recorder_config.h"
#include "sound_recorder_types.h"
#include "wav_types.h"

#ifdef HAS_SOUND_RECORDER_DIAG
#include "sound_recorder_diag.h"
#endif

/* API */
SoundRecorderHandle_t* SoundRecorderGetNode(uint8_t num);
const SoundRecorderConfig_t* SoundRecorderGetConfig(uint8_t num);
bool SoundRecorderIsValidConfig(const SoundRecorderConfig_t* const Config);

#ifdef HAS_SOUND_RECORDER_CUSTOM
const SoundRecorderInfo_t* SoundRecorderGetInfo(uint8_t num);
#endif

bool sound_recorder_mcal_init(void);
bool sound_recorder_init_custom(void);
bool sound_recorder_init_common(const SoundRecorderConfig_t* const Config, SoundRecorderHandle_t* const Node);
bool sound_recorder_init_node(SoundRecorderHandle_t* const Node);
bool sound_recorder_init_one(uint8_t num);
bool sound_recorder_is_valid_num(uint8_t num);

bool sound_recorder_proc_one(uint8_t num);
bool sound_recorder_proc(void);

/*setters*/
bool sound_rec_fix_part(SoundRecorderHandle_t* Node, uint32_t sam_index) ;
bool sound_recorder_fs_set(const uint8_t num, const uint32_t sample_freq_hz);
bool sound_recorder_test_start(const uint8_t num, float duration_s);
bool sound_recorder_start(const uint8_t num, const char* const file_name,  const float duration_s) ;
bool sound_recorder_compose_wav_header(const SoundRecorderHandle_t* const Rec, WavHeader_t* const Header);

/*getters*/

#ifdef __cplusplus
}
#endif

#endif /* SOUND_RECORDER_MCAL_H */
