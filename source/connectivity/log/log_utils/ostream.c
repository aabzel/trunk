#include "ostream.h"

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

bool oputs(ostream_t* const ostream, const char* const str) {
    bool res = false;
    if(ostream) {
        if(str) {
            size_t len = strlen(str);
            ostream->f_putstr(ostream, str, len);
            res = true;
        }
    }
    return res;
}

void oputs_len(ostream_t* const ostream, const char* const str, int32_t len) {
    if(ostream) {
        if(str) {
            ostream->f_putstr(ostream, str, len);
        }
    }
}

void oputc(ostream_t* const ostream, char c) {
    if(ostream) {
        ostream->f_putch(ostream, c);
    }
}
