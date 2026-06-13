#ifndef DASHBOARD_CONFIG_H
#define DASHBOARD_CONFIG_H

#include "std_includes.h"
#include "dashboard_types.h"

extern const DashBoardConfig_t DashBoardConfig[];
extern DashBoardHandle_t DashBoardInstance[];

uint32_t dashboard_get_cnt(void);

#endif /* DASHBOARD_CONFIG_H */
