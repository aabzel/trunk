#ifndef TEST_WM8731_H
#define TEST_WM8731_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "audio_types.h"
#include "test_hw_dep_check.h"

#ifndef HAS_WM8731
#error "+HAS_WM8731"
#endif

#ifndef HAS_I2C
#error "+HAS_I2C"
#endif

#ifndef HAS_I2S
#warning "+HAS_I2S"
#endif

#ifndef HAS_TEST_WM8731
#error "+HAS_WM8731_TESTS"
#endif

bool test_wm8731_hashset(void);
bool test_wm8731_sidetone(void);
bool test_wm8731_set_vol(void);
bool test_wm8731_reinit(void);
bool test_wm8731_play_freq(double freq, SampleType_t amplitude, uint32_t duration_ms);
bool test_wm8731_play(void);
bool test_wm8731_types(void);

#define TEST_SUIT_WM8731                              \
    {"Wm8731Type", test_wm8731_types},                \
    {"wm8731_hashset", test_wm8731_hashset},          \
    {"wm8731ReInit", test_wm8731_reinit},             \
    {"Wm8731SideTone", test_wm8731_sidetone},         \
    {"Wm8731SetVol", test_wm8731_set_vol},            \
    {"Wm8731Play", test_wm8731_play},

#ifdef __cplusplus
}
#endif

#endif /* TEST_WM8731_H */
