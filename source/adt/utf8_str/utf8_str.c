#include "utf8_str.h"

#include "log.h"
#include "num_to_str.h"

char * utf8_str_get_i(const char * const str, const uint32_t index) {
    /* Longest UTF-8 sequence: 4 bytes + terminating zero. */
    char * result = NULL;
    if (str) {
        static char buf[8] = {0};
        const uint8_t * p = (const uint8_t *)str;
        uint32_t i = 0U;
        uint32_t len = 0U;
        uint32_t k = 0U;
        bool found = false;

        /* Skip `index` code points. */
        while ((0U != p[0]) && (i < index)) {
            if (0x00U == (0x80U & p[0])) {
                p += 1;
            } else if (0xC0U == (0xE0U & p[0])) {
                p += 2;
            } else if (0xE0U == (0xF0U & p[0])) {
                p += 3;
            } else if (0xF0U == (0xF8U & p[0])) {
                p += 4;
            } else {
                p += 1;
            }
            i++;
        }

        /* Determine length of the code point at `p`. */
        if (0U == p[0]) {
            len = 0U;
        } else if (0x00U == (0x80U & p[0])) {
            len = 1U;
        } else if (0xC0U == (0xE0U & p[0])) {
            len = 2U;
        } else if (0xE0U == (0xF0U & p[0])) {
            len = 3U;
        } else if (0xF0U == (0xF8U & p[0])) {
            len = 4U;
        } else {
            len = 0U;
        }

        found = (i == index) && (0U != len);
        if (found) {
            for (k = 0U; k < len; k++) {
                buf[k] = (char)p[k];
            }
            buf[len] = '\0';
            result = buf;
        }
    }

    return result;
}

uint32_t utf8_strlen(const char *s) {
    uint32_t count = 0;
    for (; *s; ++s) {
        if ((*s & 0xC0) != 0x80){ // не continuation byte
            ++count;
        }
        LOG_DEBUG(STR_LG,"Cnt:%u,0x%02x=0b%s=[%c]",count, *s , utoa_bin8(*s),*s);
    }
    return count;
}
