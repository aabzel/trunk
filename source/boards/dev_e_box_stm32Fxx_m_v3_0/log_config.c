#include "log_config.h"

#include "data_utils.h"

const LogConfig_t SECTION_CFG_DATA LogConfig[1] = {
    {
        .num = 1,
        .valid = true,
        .colored = true,
        .time_stamp = true,
#ifdef HAS_UART1
        .inter_face = {
                        .interface_name = INTERFACE_NAME_UART,
                        .num = 1,
                      },
#endif
    },
};

LogHandle_t LogInstance[] = {
        {    .num = 1,    .valid = true,},
};

COMPONENT_GET_CNT(Log, log)
