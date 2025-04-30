#ifndef SCAN_CONST_H
#define SCAN_CONST_H

#include "scan_dep.h"


typedef enum {
    SCAN_STATE_ACC= 1,
    SCAN_STATE_CAPTURE = 2,
    SCAN_STATE_UNDEF = 0,
}ScanState_t;

typedef enum {
    SCAN_INPUT_DOWN= 1,
    SCAN_INPUT_UP = 2,
    SCAN_INPUT_TIME_OUT= 3,
    SCAN_INPUT_UNDEF = 0,
}ScanInput_t;

typedef enum {
    SCAN_ACTION_CRLF = 1,
    SCAN_ACTION_NONE = 2,
    SCAN_ACTION_UNDEF = 0,
}ScanAction_t;

#endif /* SCAN_CONST_H  */
