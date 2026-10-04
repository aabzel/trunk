#include "delta_sigma_config.h"

#include "data_utils.h"

const DeltaSigmaConfig_t SECTION_CFG_DATA DeltaSigmaConfig[] = {
    {
      .num = 1,
      .valid = true,
      .target = 1.5,
      .min = 0,
      .max = 3.3,
      .comparator_middle = 1.65,
      .sample_frequency_hz = 48000,
    },
};

DeltaSigmaHandle_t DeltaSigmaInstance[]={
    {.num=1, .valid=true,},
};


COMPONENT_GET_CNT(DeltaSigma, delta_sigma)

