#ifndef TEST_WAV_PLAYER_H
#define TEST_WAV_PLAYER_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"

#define TEST_WAV_NAME "sin2kHz5s.wav"


#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

#ifndef HAS_WAV_PLAYER
#error "It is needed HAS_WAV_PLAYER option for that component"
#endif

#ifndef HAS_TEST_SUIT_WAV_PLAYER
#error "It is needed HAS_TEST_SUIT_WAV_PLAYER option for that component"
#endif

bool test_wav_player_play(void);
bool test_wav_player_types(void);
bool test_wav_player_deps(void);

#define TEST_SUIT_WAV_PLAYER                            \
    {"wav_player_play", test_wav_player_play},               \
    {"wav_player_types", test_wav_player_types},               \
	{"wav_player_deps", test_wav_player_deps},

#ifdef __cplusplus
}
#endif

#endif /* TEST_WAV_PLAYER_H */
