#ifndef ADC_CUSTOM_CONST_H
#define ADC_CUSTOM_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "bit_const.h"

#define ADC_CUSTOM_DRV_VER 2

#define ADC_REF_VOLTAGE (3.3)
#define CODE_AT_3_3V (MAX_VALUE_12BIT)
#define CROSS_CODE_VOLTAGE (ADC_REF_VOLTAGE / CODE_AT_3_3V)


#ifdef __cplusplus
}
#endif

#endif /* ADC_CUSTOM_CONST_H  */
