#ifndef SOUND_RECORDER_DIAG_H
#define SOUND_RECORDER_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "sound_recorder_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_SOUND_RECORDER
#error "+HAS_SOUND_RECORDER"
#endif

#ifndef HAS_SOUND_RECORDER_DIAG
#error "+HAS_SOUND_RECORDER_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool sound_recorder_stop_report(const SoundRecorderHandle_t* const Node);
bool sound_recorder_diag(void);
bool sound_recorder_diag_one(uint8_t num);
bool sound_recorder_raw_reg_diag(uint8_t num);
const char* SoundRecorderConfigToStr(const SoundRecorderConfig_t* const Config);
const char* SoundRecorderNodeToStr(const SoundRecorderHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* SOUND_RECORDER_DIAG_H  */
