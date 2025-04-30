#ifndef STR_UTILS_H
#define STR_UTILS_H

#include <stdbool.h>

#include <stdint.h>
#include <string.h>

#include "string_dep.h"

#ifdef __cplusplus
extern "C" {
#endif

#define STRING_COMMA_LENGTH(STR) (STR), strlen((STR))

#define STRNCPY(dst, src)                                                                                              \
    do {                                                                                                               \
        strncpy((dst), (src), sizeof(dst));                                                                            \
        (dst)[sizeof(dst) - 1] = 0;                                                                                    \
    } while(0)
#define STRNCAT(dst, src)                                                                                              \
    do {                                                                                                               \
        strncat((dst), (src), sizeof(dst) - strlen(dst) - 1);                                                          \
        (dst)[sizeof(dst) - 1] = 0;                                                                                    \
    } while(0)
#define BZERO_S(s) bzero(&(s), sizeof(s));

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define LOCATION __FILE__ ":" TOSTRING(__LINE__)

const char* str_del_char_inplace(char* const data, char del_char);
const char* str_del_substr_inplace(char* const data, char* const substr);
bool wildcmp(const char* wild, const char* string);
bool str2uppercase(char* const inOutStr);
uint32_t string_delete_end(char *const text, size_t size, char letter);
uint32_t string_delete_continuous_duplicat(char* const text, char letter);

bool is_contain(const char* const temp_str, const char* const key_word1, const char* const key_word2);
bool generate_string(uint8_t* array, uint32_t size, char pattern);
char* rx_strtok_r(char* s, const char* delim, char** lasts);
char* str_limit(char* str, uint32_t size);
const char* str_case_str(const char* const text, const char* const pattern);
int strcmp_custon(const char* const string1, const char* const string2);
int replace_char(char* in_out_str, char orig, char rep);
int __strcasecmp(const char* s1, const char* s2);
void strrepl(char* str, char from, char to);
void str_trim(char* str);
uint32_t str_delete_first(char *text, size_t size, char letter);
#ifdef __cplusplus
}
#endif

#endif /* STR_UTILS_H */
