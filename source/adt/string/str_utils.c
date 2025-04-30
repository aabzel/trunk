#include "str_utils.h"

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifdef HAS_ARRAY
#include "array.h"
#endif
#include "log.h"

static int is_trim_char(char c);

void strrepl(char* str, char from, char to) {
    if(str == NULL) {
        return;
    }

    while(*str != 0) {
        if(*str == from) {
            *str = to;
        }
        str++;
    }
}

static int is_trim_char(char c) { return isspace((unsigned char)c) || c == '\n' || c == '\r'; }

void str_trim(char* str) {
    char* start = str;
    char* end = start + strlen(str) - 1;

    while(end >= start) { /* trim right */
        if(!is_trim_char(*end)) {
            break;
        }
        end--;
    }
    end++;
    *end = '\0';

    while(is_trim_char(*start)) { /* trim left */
        start++;
    }

    if(start != str) /* there is a string */ {
        memmove(str, start, end - start + 1);
    }
}
/*
 Find the first occurrence of pattern in text, ignore case.
 time complexity O(T*P)*/
const char* str_case_str(const char* const in_text, const char* const pattern) {
    const char* retPtr = NULL;

    if((NULL != in_text) && (NULL != pattern)) {
        if(pattern[0] == '\0') {
            retPtr = &in_text[0];
        } else {
            int32_t i;

            for(i = 0; in_text[i] != '\0'; ++i) {
                int32_t j = 0;

                for(j = 0; in_text[i + j] != '\0'; j++) {
                    int32_t symb1 = tolower((int32_t)in_text[i + j]);
                    int32_t symb2 = tolower((int32_t)pattern[j]);

                    if(symb1 != symb2) {
                        break;
                    }
                }

                if(pattern[j] == '\0') {
                    retPtr = &in_text[i];
                    break;
                }
            }
        }
    }

    return retPtr;
}

/*inOutStr must be in RAM not in ROM(FLASH)*/
/* exapmle - EXAPMLE*/
bool str2uppercase(char* const inOutStr) {
    bool res = false;
    if(NULL != inOutStr) {
        uint32_t index;
        uint32_t strLen = strlen(inOutStr);
        for(index = 0; index < strLen; index++) {
            if(('a' <= inOutStr[index]) && (inOutStr[index] <= 'z')) {
                inOutStr[index] = inOutStr[index] - 32u;
            }
        }
        res = true;
    }
    return res;
}

/*
 *
 *     (Declaration that it's public domain):
 *      http://groups.google.com/group/comp.lang.c/msg/7c7b39328fefab9c
 */

char* rx_strtok_r(char* str, const char* delim, char** nextp) {
    char* ret = NULL;

    if(str == NULL) {
        str = *nextp;
    }

    str += strspn(str, delim);

    if(*str == '\0') {
        return NULL;
    }

    ret = str;

    str += strcspn(str, delim);

    if(*str) {
        *str = '\0';
        str++;
    }

    *nextp = str;

    return ret;
}

int strcmp_custon(const char* const string1, const char* const string2) {
    int ret = 1;
    int len1 = strlen(string1);
    int len2 = strlen(string2);
    if(len1 == len2) {
        if(0 < len1) {
            bool res = array_is_equal((uint8_t*)string1, (uint8_t*)string2, len1);
            if(res) {
                ret = 0;
            } else {
                ret = 1;
            }
        } else {
            ret = 0;
        }
    } else {
        LOG_ERROR(SYS, "Len1 %d Len2 %d", len1, len2);
    }
    return ret;
}

bool wildcmp(const char* wild, const char* string) {
    const char *cp = NULL, *mp = NULL;

    while((*string) && (*wild != '*')) {
        if((toupper(*wild) != toupper(*string)) && (*wild != '?')) {
            return false;
        }
        wild++;
        string++;
    }

    while(*string) {
        if(*wild == '*') {
            ++wild;
            if(!*wild) {
                return true;
            }
            mp = wild;
            cp = string + 1;
        } else if((toupper(*wild) == toupper(*string)) || (*wild == '?')) {
            wild++;
            string++;
        } else {
            wild = mp;
            string = cp;
            cp++;
        }
    }

    while('*' == *wild) {
        wild++;
    }
    return !*wild;
}

int replace_char(char* in_out_str, char orig, char rep) {
    char* ix = in_out_str;
    int n = 0;
    while((ix = strchr(ix, orig)) != NULL) {
        *ix++ = rep;
        n++;
    }
    return n;
}

const char* str_del_char_inplace(char* const data, char del_char) {
    char* result = NULL;
    if(data) {
        size_t lenght = strlen(data);
        LOG_DEBUG(LINE, "DelChar[%c]In:[%s],Len:%u", del_char, data, lenght);
        result = data;
        bool res = false;
        int32_t i = 0;
        size_t del_cnt = 0;
        for(i = (lenght - 1); 0 <= i; i--) {
            if(data[i] == del_char) {
                res = array_u8_del_index((uint8_t*)data, lenght, i);
                if(res) {
                    del_cnt++;
                }
            }
        }
        LOG_DEBUG(LINE, "DelCnt:%u", del_cnt);
    }
    return result;
}

const char* str_del_substr_inplace_firts(char* const data, char* const substr) {
    char* result = NULL;
    if(data) {
        result = data;
        if(substr) {
            size_t lenght = strlen(data);
            size_t sub_len = strlen(substr);
            bool res = false;
            LOG_DEBUG(LINE, "Del,Sub[%s]%u]From:[%s]%u]", substr, sub_len, data, lenght);
            size_t del_cnt = 0;
            size_t i = 0;
            for(i = 0; i < (lenght - sub_len); i++) {
                int ret = strncmp(&data[i], substr, sub_len);
                if(0 == ret) {
                    res = array_u8_del_indices((uint8_t*)data, lenght, i, sub_len);
                    if(res) {
                        del_cnt++;
                        res = true;
                        break;
                    }
                }
            }
            LOG_DEBUG(LINE, "DelCnt:%u", del_cnt);
        }
    }
    return result;
}

const char* str_del_substr_inplace(char* const data, char* const substr) {
    char* result = NULL;
    if(data) {
        result = data;
        if(substr) {
            size_t lenght = strlen(data);
            size_t sub_len = strlen(substr);
            bool res = false;
            LOG_DEBUG(LINE, "Del Sub[%s]From:[%s],Len:%u", substr, data, lenght);
            int32_t i = 0;
            size_t del_cnt = 0;
            for(i = (lenght - 1); 0 <= i; i--) {
                int ret = strncmp(&data[i], substr, sub_len);
                if(0 == ret) {
                    res = array_u8_del_indices((uint8_t*)data, lenght, i, sub_len);
                    if(res) {
                        del_cnt++;
                    }
                }
            }
            LOG_DEBUG(LINE, "DelCnt:%u", del_cnt);
        }
    }
    return result;
}

/* Compare S1 and S2, ignoring case, returning less than, equal to or
   greater than zero if S1 is lexicographically less than,
   equal to or greater than S2.
   0 - equal
   not 0 - different
     */
int __strcasecmp(const char* s1, const char* s2) {
    const unsigned char* p1 = (const unsigned char*)s1;
    const unsigned char* p2 = (const unsigned char*)s2;
    int result;
    if(p1 == p2) {
        return 0;
    }
    while((result = tolower(*p1) - tolower(*p2++)) == 0) {
        if(*p1++ == '\0') {
            break;
        }
    }
    return result;
}

bool is_contain(const char* const temp_str, const char* const key_word1, const char* const key_word2) {
    bool res = false;
    if(temp_str) {
        if((0 == strcmp("", key_word1)) && (0 == strcmp("", key_word2))) {
            res = true;
        } else {

            if(0 != strcmp("", key_word1) && 0 != strcmp("", key_word2)) {
                if(str_case_str(temp_str, key_word1) && str_case_str(temp_str, key_word2)) {
                    res = true;
                }
            } else if(0 != strcmp("", key_word1) && 0 == strcmp("", key_word2)) {
                if(str_case_str(temp_str, key_word1)) {
                    res = true;
                }
            } else {
                res = true;
            }
        }
    }
    return res;
}

bool generate_string(uint8_t* array, uint32_t size, char pattern) {
    bool res = false;
    if(array) {
        if(size) {
            uint32_t i = 0;
            for(i = 0; i < size; i++) {
                array[i] = pattern;
            }
            res = true;
        }
    }
    return res;
}

char* str_limit(const char* const str, uint32_t size) {

    memset(text, 0, sizeof(text));
    uint32_t len = strlen(str);
    if(len < sizeof(text)) {
        strcpy(text, str);
    }
    if((size + 3) < sizeof(text)) {
        if(size < len) {
            text[size] = '.';
            text[size + 1] = '.';
            text[size + 2] = '\0';
        }
    }
    return text;
}

uint32_t str_delete_first(char* in_text, size_t size, char letter) {
    uint32_t i = 0;
    uint32_t cnt = 0;
    LOG_DEBUG(LINE, "DelFront:[%s]%u,Ch:[%c]", in_text, size, letter);
    bool res = false;
    for(i = 0; i < size; i++) {
        if(letter == in_text[0]) {
            res = array_u8_del_index((uint8_t*)in_text, size, 0);
            if(res) {
                cnt++;
            }
        } else {
            break;
        }
    }
    LOG_DEBUG(LINE, "DelCnt:%u", cnt);
    return cnt;
}

/*     "h vi "5->"h vi"  5 */
uint32_t string_delete_end(char* const in_text, size_t size, char letter) {
    uint32_t cnt = 0;
    if(in_text) {
        if(size) {
            LOG_DEBUG(LINE, "DelEnd:[%s]%u,Ch:[%c]", in_text, size, letter);
            int32_t i = 0;
            for(i = (size - 1); 0 <= i; i--) {
                LOG_DEBUG(LINE, "Proc:%u:[%c]", i, in_text[i]);
                if(letter == in_text[i]) {
                    in_text[i] = 0x00;
                    LOG_DEBUG(LINE, "DelAt:%u", i);
                    cnt++;
                } else {
                    break;
                }
            }
        }
    }
    LOG_DEBUG(LINE, "DelCnt:%u", cnt);
    return cnt;
}

/*Delete continuous duplicat for spesific letter*/
uint32_t string_delete_continuous_duplicat(char* const in_text, char letter) {
    uint32_t cnt = 0;
    uint32_t size = strlen(in_text);
    LOG_DEBUG(LINE, "DelDup:[%s]:%u, Del[%c]", in_text, size, letter);
    uint32_t i = 0;
    uint32_t j = 0;
    bool res = false;
    for(j = 0; j < size; j++) {
        char cur = 0;
        char prev = 0;
        for(i = 0; i < size; i++) {
            cur = in_text[i];
            if(letter == cur) {
                if(cur == prev) {
                    if(0 < i) {
                        res = array_u8_del_index((uint8_t*)in_text, size, i);
                        if(res) {
                            cnt++;
                        }
                        break;
                    }
                }
            }
            prev = cur;
        }
    }
    LOG_DEBUG(LINE, "DelCnt:%u", cnt);
    return cnt;
}
