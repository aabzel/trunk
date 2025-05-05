#ifndef END_OF_BLOCK_CONST_H
#define END_OF_BLOCK_CONST_H


#include "end_of_block_dep.h"

#define END_OF_BLOCK_MAX_LINE_SIZE 500
#define END_OF_BLOCK_DRIVER_VERSION 1
#define END_OF_BLOCK_ID 0x15
#define END_OF_BLOCK_REPORT_FILE "end_of_report.txt"

typedef enum {
    BRACE_DIR_OPEN = 1,   // {
    BRACE_DIR_CLOSE = 2,  // }



    //PARENTHESIS_DIR_OPEN = 3,   // (
    //PARENTHESIS_DIR_CLOSE = 4,  // )
    BRACE_DIR_UNDEF = 0,  //
}BraceDir_t;

#endif /* END_OF_BLOCK_CONST_H */
