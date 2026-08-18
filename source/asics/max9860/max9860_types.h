#ifndef MAX9860_TYPES_H
#define MAX9860_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "max9860_registers_types.h"
#include "max9860_const.h"
#include "audio_types.h"


typedef int8_t AdcGain_t;
typedef int8_t SideToneGain_t;

typedef struct {
    Max9860RegAddr_t addr;
    Max9860RegUniversal_t value;
}Max9860RegVal_t;

typedef struct {
    Max9860RegAddr_t addr;
    char* name;
}Max9860RegName_t;

typedef struct{
    bool dac_en;
    bool adc_left_en;
    bool adc_right_en;
    uint8_t i2c_num;
    uint8_t i2s_num;
    Gain_t dac_attenuation;
    Gain_t dac_gain;
    uint32_t mclk_hz;
    uint32_t lrclk_hz;
    Max9860I2sRole_t i2s_role;
    Max9860interface_t interface;
    bool stereo;
}Max9860Config_t;



typedef struct{
    bool dac_en;
    bool adc_left_en;
    bool adc_right_en;
    uint8_t i2c_num;
    uint8_t i2s_num;
    Gain_t dac_attenuation;
    Gain_t dac_gain;
    uint32_t mclk_hz;
    uint32_t lrclk_hz;
    Max9860I2sRole_t i2s_role;
    Max9860interface_t interface;
    bool stereo;
}Max9860Item_t;


#endif /* MAX9860_TYPES_H */
