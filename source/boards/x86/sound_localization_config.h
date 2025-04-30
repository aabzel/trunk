#ifndef SOUND_LOCALIZATION_CONFIG_H
#define SOUND_LOCALIZATION_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sound_localization_types.h"

// horisontal
//#define SOUND_LOC_CORRELATION_DEEP (80U)

#if 0
#define SOUND_LOC_CORRELATION_DEEP (40U)
extern int16_t ShiftMemLeft[SOUND_LOC_SAMPLE_OFFSET][SOUND_LOC_CORRELATION_DEEP];
extern int16_t ShiftMemRight[SOUND_LOC_SAMPLE_OFFSET][SOUND_LOC_CORRELATION_DEEP];
#endif

extern const SoundLocalizationConfig_t SoundLocalizationConfig[];
extern SoundLocalizationHandle_t SoundLocalizationInstance[];

uint32_t sound_localization_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /*SOUND_LOCALIZATION_CONFIG_H*/
