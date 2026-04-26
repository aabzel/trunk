#ifndef ADC_GENERAL_CONST_H
#define ADC_GENERAL_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAS_ADC_CUSTOM
#include "adc_custom_const.h"
#endif

#include "adc_dep.h"
#include "bit_const.h"
#include "time_mcal.h"

#define ADC_POLL_PERIOD_US 1
#define ADC_CHANNEL_PERIOD_US MSEC_2_USEC(5)

typedef enum {
    ADC_0 = 0,
    ADC_1 = 1,
    ADC_2 = 2,
    ADC_3 = 3,
    ADC_4 = 4,

    ADC_UNDEF = 200,
} AdcNum_t;

typedef enum {
    ADC_RESOLUTION_6BIT = 6,
    ADC_RESOLUTION_8BIT = 8,
    ADC_RESOLUTION_10BIT = 10,
    ADC_RESOLUTION_12BIT = 12,
    ADC_RESOLUTION_14BIT = 14,

    ADC_RESOLUTION_UNDEF = 0,
} AdcResolution_t;

typedef enum {
    ADC_MAX_VAL_6BIT = 63,
    ADC_MAX_VAL_8BIT = 255,
    ADC_MAX_VAL_10BIT = 1023,
    ADC_MAX_VAL_12BIT = 4095,
    ADC_MAX_VAL_14BIT = 16383,
    ADC_MAX_VAL_UNDEF = 0,
} AdcMaxVal_t;

typedef enum {
    ADC_MCAL_TRIG_SRC_UNDEF = 0 ,    //
    ADC_MCAL_TRIG_SRC_SOFTWARE_START    ,    //
    ADC_MCAL_TRIG_SRC_EXT_TIRER2_TRGO ,      //
    ADC_MCAL_TRIG_SRC_EXT_TIRER3_TRGO ,      //
    ADC_MCAL_TRIG_SRC_EXT_TIRER8_TRGO ,      //
    ADC_MCAL_TRIG_SRC_EXT_TIRER1_COM_CH1  ,  //
    ADC_MCAL_TRIG_SRC_EXT_TIRER1_COM_CH2  ,  //
    ADC_MCAL_TRIG_SRC_EXT_TIRER1_COM_CH3  ,  //
    ADC_MCAL_TRIG_SRC_EXT_TIRER2_COM_CH2  ,  //
    ADC_MCAL_TRIG_SRC_EXT_TIRER2_COM_CH3  ,  //
    ADC_MCAL_TRIG_SRC_EXT_TIRER2_COM_CH4  ,  //
    ADC_MCAL_TRIG_SRC_EXT_TIRER3_COM_CH1  ,  //
    ADC_MCAL_TRIG_SRC_EXT_TIRER4_COM_CH4  ,  //
    ADC_MCAL_TRIG_SRC_EXT_TIRER5_COM_CH1  ,  //
    ADC_MCAL_TRIG_SRC_EXT_TIRER5_COM_CH2  ,  //
    ADC_MCAL_TRIG_SRC_EXT_TIRER5_COM_CH3  ,  //
    ADC_MCAL_TRIG_SRC_EXT_TIRER8_COM_CH1  ,  //
    ADC_MCAL_TRIG_SRC_EXT_IT11 ,             //
} AdcExternalTriggerSource_t;


#ifdef __cplusplus
}
#endif

#endif /* ADC_GENERAL_CONST_H  */
