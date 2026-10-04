#include "adc_channel_config.h"

#include "log_config.h"
#include "data_utils.h"

/*constant compile-time known settings*/
const AdcChannelConfig_t AdcChannelConfig[]={
#ifdef HAS_ADC1
    {.num=1,   .AdcCh={ .adc=1, .channel=ADC_CHAN_0,  }, .Pad={ .port=PORT_A, .pin=0,} , .scale=2.0f, .sequence=1, .name="AI_1", .valid=true,},
    {.num=2,   .AdcCh={ .adc=1, .channel=ADC_CHAN_1,  }, .Pad={ .port=PORT_A, .pin=1,} , .scale=2.0f, .sequence=2, .name="AI_2", .valid=true,},
    {.num=3,   .AdcCh={ .adc=1, .channel=ADC_CHAN_2,  }, .Pad={ .port=PORT_A, .pin=2,} , .scale=2.0f, .sequence=3, .name="AI_3", .valid=true,},
    {.num=4,   .AdcCh={ .adc=1, .channel=ADC_CHAN_3,  }, .Pad={ .port=PORT_A, .pin=3,} , .scale=2.0f, .sequence=4, .name="AI_4", .valid=true,},
    {.num=5,   .AdcCh={ .adc=1, .channel=ADC_CHAN_4,  }, .Pad={ .port=PORT_A, .pin=4,} , .scale=2.0f, .sequence=5, .name="AI_VS_5V", .valid=true,},
    {.num=16,  .AdcCh={ .adc=1, .channel=ADC_CHAN_15, }, .Pad={ .port=PORT_A, .pin=0,} , .scale=1.0f, .sequence=6, .name="Temp", .valid=true,},
#endif
};

AdcChannelHandle_t AdcChannelInstance[] = {
#ifdef HAS_ADC1
    {.num = 1,  .AdcCh={ .adc=1, .channel = ADC_CHAN_0,  }, .valid = true, .code = 0, },
    {.num = 2,  .AdcCh={ .adc=1, .channel = ADC_CHAN_1,  }, .valid = true, .code = 0, },
    {.num = 3,  .AdcCh={ .adc=1, .channel = ADC_CHAN_2,  }, .valid = true, .code = 0, },
    {.num = 4,  .AdcCh={ .adc=1, .channel = ADC_CHAN_3,  }, .valid = true, .code = 0, },
    {.num = 5,  .AdcCh={ .adc=1, .channel = ADC_CHAN_4,  }, .valid = true, .code = 0, },
    {.num = 6,  .AdcCh={ .adc=1, .channel = ADC_CHAN_5,  }, .valid = true, .code = 0, },
    {.num = 7,  .AdcCh={ .adc=1, .channel = ADC_CHAN_6,  }, .valid = true, .code = 0, },
    {.num = 8,  .AdcCh={ .adc=1, .channel = ADC_CHAN_7,  }, .valid = true, .code = 0, },
    {.num = 9,  .AdcCh={ .adc=1, .channel = ADC_CHAN_8,  }, .valid = true, .code = 0, },
    {.num = 10, .AdcCh={ .adc=1, .channel = ADC_CHAN_9,  }, .valid = true, .code = 0, },
    {.num = 11, .AdcCh={ .adc=1, .channel = ADC_CHAN_10, }, .valid = true, .code = 0, },
    {.num = 12, .AdcCh={ .adc=1, .channel = ADC_CHAN_11, }, .valid = true, .code = 0, },
    {.num = 13, .AdcCh={ .adc=1, .channel = ADC_CHAN_12, }, .valid = true, .code = 0, },
    {.num = 14, .AdcCh={ .adc=1, .channel = ADC_CHAN_13, }, .valid = true, .code = 0, },
    {.num = 15, .AdcCh={ .adc=1, .channel = ADC_CHAN_14, }, .valid = true, .code = 0, },
    {.num = 16, .AdcCh={ .adc=1, .channel = ADC_CHAN_15, }, .valid = true, .code = 0, },
#if 0
#endif
#endif
};

COMPONENT_GET_CNT(AdcChannel, adc_channel)

