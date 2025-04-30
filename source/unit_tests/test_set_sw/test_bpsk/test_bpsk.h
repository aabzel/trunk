#ifndef TEST_BPSK_H
#define TEST_BPSK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

#ifndef HAS_BPSK
#error "It is needed HAS_BPSK option for that component"
#endif

#ifndef HAS_TEST_SUIT_BPSK
#error "It is needed HAS_TEST_SUIT_BPSK option for that component"
#endif

bool test_bpsk_utils(void);
bool test_bpsk_encode(void);
bool test_bpsk_decode(void);

#define TEST_SUIT_BPSK                  \
   {"bpsk_utils", test_bpsk_utils}, \
   {"bpsk_encode", test_bpsk_encode}, \
   {"bpsk_decode", test_bpsk_decode}, \

#ifdef __cplusplus
}
#endif

#endif /* TEST_BPSK_H */
