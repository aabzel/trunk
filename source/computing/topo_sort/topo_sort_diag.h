#ifndef TOPO_SORT_DIAG_H
#define TOPO_SORT_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include  "topo_sort_types.h"

bool topo_sort_diag(uint8_t num);
const char* TopoSortConfigToStr(const TopoSortConfig_t* const Config);
const char* TopoSortNodeToStr(const TopoSortHandle_t* const Node);


#ifdef __cplusplus
}
#endif

#endif /* TOPO_SORT_DIAG_H */
