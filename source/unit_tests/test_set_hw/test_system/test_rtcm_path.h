#ifndef TEST_RTCM3_PATH_H
#define TEST_RTCM3_PATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

bool test_rtcm3_path(void);

#define TEST_SUIT_RTCM3_PATH                      \
        {"rtcm3_path", test_rtcm3_path},                                                                                                     \

#ifdef __cplusplus
}
#endif

#endif /* TEST_RTCM3_PATH_H */
