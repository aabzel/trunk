#ifndef ADC_DRIVER_GENERAL_API_H
#define ADC_DRIVER_GENERAL_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
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
bool AdcIsValidConfig(const AdcConfig_t* const Config);
bool adc_proc(void);
bool adc_proc_one(uint8_t num);
void AdcConvCpltCallback(AdcHandle_t* Node) ;

/*ADC*/
AdcHandle_t* AdcGetNode(AdcNum_t adc_num);
const AdcConfig_t* AdcGetConfig(AdcNum_t adc_num);

/*init */
bool adc_init_custom(void);
bool adc_init_one(uint8_t num);
bool adc_init_common(const AdcConfig_t* const Config, AdcHandle_t* const Node);
bool adc_mcal_init(void);

bool adc_wait_convert_done_ll(AdcHandle_t* Node, uint32_t time_out_ms) ;


/*Get*/
float AdcSample12ToVoltageVef3_3(const uint32_t sample);
float AdcCode2Voltage(const int32_t code);
bool adc_is_valid_num(AdcNum_t adc_num);

/*setters*/
bool adc_wait_conv_done_ll(AdcHandle_t* Node, uint32_t time_out_ms) ;
bool adc_start(uint8_t num );
bool adc_set_vref(uint8_t adc_num, float v_ref_voltage);



#ifdef __cplusplus
}
#endif

#endif /* ADC_DRIVER_GENERAL_API_H */
