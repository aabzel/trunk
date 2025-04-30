#include "sound_localization_config.h"

//#include <stddef.h>

#include "data_utils.h"

#if 0
// vertical
static int16_t OfftetMemLeft[SOUND_LOC_SAMPLE_OFFSET]={0};
static int16_t OfftetMemRight[SOUND_LOC_SAMPLE_OFFSET]={0};

// horisontal
int16_t ShiftMemLeft[SOUND_LOC_SAMPLE_OFFSET][SOUND_LOC_CORRELATION_DEEP] ={0};
int16_t ShiftMemRight[SOUND_LOC_SAMPLE_OFFSET][SOUND_LOC_CORRELATION_DEEP]={0};

#endif

const SoundLocalizationConfig_t SoundLocalizationConfig[] = {
    {
            .num = 1,
            .direction_file_name = "direction.csv",
            .distance_between_microphones_m = 1.0,
            .valid = true,
            .correlation_depth = SOUND_LOC_CORRELATION_DEEP,
            .sampling_frequency_hz = 96000,
            .OffsetSize = SOUND_LOC_SAMPLE_OFFSET,
#if 0
            .OffsetMem = {
                    .vLeft = OfftetMemLeft,
                    .vRight = OfftetMemRight,
            },
#endif
    },
};


SoundLocalizationHandle_t SoundLocalizationInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t sound_localization_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(SoundLocalizationConfig);
    uint32_t cnt_ints = ARRAY_SIZE(SoundLocalizationInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
