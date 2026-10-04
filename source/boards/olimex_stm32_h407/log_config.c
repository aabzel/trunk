#include "log_config.h"

#include "data_utils.h"

const LogConfig_t SECTION_CFG_DATA LogConfig[] = {
    {
        .num = 1,
        .valid = true,
        .colored = true,
        .time_stamp = true,
#ifdef HAS_UART3
        .inter_face = {.interface_name = INTERFACE_NAME_UART,
                       .num=3, 
                       },
#endif
    },
#ifdef HAS_USB
    {
        .num = 2,
        .valid = true,
        .colored = false,
        .time_stamp = true,
        .inter_face = IF_USB_HID,
    },
#endif
};

LogHandle_t LogInstance[] = {
        {    .num = 1,    .valid = true,},
#ifdef HAS_USB
        {    .num = 2,    .valid = true,},
#endif
};

COMPONENT_GET_CNT(Log, log)
