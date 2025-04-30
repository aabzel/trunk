#ifndef OUT_STREAM_TYPES_H
#define OUT_STREAM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef struct {
    void (*f_putch)(void* f_data, char ch);
    void (*f_putstr)(void* f_data, const char* s, int32_t len);
} ostream_t;


#ifdef __cplusplus
}
#endif

#endif /* OUT_STREAM_TYPES_H*/
