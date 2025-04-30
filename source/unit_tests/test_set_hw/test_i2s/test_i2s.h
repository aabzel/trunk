#ifndef TEST_I2S_H
#define TEST_I2S_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "test_hw_dep_check.h"
#include "audio_types.h"

#ifndef HAS_I2S
#error "It is needed HAS_I2S option for that component"
#endif

#define PLAY_DURATION 1000

#define I2S_SAMPLE_CNT 2
#define I2S_SAMPLE_SIZE 4
#define I2S_CHANNEL_CNT 2
#define I2S_TEST_BLOCK_SIZE (I2S_CHANNEL_CNT * I2S_SAMPLE_CNT * I2S_SAMPLE_SIZE)

bool test_i2s_types(void);
bool test_i2s_play_freq(uint8_t num, double freq, SampleType_t amp, uint32_t pause_ms) ;
bool test_i2s_play_freq_com(uint8_t num, double freq, SampleType_t amp);
bool test_i2s_write_one(uint8_t num);
bool test_i2s_write_one_qword(uint8_t num);

#ifdef HAS_I2S0
bool test_i2s0_read(void);
bool test_i2s0_amplitude_play(void);
bool test_i2s0_loopback(void);
bool test_i2s0_loopback_continuous(void);
bool test_i2s0_write(void);
bool test_i2s0_write_word(void);
bool test_i2s0_write_single(void);
bool test_i2s0_write_toggle(void);
bool test_i2s0_play(void);

#define TEST_SUIT_I2S0_INTERGRATION                                     \
    {"i2s0_loopback", test_i2s0_loopback},                              \
    {"i2s0_loopback_continuous", test_i2s0_loopback_continuous},

#define TEST_SUIT_I2S0                                                  \
    {"i2s0_write", test_i2s0_write},                                    \
    {"i2s0_write_word", test_i2s0_write_word},                          \
    {"i2s0_amplitude_play", test_i2s0_amplitude_play},                  \
    {"i2s0_write_single", test_i2s0_write_single},                      \
    {"i2s0_write_toggle", test_i2s0_write_toggle},                      \
    {"i2s0_read", test_i2s0_read},                                      \
    {"i2s0_play", test_i2s0_play},
#else
#define TEST_SUIT_I2S0
#define TEST_SUIT_I2S0_INTERGRATION
#endif

#ifdef HAS_I2S1
bool test_i2s1_read(void);
bool test_i2s1_write(void);

#define TEST_SUIT_I2S1 {"i2s1_write", test_i2s1_write}, {"i2s1_read", test_i2s1_read},
#else
#define TEST_SUIT_I2S1
#endif

#ifdef HAS_I2S2
bool test_i2s2_read(void);
bool test_i2s2_write(void);
bool test_i2s2_write_word(void);

#define TEST_SUIT_I2S2                \
    {"i2s2_write", test_i2s2_write},  \
    {"i2s2_write_word", test_i2s2_write_word},  \
    {"i2s2_read", test_i2s2_read},
#else
#define TEST_SUIT_I2S2
#endif

#ifdef HAS_I2S3
bool test_i2s3_read(void);
bool test_i2s3_write(void);

#define TEST_SUIT_I2S3 {"i2s3_write", test_i2s3_write}, {"i2s3_read", test_i2s3_read},
#else
#define TEST_SUIT_I2S3
#endif

#ifdef HAS_I2S4
bool test_i2s4_read(void);
bool test_i2s4_write(void);

#define TEST_SUIT_I2S4 {"i2s4_write", test_i2s4_write}, {"i2s4_read", test_i2s4_read},
#else
#define TEST_SUIT_I2S4
#endif

#ifdef HAS_I2S5
bool test_i2s5_read(void);
bool test_i2s5_write(void);

#define TEST_SUIT_I2S5 {"i2s5_write", test_i2s5_write}, {"i2s3_read", test_i2s5_read},
#else
#define TEST_SUIT_I2S5
#endif

#define TEST_SUIT_I2S                                                                                                  \
    {"i2s_types", test_i2s_types},                                                                                     \
        TEST_SUIT_I2S0 TEST_SUIT_I2S1 TEST_SUIT_I2S2 TEST_SUIT_I2S3 TEST_SUIT_I2S4 TEST_SUIT_I2S5


#define TEST_SUIT_I2S_INTEGRATION    \
    TEST_SUIT_I2S0_INTERGRATION      \


#ifdef __cplusplus
}
#endif

#endif /* TEST_I2S_H */
