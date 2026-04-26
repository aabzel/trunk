#ifndef ADC_CHANNEL_DRIVER_GENERAL_API_H
#define ADC_CHANNEL_DRIVER_GENERAL_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "adc_channel_types.h"
#include "adc_channel_config.h"
#include "gpio_types.h"

#ifdef HAS_ADC_CHANNEL_DIAG
#include "adc_channel_diag.h"
#endif

#ifdef HAS_ADC_CHANNEL_CUSTOM
#include "adc_custom_types.h"
#include "adc_channel_custom_drv.h"
#endif

/*API*/
bool adc_channel_init(uint8_t adc_num, AdcChannel_t channel);
#ifdef HAS_ADC_CHANNEL_CUSTOM
const AdcChannelInfo_t* AdcChannelToInfo(uint8_t adc_num, AdcChannel_t channel) ;
#endif

/*ADC*/
const AdcChannelConfig_t* AdcChannelGetConfig(uint8_t num);
const AdcChannelConfig_t* AdcChannelGetConfigV2(AdcNum_t adc_num, AdcChannel_t channel);
bool AdcChannelGetVoltage(uint8_t node_num, float* const voltage_scale);

AdcChannelHandle_t* AdcChannelGetNodeV2(AdcNum_t adc_num, AdcChannel_t channel);
AdcChannelHandle_t* AdcChannelGetNode(uint8_t num);

/*init */
bool adc_channel_init_node(const AdcChannelConfig_t* const Config, AdcChannelHandle_t*  const Node);
bool adc_channel_init_custom(void);
bool adc_channel_init_one(uint8_t num);
bool adc_channel_mcal_init(void);

bool adc_channel_proc_one(uint8_t num);
bool adc_channel_proc(void);

Pad_t AdcChannel2Pad(AdcNum_t adc_num, AdcChannel_t channel);
uint32_t AdcCode2mV(AdcNum_t adc_num, AdcChannel_t channel, int32_t code);


/*Get*/
AdcChannel_t AdcPad2Channel(Pad_t pad);
bool adc_code_to_params(AdcChannelHandle_t* const Channel) ;
bool adc_is_valid_channel(AdcChannel_t channel);
bool adc_channel_read_code(AdcNum_t adc_num, AdcChannel_t channel, int32_t* const code);
bool adc_channel_read_voltage(AdcNum_t adc_num, AdcChannel_t channel, float* const voltage);
bool adc_pad_read_code(Pad_t pad, int32_t* code);
bool adc_pad_read_voltage(Pad_t pad, float* const voltage);
float adc_channel_read_voltage_short(AdcNum_t adc_num, AdcChannel_t channel);
float adc_pad_read_voltage_short(Pad_t pad);
float AdcChannelGetVoltageScale(uint8_t num);


#ifdef __cplusplus
}
#endif

#endif /* ADC_DRIVER_GENERAL_API_H */
