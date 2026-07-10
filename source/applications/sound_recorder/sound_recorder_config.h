#ifndef SOUND_RECORDER_CONFIG_H
#define SOUND_RECORDER_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "sound_recorder_types.h"
#include "dsp_types.h"
#include "sound_recorder_dep.h"

#define SAMPLE_FREQ_HZ  96000UL
/*REC_MEM_SAM_CNT 8kByte*/
/*512 samples = 1024 byte
 512 losses
 1024UL*9UL  losses
 1024UL*7UL  losses
 1024UL*6UL  losses
 1024UL*5UL  losses small
 1024UL*4UL  OK
 1024UL*2UL  crackling on the left channel
 */
#define REC_CHAN_CNT 2
#define REC_MEM_SAM_CNT ( 4096UL)
#define REC_MEM_HALF_SIZE (REC_MEM_SAM_CNT/2)
#define REC_SAMPLE_SIZE 2UL
#define REC_SIZE_OF (REC_SAMPLE_SIZE*REC_MEM_SAM_CNT)
#define REC_FRAMES (REC_MEM_SAM_CNT/REC_CHAN_CNT)
#define REC_PART_DURATION_S (((float)REC_FRAMES)/   ((float) SAMPLE_FREQ_HZ))

#define REC_HALF_SIZE_OF (REC_SIZE_OF/2UL)

/*REC_MEM_HALF_SIZE 4kByte*/
/*125 samples*/
#define REC_PART_TIMEOUT_US (    (1000000UL*REC_MEM_HALF_SIZE)/SAMPLE_FREQ_HZ     )


extern const SoundRecorderConfig_t SoundRecorderConfig[];
extern SoundRecorderHandle_t SoundRecorderInstance[];

uint32_t sound_recorder_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* SOUND_RECORDER_CONFIG_H */
