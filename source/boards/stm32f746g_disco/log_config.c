#include "log_config.h"

#include "data_utils.h"

const LogConfig_t SECTION_CFG_DATA LogConfig[1] = {
    {
        .num = 1,
        .valid = true,
        .colored = true,
        .time_stamp = true,
#ifdef HAS_UART
        .inter_face = {.interface_name = INTERFACE_NAME_UART, .num = 1,},
#endif
    },
};

LogHandle_t LogInstance[1] = {
    {
      .num = 1,
      .valid = true,
      .serial_nun = 0,
      .time_stamp = true,
      .colored = true,
#ifdef HAS_UART
      .inter_face = {.interface_name = INTERFACE_NAME_UART, .num = 1,},
#endif
    },
};


COMPONENT_GET_CNT(Log, log)

