#ifndef HEALTH_MONITOR_TYPES_H
#define HEALTH_MONITOR_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>


#ifndef HAS_HEALTH_MONITOR
#error "+HAS_HEALTH_MONITOR"
#endif

#include "health_monitor_const.h"

typedef struct {
    bool init_error;
    bool power;
    uint32_t error_cnt;
    uint32_t crc_error_cnt;
    uint16_t init_error_cnt;
    char error_messege[ERR_MSG_SIZE];
} HealthMon_t;



#ifdef __cplusplus
}
#endif

#endif /* HEALTH_MONITOR_TYPES_H */
