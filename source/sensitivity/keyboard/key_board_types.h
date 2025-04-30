#ifndef KEY_BOARD_TYPES_H
#define KEY_BOARD_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef union{
    uint8_t byte;
    struct{
    	uint8_t num_lock :1;
    	uint8_t caps_lock :1;
    	uint8_t scroll_lock :1;
    	uint8_t res :5;
    };
}LedStatus_t;

typedef struct {
	LedStatus_t led;
}KeyBoard_t;

#ifdef __cplusplus
}
#endif

#endif /* KEY_BOARD_TYPES_H */
