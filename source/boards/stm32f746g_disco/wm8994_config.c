#include "wm8994_config.h"

#include "data_utils.h"

const Wm8994Config_t Wm8994Config[] = {
    {
        .num = 1,
        .i2c_num = 3,
        .valid = true,
        .name = "WM89941",
    },
};

Wm8994Handle_t Wm8994Instance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(Wm8994, wm8994)


