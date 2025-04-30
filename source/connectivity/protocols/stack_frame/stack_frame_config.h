#ifndef STACK_FRAME_CONFIG_H
#define STACK_FRAME_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stack_frame_types.h"

extern const StackFrameConfig_t StackFrameConfig[];
extern StackFrameHandle_t StackFrameInstance[];

uint32_t stack_frame_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /*STACK_FRAME_CONFIG_H*/
