#ifndef DASHBOARD_TYPES_H
#define DASHBOARD_TYPES_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "dashboard_const.h"
#include "dashboard_dep.h"

#define DASHBOARD_COMMON_VARIABLES                 \
    uint8_t num;                                    \
    uint8_t display_num;            \
    uint8_t rtc_num;             \
    uint8_t light_sensor_num;       \
    uint8_t light_nav_num;          \
    bool valid;

typedef struct {
    DASHBOARD_COMMON_VARIABLES
    char name[10];
} DashBoardConfig_t;

typedef struct {
    DASHBOARD_COMMON_VARIABLES
    char text[300];
    bool init_done;
    double lighting;
    struct tm time_date;
} DashBoardHandle_t;


#ifdef __cplusplus
}
#endif

#endif /* DASHBOARD_TYPES_H */
