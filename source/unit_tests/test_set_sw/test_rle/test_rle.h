
#ifndef TEST_RLE_H
#define TEST_RLE_H

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

#ifndef HAS_RLE
#error "It is needed HAS_RLE option for that component"
#endif

#ifndef HAS_TEST_SUIT_RLE
#error "It is needed HAS_TEST_SUIT_RLE option for that component"
#endif

bool test_rle_encode(void);
bool test_rle_encode_v2(void);
bool test_rle_encode_in_place(void);
bool test_rle_decode(void);
bool test_rle_encode_decode(void);

#define TEST_SUIT_RLE                                                                                                  \
    {"rle_encode", test_rle_encode}, {"rle_encode_v2", test_rle_encode_v2},                                            \
        {"rle_encode_in_place", test_rle_encode_in_place}, {"rle_decode", test_rle_decode},                            \
        {"rle_encode_decode", test_rle_encode_decode},

#ifdef __cplusplus
}
#endif

#endif /* TEST_RLE_H */
