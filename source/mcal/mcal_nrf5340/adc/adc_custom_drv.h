
#ifndef ADC_CONST_DRV_H
#define ADC_CONST_DRV_H

#include <stdint.h>

uint32_t AdcResol2MaxValue(uint8_t resolution);
const AdcChannelStaticInfo_t* AdcGetChannelInfo(AdcChannel_t chan_num);

#endif /* ADC_CONST_DRV_H  */
