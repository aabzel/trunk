#include "log_config.h"

#include "data_utils.h"

const LogConfig_t LogConfig[] = {
    {
        .num = 1,
        .valid = true,
        .colored = true,
        .time_stamp = true,
#ifdef HAS_INTERFACES
        .inter_face = {.interface_name=INTERFACE_NAME_STDIO, .num=0,},
#endif
    },
};

LogHandle_t LogInstance[] = {
        {    .num = 1,    .valid = true,},
};

COMPONENT_GET_CNT(Log, log)

