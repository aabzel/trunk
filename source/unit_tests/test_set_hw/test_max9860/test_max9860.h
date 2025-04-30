#ifndef TEST_MAX9860_H
#define TEST_MAX9860_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

//#include "audio_types.h"
#include "test_hw_dep_check.h"

#ifndef HAS_MAX9860
#error "+HAS_MAX9860"
#endif

#ifndef HAS_I2C
#error "+HAS_I2C"
#endif

#ifndef HAS_I2S
#warning "+HAS_I2S"
#endif

#ifndef HAS_TEST_MAX9860
#error "+HAS_MAX9860_TESTS"
#endif

bool test_max9860_volume_play(void);
bool test_max9860_freq_play(void);
bool test_max9860_sidetone(void);
bool test_max9860_connected(void);
bool test_max9860_set_vol(void);
bool test_max9860_hash_tables(void);
bool test_max9860_reinit(void);
bool test_max9860_play_freq(double freq, uint16_t amplitude, uint32_t duration_ms);
bool test_max9860_reg_write_read(void);
bool test_max9860_types(void);
bool test_max9860_sample(void);

#define TEST_SUIT_MAX9860                                             \
    {"max9860_types", test_max9860_types},                             \
    {"max9860_sample", test_max9860_sample},                             \
    {"max9860_connected", test_max9860_connected},                    \
    {"max9860_reg_write_read", test_max9860_reg_write_read},          \
    {"max9860_hash_tables", test_max9860_hash_tables},                \
    {"max9860_reinit", test_max9860_reinit},                          \
    {"max9860_sidetone", test_max9860_sidetone},                      \
    {"max9860_SetVol", test_max9860_set_vol},                         \
    {"max9860_volume_play", test_max9860_volume_play},                \
    {"max9860_freq_play", test_max9860_freq_play},

#ifdef __cplusplus
}
#endif

#endif /* TEST_MAX9860_H */
