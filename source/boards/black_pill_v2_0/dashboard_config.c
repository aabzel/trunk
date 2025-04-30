#include "dashboard_config.h"

#include "data_utils.h"
#include "dashboard_const.h"

const DashBoardConfig_t DashBoardConfig[] = {
      {.num=1,  .valid=true, .ssd1306_num=1, },
};

DashBoardHandle_t DashBoardInstance[]={
     {.num=1, .valid=true,},
};

uint32_t dashboard_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(DashBoardInstance);
    cnt2 = ARRAY_SIZE(DashBoardConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
