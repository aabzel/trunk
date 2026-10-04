#include "topo_sort_config.h"

#include "data_utils.h"

const TopoSortConfig_t TopoSortConfig[] = {
    {
      .num = 1,
      .valid = true,
    },
};

TopoSortHandle_t TopoSortInstance[]={
    {.num=1, .valid=true,}
};


COMPONENT_GET_CNT(TopoSort, topo_sort)

