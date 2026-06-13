#include "dashboard_config.h"

#include "data_utils.h"
#include "dashboard_const.h"

const DashBoardConfig_t DashBoardConfig[] = {
      {.num=1, .valid=true, .display_num=1, .light_nav_num=1, .ds3231_num=1, .bh1750_num=1, },
};

DashBoardHandle_t DashBoardInstance[]={
     {.num=1, .valid=true,},
};

COMPONENT_GET_CNT(DashBoard, dashboard)

