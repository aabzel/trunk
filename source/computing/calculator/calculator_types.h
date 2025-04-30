#ifndef CALCULATOR_TYPES_H
#define CALCULATOR_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "calculator_const.h"
#include "lifo_array.h"
#include "stack_frame_types.h"
#include "convert.h"

typedef struct {
	double val_left;
	double val_right;
	Operation_t operation;
	double result;
}OperationData_t;

typedef struct {
    char cur_char;
    char prev_char;
    char prev_prev_char;
    double result;
    int8_t number_sign; // 1 or -1
    double number;
    char *text;
    LifoArray_t LifoArray;
    Text2NumberFsm_t NumberFsm;
    //StackFrameHandle_t StackFrame;
}Calculator_t;

#ifdef __cplusplus
}
#endif

#endif /* CALCULATOR_TYPES_H */
