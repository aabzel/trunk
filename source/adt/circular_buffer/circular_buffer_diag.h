#ifndef CIRCULAR_BUFFER_DIAG_H
#define CIRCULAR_BUFFER_DIAG_H

//#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "circular_buffer_word_types.h"

const char* CircularBufferStateToStr(const CircularBufferIndexInfo_t* const Node);
const char* CircularBufferNodeToStr(const CircularBufferWord_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* CIRCULAR_BUFFER_DIAG_H */



