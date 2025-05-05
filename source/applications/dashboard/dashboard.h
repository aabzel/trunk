#ifndef DASHBOARD_H
#define DASHBOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dashboard_config.h"
#include "dashboard_types.h"
#ifdef HAS_DASHBOARD_DIAG
#include "dashboard_diag.h"
#endif

const DashBoardConfig_t* DashBoardGetConfNode(uint8_t num);
DashBoardHandle_t* DashBoardGetNode(uint8_t num);

bool dashboard_proc(void);
bool dashboard_mcal_init(void);

#ifdef __cplusplus
}
#endif

#endif /* DASHBOARD_H */
