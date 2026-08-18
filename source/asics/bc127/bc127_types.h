#ifndef BC127_TYPES_H
#define BC127_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "bc127_const.h"

typedef struct {
    uint8_t bits_per_sample;
    Bc127I2sBusRole_t bus_mode;
    BC127JustifyFormat_t justify_format;
    BC127LeftJustifyDelay_t left_justify_delay;
    BC127ChannelPolarity_t channel_polarity;
    BC127JustifyResolution_t justify_resolution;
    BC127CropEnable_t crop_enable;
    BC127StratSampling_t start_rx_sampling;
    BC127StratSampling_t start_tx_sampling;
    uint32_t scaling_factor;
    uint8_t audio_attenuation;
    BC127AudioAttenuationEnable_t audio_attenuation_en;
}Bc127I2sParam_t;

typedef struct {
    uint32_t digital_rate;
    BC127DigitalFormat_t digital_format;
    Bc127I2sParam_t i2s_param;
}Bc127Config_t;

typedef struct  {
    uint16_t err_code;
    char* name;
}ErrCodeName_t;

typedef struct  {
    bool busy;
    uint8_t link_id;
    uint8_t volume;
    char name[6];
}LinkVolume_t;

typedef union {
    uint32_t reg_val;
    struct { //eDigitalFormatI2s_t
        uint32_t start_rx_sampling         :1;/*Bit0*/
        uint32_t start_tx_sampling         :1;/*Bit1*/
        uint32_t crop_enable               :1;/*Bit2*/
        uint32_t justify_resolution        :2;/*Bit3-4*/
        uint32_t res1                      :2;/*Bit5-6*/
        uint32_t audio_attenuation_enable  :1;/*Bit7*/
        uint32_t channel_polarity          :1;/*Bit8*/
        uint32_t left_justify_delay        :1;/*Bit9*/
        uint32_t justify_format            :1;/*Bit10*/
        uint32_t mode                      :1;/*Bit11*/
        uint32_t audio_attenuation         :4;/*Bit12-15*/
        uint32_t bits_per_sample           :8;/*Bit16-23*/
        uint32_t res2                      :8;/*Bit24-31*/
    };
}Bc127Param2_t;

typedef struct {
    char cur_line[BC127_MAX_LINE_SZ];
    char fix_line[BC127_MAX_LINE_SZ];
    uint32_t line_cnt;
    uint32_t pos;
    uint32_t digital_rate;
    uint32_t ack_cnt;
    uint16_t err_code;
    Bc127I2sParam_t i2s_param;
    BC127DigitalFormat_t digital_format;
    uint32_t param_1;
    LinkVolume_t  LinkVolume[5];
    Bc127Param2_t Param2;
    bool ack;
}Bc127Handle_t;


#endif /* BC127_TYPES_H */
