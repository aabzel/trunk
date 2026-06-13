#include "adc_config.h"

#include "log_config.h"
#include "data_utils.h"
#include "adc_const.h"
#include "macro_utils.h"

uint16_t Adc1RxSamples[ADC1_RX_SAMPLE_CNT]={0};


uint16_t Adc1FifoSamples[ADC1_RX_SAMPLE_CNT*2]={0};

/*constant compile-time known settings*/
const AdcConfig_t AdcConfig[] = {
#ifdef HAS_ADC1
    { .num = 1,
      .move_mode = MOVE_MODE_DMA,
      .RxSamples = Adc1RxSamples,
      .RxSamplesCnt = ARRAY_SIZE(Adc1RxSamples),
      .irq_priority = 0,
      .resolution = 12,
      .name = "ADC1",
      .v_ref_voltage = 3.3,
      .trigger_source = ADC_MCAL_TRIG_SRC_EXT_TIRER2_TRGO,
      .SampleFifoMem = Adc1FifoSamples,
      .SampleFifoMemCnt = ARRAY_SIZE(Adc1FifoSamples),
      .valid = true,
    },
#endif
};

AdcHandle_t AdcInstance[]={
#ifdef HAS_ADC1
    {.num = 1, .valid = true,    },
#endif
};

COMPONENT_GET_CNT(Adc,adc)
