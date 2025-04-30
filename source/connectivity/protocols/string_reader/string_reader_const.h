#ifndef READER_CONST_H
#define READER_CONST_H

#include "string_reader_dep.h"
#include "ascii_const.h"

#define PREV_CMD_MAX_LEN 100
#define STRING_READER_PERIOD_US 10000

#define STRING_READER_HISTORY_FILE "hist.txt"

typedef enum {
    ARROW_UP = 1,
    ARROW_DOWN = 2,
    ARROW_LEFT = 3,
    ARROW_RIGHT = 4,

    ARROW_UNDEF = 0,
} Arrow_t;

#endif /*READER_CONST_H*/
