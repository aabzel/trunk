#ifndef TOPO_SORT_DRV_H
#define TOPO_SORT_DRV_H

/*TOPO_SORT receiver invariant component*/
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

#include "topo_sort_diag.h"
#include "topo_sort_types.h"
#include "topo_sort_config.h"

TopoSortHandle_t* TopoSortGetNode(uint8_t num);
const TopoSortConfig_t* TopoSortGetConfig(uint8_t num);

bool topo_sort_load_dep(uint8_t num, char* const sw_dep);
bool topo_sort_run(uint8_t num, char* const sw_comps, char* const sw_dep);
bool topo_sort_proc_ll(TopoSortHandle_t* Node);
bool topo_sort_init_one(uint8_t num);
bool topo_sort_mcal_init(void);
bool topo_sort_init_custom(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*TOPO_SORT_DRV_H*/
