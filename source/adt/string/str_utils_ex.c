#include "str_utils_ex.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "convert.h"
#include "log.h"

#ifdef HAS_MCU
#error "That code only for desktop builds"
#endif

uint32_t count_substring(char* in_str, char* substr) {
    uint32_t match_cnt = 0u;
    int in_str_len = strlen(in_str);
    if(0 < in_str_len) {
        int sub_str_len = strlen(substr);
        char* cur_ptr = strstr(in_str, substr);
        while(NULL != cur_ptr) {
            match_cnt++;
            cur_ptr = strstr(&cur_ptr[sub_str_len], substr);
        }
    }

    return match_cnt;
}

bool parse_lhex_array_after_prefix(char* prefix, uint32_t prefix_num, char* in_str_array, char* out_array,
                                   uint32_t out_arr_size) {
    bool res = false;
    uint32_t i = 0;
#ifdef HAS_STR_DEBUG
    LOG_DEBUG(LINE, " prefix [%s] prefix_num [%u]", prefix, prefix_num);
#endif
    char* ptr = in_str_array;
    do {
        ptr = strstr(ptr, prefix);
        if(ptr) {
            if(i == prefix_num) {
#ifdef HAS_STR_DEBUG
                LOG_DEBUG(LINE, " spot prefix [%s] start[%s] i=%u", prefix, ptr, i);
#endif
                uint32_t out_array_len = 0;
                res = try_strl2array(ptr, 2 * out_arr_size, (uint8_t*)out_array, out_arr_size, &out_array_len);
                if(res) {
#ifdef HAS_STR_DEBUG
                    LOG_DEBUG(LINE, " spot array");
#endif
                    if(out_array_len == out_arr_size) {
                        res = true;
                    } else {
#ifdef HAS_STR_DEBUG
                        LOG_DEBUG(LINE, "[e] array len error");
#endif
                        res = false;
                    }
                } else {
#ifdef HAS_STR_DEBUG
                    LOG_DEBUG(LINE, "[e] parse array error");
#endif
                }
                break;
            }
            ptr++;
            i++;
        }
    } while(ptr);

    return res;
}

/*Exctract sub string*/
bool parse_text_after_prefix(const char* const cur_file_str, int in_str_len, char* const out_text,
                             uint16_t* const text_len, char* const prefix, char terminator) {
    bool res = false;
    LOG_DEBUG(LINE, "InLen:%u", in_str_len);
    (*text_len) = 0;
    int prefix_len = strlen(prefix);
    LOG_DEBUG(LINE, "PrefixLen:%u", prefix_len);
    char* ptr = strstr(cur_file_str, prefix);
    if(ptr) {
        LOG_DEBUG(LINE, "SpotPrefix:[%s]", prefix);
        res = true;
        int i = 0;
        uint32_t rest_len = in_str_len - prefix_len;
        LOG_DEBUG(LINE, "RestLen:%u", rest_len);
        for(i = 0; i < rest_len; i++) {
            char* cur_char_ptr = ptr + prefix_len + i;
            if(('"' != *cur_char_ptr) || ('\r' != *cur_char_ptr) || ('\n' != *cur_char_ptr)) {
                if((terminator != *cur_char_ptr) && ('\r' != *cur_char_ptr) && ('\n' != *cur_char_ptr)) {
                    out_text[i] = *cur_char_ptr;
                    (*text_len)++;
                    LOG_DEBUG(LINE, "+%c,Out:[%s],Len:%u", *cur_char_ptr, out_text, *text_len);
                    res = true;
                }
            } else {
                break;
            }
        }
        out_text[i] = 0x00;
    } else {
        LOG_DEBUG(LINE, "LackOfPrefix[%s]", prefix);
        res = false;
    }
    return res;
}

void replaceFirstOccurrence(char* str, const char* target, const char* replacement) {
    char* position = strstr(str, target);
    LOG_DEBUG(LINE, " position:[%s]", position);
    if(position != NULL) {
        // Calculate the length of the matched substring
        size_t targetLength = strlen(target);
        LOG_DEBUG(LINE, " targetLength:%u", targetLength);
        size_t replacementLength = strlen(replacement);
        LOG_DEBUG(LINE, " replacementLength:%u", replacementLength);
        // Calculate the length difference between the target and replacement
        // int lengthDiff = replacementLength - targetLength;

        // Move characters after the match to make space for the replacement
        memmove(position + replacementLength, position + targetLength, strlen(position + targetLength) + 1);

        // Copy the replacement into the matched position
        memcpy(position, replacement, replacementLength);
    }
}

bool replace_substring_first(char* in_out_str, char* orig, char* rep) {
    bool res = false;
    LOG_DEBUG(LINE, " text:[%s],orig:[%s],rep:[%s]", in_out_str, orig, rep);
    int text_len = strlen(in_out_str);
    int patt_len = strlen(orig);
    int rep_len = strlen(rep);
    int cnt = count_substring(in_out_str, orig);
    if(0 < cnt) {
        while(0 < count_substring(in_out_str, orig)) {
            char* cur_ptr = strstr(in_out_str, orig);
            if(cur_ptr) {
                LOG_DEBUG(LINE, " cur_ptr:[%s]", cur_ptr);
                memset(cur_ptr, 0x00, patt_len);
                char* suffix;
                suffix = &cur_ptr[patt_len];
                uint32_t size = text_len + patt_len + rep_len;
                if(0 < size) {
                    LOG_DEBUG(LINE, " size %u", size);
                    char* temp_str = malloc(size);
                    if(temp_str) {
                        LOG_DEBUG(LINE, " temp [%s][%s][%s]", in_out_str, rep, suffix);
                        snprintf(temp_str, size, "%s%s%s", in_out_str, rep, suffix);
                        strcpy(in_out_str, temp_str);
                        LOG_DEBUG(LINE, " res[%s]", in_out_str);
                        free(temp_str);
                        temp_str = NULL;
                        res = true;
                        return res;
                    }
                }
            }
        } // while
    } else {
        LOG_WARNING(LINE, "LackOfPattern [%s]", orig);
    }

    return res;
}

bool replace_substring(char* in_out_str, char* orig, char* rep) {
    bool res = false;
    LOG_PARN(LINE, " text [%s] orig [%s] rep [%s]", in_out_str, orig, rep);
    int text_len = strlen(in_out_str);
    int patt_len = strlen(orig);
    int rep_len = strlen(rep);
    int cnt = count_substring(in_out_str, orig);
    if(0 < cnt) {
        while(0 < count_substring(in_out_str, orig)) {
            char* cur_ptr = strstr(in_out_str, orig);
            if(NULL != cur_ptr) {
                LOG_PARN(LINE, " cur_ptr %s", cur_ptr);
                memset(cur_ptr, 0x00, patt_len);
                char* suffix;
                suffix = &cur_ptr[patt_len];
                uint32_t size = text_len + patt_len + rep_len;
                if(0 < size) {
                    LOG_PARN(LINE, " size %u", size);
                    char* temp_str = malloc(size);
                    if(temp_str) {
                        LOG_PARN(LINE, " temp [%s][%s][%s]", in_out_str, rep, suffix);
                        snprintf(temp_str, size, "%s%s%s", in_out_str, rep, suffix);
                        strcpy(in_out_str, temp_str);
                        LOG_PARN(LINE, " res[%s]", in_out_str);
                        free(temp_str);
                        temp_str = NULL;
                        res = true;
                    }
                }
            }
        } // while
    } else {
        LOG_WARNING(LINE, "LackOfPattern [%s]", orig);
    }

    return res;
}
