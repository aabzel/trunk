#ifndef NOR_GRAPHVIZ_TO_TSORT_TYPES_H
#define NOR_GRAPHVIZ_TO_TSORT_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "data_types.h"
#include "graphviz_to_tsort_const.h"

#define GRAPHVIZ_TO_TSORT_COMMON_VARIABLES             \
    bool valid;                                        \
    char* gv_filename;                                 \
    char* tsort_file;

typedef struct {
    GRAPHVIZ_TO_TSORT_COMMON_VARIABLES
} GraphvizToTsortConfig_t;

typedef struct {
    GRAPHVIZ_TO_TSORT_COMMON_VARIABLES
    char GraphVizFile[500];
    bool init;
    uint32_t char_cnt;
    char letter;
    char prev_letter;

    char Source[TOKEN_SIZE];;
	uint32_t s;

    char Destination[TOKEN_SIZE];
	uint32_t d;

    GraTsortState_t state;
    GraTsortInput_t input;
//    char AdjacencyList[MAX_COMP_CNT][DEP_CSV_SIZE];
} GraphvizToTsortHandle_t;

#endif /* NOR_GRAPHVIZ_TO_TSORT_TYPES_H */
