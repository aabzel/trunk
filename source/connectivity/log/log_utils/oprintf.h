#ifndef OUT_PRINTF_H
#define OUT_PRINTF_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdarg.h>
#include <stddef.h>

#include "std_includes.h"
#include "ostream.h"
#include "writer_types.h"

#ifndef HAS_STREAM
#error "+HAS_STREAM"
#endif

#ifndef MAX_INT64_STR_LEN_10
#define MAX_INT64_STR_LEN_10 40
#endif

#ifndef MAX_PRECISION
#define MAX_PRECISION 11
#endif

#ifndef HAS_X86_64
#ifndef ssize_t
// typedef int32_t ssize_t;
#endif
#endif

typedef enum {
    SIZE_SIGNED_CHAR,
    SIZE_SHORT,
    SIZE_NORMAL,
    size_long,
    SIZE_LONG_LONG,
    size_long_long_long = 8,
    SIZE_SIZE_T
} format_size_t;


void oprintf(ostream_t* s, const char* fmt, ...);
bool ovprint_is_valid(ostream_t* stream);
bool ovprintf(ostream_t* s, const char* fmt, va_list va);

#ifdef __cplusplus
}
#endif

#endif /* OUT_PRINTF_H */
