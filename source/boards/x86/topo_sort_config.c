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

uint32_t topo_sort_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(TopoSortInstance);
    cnt2 = ARRAY_SIZE(TopoSortConfig);
    if(cnt1==cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
