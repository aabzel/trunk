#ifndef TEST_BPSK_4FS_H
#define TEST_BPSK_4FS_H

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

#ifndef HAS_BPSK_4FS
#error "It is needed HAS_BPSK_4FS option for that component"
#endif

#ifndef HAS_TEST_SUIT_BPSK_4FS
#error "It is needed HAS_TEST_SUIT_BPSK_4FS option for that component"
#endif

bool test_bpsk_4fs_phase_error(void);
bool test_bpsk_4fs_decode_aaaa(void);
bool test_bpsk_4fs_decode_FFFF(void);
bool test_bpsk_4fs_decode_feed(void);
bool test_bpsk_4fs_utils(void);
bool test_bpsk_4fs_encode(void);
bool test_bpsk_4fs_decode(void);
bool test_bpsk_4fs_perf(void);
bool test_bpsk_4fs_calc_phase_err(void);

#define TEST_SUIT_BPSK_4FS                     \
    {"bpsk_4fs_utils", test_bpsk_4fs_utils},   \
    {"bpsk_4fs_perf", test_bpsk_4fs_perf},     \
    {"bpsk_4fs_encode", test_bpsk_4fs_encode}, \
    {"bpsk_4fs_phase_error", test_bpsk_4fs_phase_error}, \
    {"bpsk_4fs_calc_phase_err", test_bpsk_4fs_calc_phase_err},    \
    {"bpsk_4fs_decode_ffff", test_bpsk_4fs_decode_FFFF},    \
    {"bpsk_4fs_decode_feed", test_bpsk_4fs_decode_feed},    \
    {"bpsk_4fs_decode_aaaa", test_bpsk_4fs_decode_aaaa},    \
    {"bpsk_4fs_decode", test_bpsk_4fs_decode},

#ifdef __cplusplus
}
#endif

#endif /* TEST_BPSK_4FS_H */
