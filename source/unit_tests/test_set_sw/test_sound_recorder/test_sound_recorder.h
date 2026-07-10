#ifndef TEST_SOUND_RECORDER_H
#define TEST_SOUND_RECORDER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

#ifndef HAS_SOUND_RECORDER
#error "It is needed HAS_SOUND_RECORDER option for that component"
#endif

#ifndef HAS_TEST_SUIT_SOUND_RECORDER
#error "It is needed HAS_TEST_SUIT_SOUND_RECORDER option for that component"
#endif

#define WAV_REC_FILE "RecTest.wav"
#define SAVE_PART_SIZE 4096UL
#define TEST_WAV_FILE_SIZE (SAVE_PART_SIZE*400UL)
#define REC_PART_32K_TIMEOUT_US (    (1000000UL*REC_MEM_HALF_SIZE)/AUDIO_FREQ_32K     )
#define REC_PART_48K_TIMEOUT_US (    (1000000UL*REC_MEM_HALF_SIZE)/AUDIO_FREQ_48K     )
#define REC_PART_88K_TIMEOUT_US (    (1000000UL*REC_MEM_HALF_SIZE)/AUDIO_FREQ_88K     )
#define REC_PART_96K_TIMEOUT_US (    (1000000UL*REC_MEM_HALF_SIZE)/AUDIO_FREQ_96K     )

bool test_sound_recorder_save_perf(void);
bool test_sound_recorder_rec(void);
bool test_sound_recorder_types(void);
bool test_sound_recorder_deps(void);
bool test_sound_recorder_write_perf(void);

#define TEST_SUIT_SOUND_RECORDER                                                 \
    {"sound_recorder_write_perf", test_sound_recorder_write_perf},               \
    {"sound_recorder_rec", test_sound_recorder_rec},                             \
    {"sound_recorder_save_perf", test_sound_recorder_save_perf},                 \
    {"sound_recorder_types", test_sound_recorder_types},                         \
    {"sound_recorder_deps", test_sound_recorder_deps},

#ifdef __cplusplus
}
#endif

#endif /* TEST_SOUND_RECORDER_H */
