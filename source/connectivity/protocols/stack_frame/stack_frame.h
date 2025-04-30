#ifndef STACK_FRAME_PROTOCOL_H
#define STACK_FRAME_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "array.h"
#include "stack_frame_config.h"
#include "stack_frame_types.h"

bool stack_frame_parse_number(const Array_t* const node, double* const number);
bool stack_frame_parse_operation(const Array_t* const node, Operation_t* const operation);
bool stack_frame_init(void);
bool stack_frame_compose_operation(StackFrameHandle_t* const Node, Operation_t operation);
bool stack_frame_compose_double(StackFrameHandle_t* const Node, double value);
bool stack_frame_init_ll(StackFrameHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* STACK_FRAME_PROTOCOL_H */
