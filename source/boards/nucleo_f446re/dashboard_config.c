#include "dashboard_config.h"

#include "data_utils.h"
#include "dashboard_const.h"

const DashBoardConfig_t DashBoardConfig[] = {
    {.num=1, .valid=true, .display_num=1, },
};

DashBoardHandle_t DashBoardInstance[]={
     {.num=1, .valid=true,},
};

COMPONENT_GET_CNT(DashBoard, dashboard)

