#ifndef CSV_CONST_H
#define CSV_CONST_H

#define CSV_VAL_MAX_SIZE 80

typedef enum {
    CSV_STATE_INIT = 1,
    CSV_STATE_ACCUMULATE = 2,
    CSV_STATE_SEP = 3,
    CSV_STATE_END = 4,

    CSV_STATE_UNDEF = 0,
} CsvState_t;

typedef enum {
    CSV_INPUT_NOT_SEP = 1,
    CSV_INPUT_SEP = 2,
    CSV_INPUT_END = 3,

    CSV_INPUT_UNDEF = 0,
} CsvInput_t;

typedef enum {
    CSV_ORVER_FORWARD = 1,
    CSV_ORVER_REVERSE = 2,
    CSV_ORVER_UNDEF = 0,
} Order_t;



#endif
