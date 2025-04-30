#ifndef STR_UTILS_EX_H
#define STR_UTILS_EX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    char* ptr;
    uint32_t len;
} string_t;

#ifdef HAS_MCU
#error That code only for desktop builds
#endif

char * replace_substring_first_malloc(
    char const * const original,
    char const * const pattern,
    char const * const replacement
);


void replaceFirstOccurrence(char *str, const char *target, const char *replacement);
bool replace_substring_first(char* in_out_str, char* orig, char* rep) ;
bool replace_substring(char* in_out_str, char* orig, char* rep) ;
uint32_t count_substring(char* in_str, char* substr);
char* select_sub_string(char* text, char* tail);
bool parse_text_after_prefix(const char*const cur_file_str, int in_str_len, char*const out_text, uint16_t*const text_len, char*const prefix,
                             char terminator);

bool parse_lhex_array_after_prefix(char* prefix, uint32_t prefix_num, char* in_str_array, char* out_array,
                                   uint32_t out_arr_size);
#ifdef __cplusplus
}
#endif

#endif /* STR_UTILS_EX_H */
