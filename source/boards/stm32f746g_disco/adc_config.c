#include "adc_config.h"

#include "log_config.h"
#include "data_utils.h"
#include "adc_const.h"

static uint16_t AdcSamples[6]={0};

/*constant compile-time known settings*/
const AdcConfig_t SECTION_CFG_DATA AdcConfig[] = {
#ifdef HAS_ADC1
    {
      .num = 1,
      .name = "Adc",
      .valid = true,
      .trigger_source = ADC_MCAL_TRIG_SRC_EXT_TIRER2_TRGO,
      .num_of_conversion = 5,
      .RxSamples = AdcSamples,
      .RxSamplesCnt = ARRAY_SIZE(AdcSamples),
      .move_mode =MOVE_MODE_DMA  ,
      .irq_priority = 4,
      .resolution = 12,
      .v_ref_voltage = 3.0f,
    },
#endif
};

AdcHandle_t AdcInstance[] = {
#ifdef HAS_ADC1
    {.num = 1, .valid = true,    },
#endif
};

COMPONENT_GET_CNT(Adc, adc)

