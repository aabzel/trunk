#include "delta_sigma_config.h"

#include "timer_config.h"
#include "data_utils.h"

const DeltaSigmaConfig_t DeltaSigmaConfig[] = {
    {
      .num = 1,
      .timer_num = TIMER_NUM_DELTA_SIGMA,
      .valid = true,
      .target = 1.0f,
      .min = 0.0f,
      .max = 100.0f,
      .comparator_middle = 50.0f,
      .sample_frequency_hz = 20000,
      .name = "LED",
      .Pad = {.port = PORT_E, .pin = 4, },
    },
};

DeltaSigmaHandle_t DeltaSigmaInstance[]={
    {.num = 1, .valid = true,},
};

COMPONENT_GET_CNT(DeltaSigma, delta_sigma)

