#ifndef NOR_END_OF_BLOCK_TYPES_H
#define NOR_END_OF_BLOCK_TYPES_H

#include <stdio.h>

#include "std_includes.h"
#include "data_types.h"
#include "end_of_block_const.h"
#include "lifo_array_types.h"

typedef struct {
    uint32_t line_number;
    BraceDir_t dir;
    uint8_t code;
}BraceInfo_t;

#define END_OF_BLOCK_COMMON_VARIABLES         \
    bool valid;                               \
    char filename[30];

typedef struct {
    END_OF_BLOCK_COMMON_VARIABLES
} EndOfBlockConfig_t;

typedef struct {
    END_OF_BLOCK_COMMON_VARIABLES
    bool init;
    char fileNameC[800];
    char fileShortName[100];
    char ReportFileName[100];
    char curLine[END_OF_BLOCK_MAX_LINE_SIZE];
    FILE* filePtr;
    uint32_t line_threshold;
    uint32_t err_cnt;
    uint32_t pair_cnt;
    uint32_t ok_counter;
    uint32_t violation_counter;
    uint32_t ok_cnt;
    uint32_t cur_line;
    LifoArray_t LifoArray;
} EndOfBlockHandle_t;

#endif /* NOR_END_OF_BLOCK_TYPES_H */
