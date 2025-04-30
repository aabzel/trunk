#ifndef TEST_WAV_FILES_H
#define TEST_WAV_FILES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

bool test_wav_types(void);

#define TEST_SUIT_WAV            \
    {"wav_types", test_wav_types},

#ifdef __cplusplus
}
#endif

#endif /* TEST_WAV_FILES_H */
