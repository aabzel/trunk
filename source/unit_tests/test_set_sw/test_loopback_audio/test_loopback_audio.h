#ifndef TEST_LOOPBACK_AUDIO_H
#define TEST_LOOPBACK_AUDIO_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"

#define TEST_LOOPBACK_WAV_NAME "sin2kHz5s.wav"

#define TEST_WAV_PLAY "sin2kHz5s.wav"
#define TEST_WAV_REC "Rec.wav"

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

#ifndef HAS_LOOPBACK_AUDIO
#error "It is needed HAS_LOOPBACK_AUDIO option for that component"
#endif

#ifndef HAS_TEST_SUIT_LOOPBACK_AUDIO
#error "It is needed HAS_TEST_SUIT_LOOPBACK_AUDIO option for that component"
#endif

bool test_loopback_audio_rec_play_one(uint8_t num, const  char* const PlayFileName);

bool test_loopback_audio_rec_play(void);
bool test_loopback_audio_play(void);
bool test_loopback_audio_types(void);
bool test_loopback_audio_deps(void);

#define TEST_SUIT_LOOPBACK_AUDIO                                     \
    {"loopback_audio_rec_play", test_loopback_audio_rec_play},               \
    {"loopback_audio_play", test_loopback_audio_play},               \
    {"loopback_audio_types", test_loopback_audio_types},             \
    {"loopback_audio_deps", test_loopback_audio_deps},

#ifdef __cplusplus
}
#endif

#endif /* TEST_LOOPBACK_AUDIO_H */
