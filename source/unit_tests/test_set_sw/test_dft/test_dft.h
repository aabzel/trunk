#ifndef TEST_DFT_H
#define TEST_DFT_H

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

bool test_dft_500(void);
bool test_dft_1000(void);
bool test_dft_2000(void);

#define TEST_SUIT_DFT             \
    {"dft_500", test_dft_500},    \
    {"dft_1000", test_dft_1000},  \
    {"dft_2000", test_dft_2000},  \

#ifdef __cplusplus
}
#endif

#endif /* TEST_DFT_H */
