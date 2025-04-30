#ifndef TEST_STRING_UTILS_H
#define TEST_STRING_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

bool test_replace_char(void);
bool test_str_limiter(void);
bool test_str_delete_con_duplicat(void);
bool test_delete_char(void);
bool test_delete_substr(void);
bool test_string_delete_end(void);
bool test_str_del_substr_inplace_firts(void);

#define TEST_SUIT_STRING_UTILS_BASE         \
    {"str_del_substr_inplace_firts", test_str_del_substr_inplace_firts},  \
    {"replace_char", test_replace_char},  \
    {"delete_char", test_delete_char},  \
    {"test_string_delete_end", test_string_delete_end},  \
    {"str_delete_con_duplicat", test_str_delete_con_duplicat},  \
    {"delete_substr", test_delete_substr},  \
    {"str_limiter", test_str_limiter},

#ifdef HAS_PC
bool test_string_extract(void);
bool test_string_utils_ext(void);
bool test_replace_substr(void);
bool test_replace_substr_first(void);
bool test_count_substring(void);

#define TEST_SUIT_STRING_UTILS_EXT                               \
    {"replace_substr_first", test_replace_substr_first},  \
    {"str_count_substring", test_count_substring},  \
    {"string_extract", test_string_extract},  \
    {"replace_substr", test_replace_substr},                            \
    {"str_utils_ext", test_string_utils_ext},
#else
#define TEST_SUIT_STRING_UTILS_EXT
#endif

#define TEST_SUIT_STRING_UTILS                                                                                         \
    TEST_SUIT_STRING_UTILS_EXT                                                                                         \
    TEST_SUIT_STRING_UTILS_BASE

#ifdef __cplusplus
}
#endif

#endif /* TEST_STRING_UTILS_H */
