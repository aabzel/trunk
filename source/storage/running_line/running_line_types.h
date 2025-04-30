#ifndef RUNNING_LINE_TYPES_H
#define RUNNING_LINE_TYPES_H

#include "std_includes.h"
#include "running_line_constants.h"

// linked list node in array
typedef struct {
    char letter;
    uint16_t next_i;
    //uint16_t cur_i;
    //uint16_t prev_i;
} RunningLineChar_t;

#define RUNNING_LINE_COMMON_VARIABLE                      \
    uint8_t num;                                          \
    bool valid;                                           \
    char* Text; /* data to show */                        \
    uint32_t size;   /* line length */                    \
    char* WindowText;                                     \
    RunningLineChar_t* Symbol;                            \
    uint32_t window_size;   /* visible window length */   \
    uint32_t duration_ms; /* duration of one position (period) */

typedef struct {
    RUNNING_LINE_COMMON_VARIABLE
} RunningLineConfig_t;


typedef struct {
    RUNNING_LINE_COMMON_VARIABLE
    uint32_t i_start; // index at which the string starts
    uint32_t len; // length of data in string
    uint32_t next_update_time_ms; /* duration of one position */
} RunningLineHandle_t;



#endif /* RUNNING_LINE_TYPES_H  */
