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

bool test_sound_recorder_save_perf(void);
bool test_sound_recorder_rec(void);
bool test_sound_recorder_types(void);
bool test_sound_recorder_deps(void);

#define TEST_SUIT_SOUND_RECORDER                                   \
    {"sound_recorder_rec", test_sound_recorder_rec},               \
    {"sound_recorder_save_perf", test_sound_recorder_save_perf},               \
    {"sound_recorder_types", test_sound_recorder_types},           \
	{"sound_recorder_deps", test_sound_recorder_deps},

#ifdef __cplusplus
}
#endif

#endif /* TEST_SOUND_RECORDER_H */
