#include "delta_sigma_config.h"

#include "data_utils.h"

const DeltaSigmaConfig_t SECTION_CFG_DATA DeltaSigmaConfig[] = {
    {
      .num = 1,
      .valid = true,
      .target = 1500,
      .min = 0,
      .Pad = {.port=PORT_D, .pin=14,},
      .max = 3300,
      .comparator_middle = 1650,
      .sample_frequency_hz = 48000,
    },
};

DeltaSigmaHandle_t DeltaSigmaInstance[]={
    {.num=1, .valid=true,},
};


COMPONENT_GET_CNT(DeltaSigma, delta_sigma)

