#ifndef TOPO_SORT_CONFIG_H
#define TOPO_SORT_CONFIG_H

#include <stdbool.h>

#include "topo_sort_types.h"

extern const TopoSortConfig_t TopoSortConfig[];
extern TopoSortHandle_t TopoSortInstance[];

uint32_t topo_sort_get_cnt(void);

#endif /* TOPO_SORT_CONFIG_H  */
