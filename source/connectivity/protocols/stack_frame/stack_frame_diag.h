#ifndef STACK_FRAME_DIAG_H
#define STACK_FRAME_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "stack_frame_types.h"
#include "log.h"

StackFrameHandle_t* StackFrameGetNode(uint8_t num);
const char* StackFrame2Str(const uint8_t* const data, size_t size);
bool stack_frame_protocol_diag(uint8_t num);
const char* Content2Str(StackContentType_t content);

#ifdef __cplusplus
}
#endif

#endif /* STACK_FRAME_DIAG_H */
