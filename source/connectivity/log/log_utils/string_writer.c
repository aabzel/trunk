#include "string_writer.h"

#include <string.h>

void string_putc(void* string_stream, char ch) {
    string_stream_t* s = (string_stream_t*)string_stream;
    if(s->pos < s->size - 1) {
        s->data[s->pos] = ch;
        s->pos++;
        s->data[s->pos] = '\0';
    } else {
        s->overflow = true;
    }
}

void string_puts(void* string_stream, const char* str, int32_t len) {
    int i;
    if(len < 0) {
        len = strlen(str);
    }
    for(i = 0; i < len; i++) {
        string_putc(string_stream, str[i]);
    }
}
