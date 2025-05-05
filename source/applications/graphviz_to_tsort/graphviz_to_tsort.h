#ifndef GRAPHVIZ_TO_TSORT_H
#define GRAPHVIZ_TO_TSORT_H

#include <stdbool.h>
//#include <stdint.h>

#include "graphviz_to_tsort_config.h"
#include "graphviz_to_tsort_types.h"
#include "graphviz_to_tsort_diag.h"

bool gra_tsort_get_spare_line(GraphvizToTsortHandle_t* Node, uint32_t* spare);
bool gra_tsort_is_dest_known(GraphvizToTsortHandle_t* Node, uint32_t* line);

bool graphviz_to_tsort_proc_line(GraphvizToTsortHandle_t* Node, char* file_line);
bool graphviz_to_tsort_proc_gv( const char* const file_name);
bool graphviz_to_tsort_init(void);
bool graphviz_to_tsort_proc(void);

#endif /* GRAPHVIZ_TO_TSORT_H */
