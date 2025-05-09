#ifndef TEST_HEX_BIN_UTILS_H
#define TEST_HEX_BIN_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

bool test_hex_bin_types(void) ;
bool test_hex_bin_is_hex_file(void) ;
bool test_hex_bin_proc(void);
bool test_hex_bin_proc_4(void);

#define TEST_SUIT_HEX_BIN                  \
    {"hex_bin_types", test_hex_bin_types}, \
    {"hex_bin_is_hex_file", test_hex_bin_is_hex_file}, \
    {"hex_bin_proc_4", test_hex_bin_proc_4}, \
    {"hex_bin_proc", test_hex_bin_proc},

#ifdef __cplusplus
}
#endif

#endif /* TEST_HEX_BIN_UTILS_H */
