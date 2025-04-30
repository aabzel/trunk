#ifndef TEST_FFT_H
#define TEST_FFT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

bool test_fft_500(void);
bool test_fft_1000(void);
bool test_fft_2000(void);

#define TEST_SUIT_FFT             \
    {"fft_500", test_fft_500},    \
    {"fft_1000", test_fft_1000},  \
    {"fft_2000", test_fft_2000},  \

#ifdef __cplusplus
}
#endif

#endif /* TEST_FFT_H */
