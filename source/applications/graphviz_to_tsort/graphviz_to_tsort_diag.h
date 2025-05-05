#ifndef GRAPHVIZ_TO_TSORT_DIAG_H
#define GRAPHVIZ_TO_TSORT_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "graphviz_to_tsort_types.h"

bool graphviz_to_tsort_diag(void);
bool GraphvizToTsortDiag(const  GraphvizToTsortHandle_t* const Node);
bool graphviz_to_tsort_print(const GraphvizToTsortHandle_t* const Node);
const char* GraphvizToTsortDiagToStr(const GraphvizToTsortHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* GRAPHVIZ_TO_TSORT_DIAG_H */
