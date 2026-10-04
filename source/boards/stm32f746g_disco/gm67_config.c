#include "gm67_config.h"

#include "data_utils.h"

static uint8_t Gm67RxArray1[32];

const Gm67Config_t Gm67Config[] = {
    {
      .num = 1,
      .uart_num = 1,
      .name = "Gm671",
      .rx_array_size = sizeof(Gm67RxArray1),
      .RxArray = Gm67RxArray1,
      .valid = true,
    },
};

Gm67Handle_t Gm67Instance[] = {
    {.num = 1, .valid = true, },
};

COMPONENT_GET_CNT(Gm67, gm67)


