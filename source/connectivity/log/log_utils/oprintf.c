#include "oprintf.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifndef HAS_STRING
#error "HAS_STRING"
#endif

#ifndef ssize_t
typedef int32_t ssize_t;
#endif

#ifdef HAS_STRING
#include "convert.h"
#endif

static char* uli2a(uint64_t num, uint8_t base, bool uc, char* bf) {
    uint8_t n = 0;
    uint64_t digit = 1;
    while(base <= (num / digit)) {
        digit *= base;
    }
    while(0 != digit) {
        uint8_t dgt = num / digit;
        num %= digit;
        digit /= base;
        if((n != 0) || (0 < dgt) || (0 == digit)) {
            *bf = (char)(dgt + (dgt < 10 ? '0' : (uc ? 'A' : 'a') - 10));
            bf++;
            ++n;
        }
    }
    *bf = '\0';
    return bf;
}

static char* li2a(int64_t num, char* bf) {
    if(num < 0) {
        num = -num;
        *bf = '-';
        bf++;
    }
    return uli2a(num, 10, false, bf);
}

static void ui2a(uint32_t num, unsigned int base, bool uc, char* bf) {
    int n = 0;
    uint32_t d = 1;
    while(num / d >= base) {
        d *= base;
    }
    while(d != 0) {
        uint8_t dgt = num / d;
        num %= d;
        d /= base;
        if((n != 0) || dgt > 0 || d == 0) {
            *bf = dgt + (dgt < 10 ? '0' : (uc ? 'A' : 'a') - 10);
            bf++;
            ++n;
        }
    }
    *bf = 0;
}

static void i2a(int32_t num, char* bf) {
    if(num < 0) {
        num = -num;
        *bf = '-';
        bf++;
    }
    ui2a(num, 10, false, bf);
}

static int8_t a2d(char ch) {
    if(('0' <= ch) && (ch <= '9')) {
        return ch - '0';
    } else {
        return -1;
    }
}

static char a2i(char ch, const char** src, int32_t* nump) {
    const char* p = *src;
    int32_t num = 0, digit = a2d(ch);
    while(0 <= digit) {
        num = num * 10 + digit;
        ch = *p;
        p++;
        digit = a2d(ch);
    }
    *src = p;
    *nump = num;
    return ch;
}

static void putsw(ostream_t* s, int n, bool z, const char* bf) {
    char fc = z ? '0' : ' ';
    const char* p = bf;
    while(*p && (0 < n)) {
        n--;
        p++;
    }
    while(0 < n) {
        s->f_putch(s, fc);
        n--;
    }
    int32_t len = strlen(bf);
    s->f_putstr(s, bf, len); /*Error*/
}

typedef enum {
    SIZE_SIGNED_CHAR,
    SIZE_SHORT,
    SIZE_NORMAL,
    size_long,
    SIZE_LONG_LONG,
    size_long_long_long = 8,
    SIZE_SIZE_T
} format_size_t;

bool ovprintf(ostream_t* stream, const char* fmt, va_list va) {
    bool res = false;
    static bool works = false;
    if(false == works) {
        works = true;
        if(NULL != stream) {
            res = true;
            char bf[MAX_INT64_STR_LEN_10 + MAX_PRECISION + 1 + 1];
            const char* start = NULL;
            int len = 0;
            while(*fmt) {
                char ch = *fmt;
                fmt++;
                if(ch != '%') {
                    if(0 == len) {
                        len = 1;
                        start = fmt - 1;
                    } else {
                        len++;
                    }
                } else {
                    bool leading_zero = false;
                    format_size_t size = SIZE_NORMAL;
                    int32_t width = 0;
                    int32_t precision = -1;
                    if(len) {
                        stream->f_putstr(stream, start, len);
                        len = 0;
                    }
                    ch = *fmt;
                    fmt++;
                    if(ch == '0') {
                        ch = *fmt;
                        fmt++;
                        leading_zero = true;
                    }
                    if(('0' <= ch) && (ch <= '9')) {
                        ch = a2i(ch, &fmt, &width);
                        if(ch == '.') {
                            ch = *fmt;
                            fmt++;
                            if(ch >= '0' && ch <= '9') {
                                ch = a2i(ch, &fmt, &precision);
                                if(precision > (int32_t)MAX_PRECISION) {
                                    precision = MAX_PRECISION;
                                }
                            }
                        }
                    }
                    if('h' == ch) {
                        ch = *fmt;
                        fmt++;
                        size = SIZE_SHORT;
                    }
                    if('h' == ch) {
                        ch = *fmt;
                        fmt++;
                        size = SIZE_SIGNED_CHAR;
                    }
                    if(ch == 'l' || ch == 'L') {
                        ch = *fmt;
                        fmt++;
                        size = size_long;
                    }
                    if(ch == 'z') {
                        ch = *fmt;
                        fmt++;
                        size = SIZE_SIZE_T;
                    }
                    if(ch == 'l' || ch == 'L') {
                        ch = *fmt;
                        fmt++;
                        size = SIZE_LONG_LONG;
                    }
                    if(ch == 'l' || ch == 'L') {
                        ch = *fmt;
                        fmt++;
                        size = size_long_long_long;
                    }

                    if(0 == ch) {
                        return res;
                    }
                    switch(ch) {
                    case 'u':
                        switch(size) {
                        case size_long:
                            ui2a(va_arg(va, unsigned long), 10, false, bf);
                            break;
                        case SIZE_LONG_LONG:
                            uli2a(va_arg(va, uint64_t), 10, false, bf);
                            break;
                        case size_long_long_long:
                            uli2a(va_arg(va, uint64_t), 10, false, bf);
                            break;
                        case SIZE_SIZE_T:
                            ui2a(va_arg(va, size_t), 10, false, bf);
                            break;
                        case SIZE_SIGNED_CHAR:
                        case SIZE_SHORT:
                        case SIZE_NORMAL:
                        default:
                            ui2a(va_arg(va, unsigned int), 10, false, bf);
                            break;
                        }
                        putsw(stream, width, leading_zero, bf);
                        break;
                    case 'd':
                        switch(size) {
                        case size_long:
                            i2a(va_arg(va, long), bf);
                            break;
                        case SIZE_SIZE_T:
                            i2a(va_arg(va, ssize_t), bf);
                            break;
                        case SIZE_LONG_LONG:
                            li2a(va_arg(va, long long), bf);
                            break;
                        case SIZE_SIGNED_CHAR:
                        case SIZE_SHORT:
                        case SIZE_NORMAL:
                        default:
                            i2a(va_arg(va, int), bf);
                            break;
                        }
                        putsw(stream, width, leading_zero, bf);
                        break;
                    case 'x':
                    case 'X':
                    case 'p':
                        switch(size) {
                        case size_long:
                            ui2a(va_arg(va, unsigned long), 16, (ch == 'X'), bf);
                            break;
                        case SIZE_SIZE_T:
                            ui2a(va_arg(va, size_t), 16, (ch == 'X'), bf);
                            break;
                        case SIZE_LONG_LONG:
                            uli2a(va_arg(va, uint64_t), 16, (ch == 'X'), bf);
                            break;
                        case SIZE_SHORT:
                        case SIZE_SIGNED_CHAR:
                        case SIZE_NORMAL:
                        default:
                            ui2a(va_arg(va, unsigned int), 16, (ch == 'X'), bf);
                            break;
                        }
                        putsw(stream, width, leading_zero, bf);
                        break;
                    case 'c':
                        stream->f_putch(stream, (char)(va_arg(va, int)));
                        break;
                    case 's':
                        putsw(stream, width, false, va_arg(va, const char*)); /*Error*/
                        break;
                    case 'f':
                    case 'g':
#ifdef HAS_STR2_DOUBLE
#ifdef HAS_STRING_PARSER
                        dtoa_(va_arg(va, double), precision, bf);
#endif
                        putsw(stream, width, false, bf);
#endif
                        break;
                    case '%':
                        stream->f_putch(stream, ch);
                        break;
                    default:
                        stream->f_putstr(stream, "???", 3);
                        stream->f_putch(stream, ch);
                        break;
                    }
                }
            } // while
            if(len) {
                stream->f_putstr(stream, start, len);
                len = 0;
            }
        }
        works = false;
    } else {
        // Recursion
    }
    return res;
}

void oprintf(ostream_t* s, const char* fmt, ...) {
    va_list va;
    va_start(va, fmt);
    ovprintf(s, fmt, va);
    va_end(va);
}
