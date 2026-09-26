#include "histogram_config.h"

#include "data_utils.h"
#include "common_const.h"
#include "histogram_const.h"

static uint32_t HistogramData[1023*16]={0};

const HistogramConfig_t HistogramConfig[] = {
    {
      .num=1,
      .valid = true,
      .size = ARRAY_SIZE(HistogramData),
      .frequency = HistogramData,
      .min_val = 0,
      .max_val=1023*16,
      .resolution=1,
    },
};

HistogramHandle_t HistogramInstance[]={
    {.num=1, .valid=true,},
};

COMPONENT_GET_CNT(Histogram, histogram)

