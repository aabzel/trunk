#ifndef ADC_DRIVER_GENERAL_API_H
#define ADC_DRIVER_GENERAL_API_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "adc_types.h"
#include "adc_config.h"
#include "gpio_types.h"
#ifdef HAS_ADC_DIAG
#include "adc_diag.h"
#endif

#ifdef HAS_ADC_CUSTOM
#include "adc_custom_drv.h"
#endif

/*API*/
/*proc*/
bool adc_proc(void);
bool adc_proc_one(uint8_t num);
bool adc_channel_proc(void);

const AdcChannelInfo_t* AdcChannelToInfo(uint8_t adc_num, AdcChannel_t channel) ;

/*ADC*/
const AdcConfig_t* AdcGetConfig(AdcNum_t adc_num);
AdcHandle_t* AdcGetNode(AdcNum_t adc_num);
/*Channel*/
const AdcChannelConfig_t* AdcChannelGetConfig(uint8_t num);
const AdcChannelConfig_t* AdcChannelGetConfigV2(AdcNum_t adc_num, AdcChannel_t channel);
bool AdcChannelGetVoltage(uint8_t node_num, double* const voltage_scale);
AdcChannelHandle_t* AdcChannelGetNodeV2(AdcNum_t adc_num, AdcChannel_t channel);
AdcChannelHandle_t* AdcChannelGetNode(uint8_t num);


/*init */
bool adc_channel_init_node(const AdcChannelConfig_t* const Config, AdcChannelHandle_t*  const Node);
bool adc_channel_init_custom(void);
bool adc_channel_init_one(uint8_t num);
bool adc_channel_mcal_init(void);
bool adc_init_custom(void);
bool adc_init_one(uint8_t num);
bool adc_mcal_init(void);


Pad_t AdcChannel2Pad(AdcNum_t adc_num, AdcChannel_t channel);
bool adc_wait_convert_done_ll(AdcHandle_t* Node, uint32_t time_out_ms) ;
uint32_t AdcCode2mV(AdcNum_t adc_num, AdcChannel_t channel, int32_t code);


/*Get*/
bool adc_is_valid_num(AdcNum_t adc_num);
AdcChannel_t AdcPad2Channel(Pad_t pad);
bool adc_is_valid_channel(AdcChannel_t channel);
bool adc_channel_read_code(AdcNum_t adc_num, AdcChannel_t channel, int32_t* const code);
bool adc_channel_read_voltage(AdcNum_t adc_num, AdcChannel_t channel, double* const voltage);
bool adc_pad_read_code(Pad_t pad, int32_t* code);
bool adc_pad_read_voltage(Pad_t pad, double* const voltage);
double adc_channel_read_voltage_short(AdcNum_t adc_num, AdcChannel_t channel);
double adc_pad_read_voltage_short(Pad_t pad);
double AdcChannelGetVoltageScale(uint8_t num);

/*setters*/
bool adc_start(uint8_t num );
bool adc_set_vref(uint8_t adc_num, double v_ref_voltage);



#ifdef __cplusplus
}
#endif

#endif /* ADC_DRIVER_GENERAL_API_H */
