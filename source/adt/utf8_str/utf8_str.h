#ifndef UTF8_STR_H
#define UTF8_STR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_inc.h"

char * utf8_str_get_i(const char* const str, const uint32_t index) ;
uint32_t utf8_strlen(const char *s) ;

#ifdef __cplusplus
}
#endif

#endif /* UTF8_STR_H */
