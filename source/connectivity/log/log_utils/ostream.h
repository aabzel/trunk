#ifndef OUT_STREAM_H
#define OUT_STREAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "ostream_types.h"

bool oputs(ostream_t* const ostream, const char* const str);
void oputs_len(ostream_t* const ostream, const char* const str, int32_t len);
void oputc(ostream_t* const ostream, char c);

#ifdef __cplusplus
}
#endif

#endif /* OUT_STREAM_H*/
