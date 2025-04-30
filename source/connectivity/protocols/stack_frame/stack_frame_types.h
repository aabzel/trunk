#ifndef STACK_FRAME_TYPES_H
#define STACK_FRAME_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "stack_frame_constants.h"
//#include "param_constants.h"

/*op   nop    1 sun  crc*/
/*data double 8 value crc*/

typedef struct {
	StackContentType_t content;
    uint8_t payload_size;
} StackFrameHeader_t;
    //uint8_t crc8; /*data crc*/

typedef struct {
    uint8_t data[20];
    size_t size;
    uint8_t crc8;
    bool valid;
    uint8_t num;
}StackFrameHandle_t;

typedef struct {
     uint8_t num;
     bool valid;
}StackFrameConfig_t;


#ifdef __cplusplus
}
#endif

#endif /* STACK_FRAME_TYPES_H */
