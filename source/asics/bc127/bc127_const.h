#ifndef BC127_CONST_H
#define BC127_CONST_H

#include "timer_utils.h"

#define BC127_MAX_LINE_SZ 80

#define BC127_PERIOD_US  MSEC_2_USEC(500)

#define BC127_AUDIO "AUDIO"
#define BC127_AUDIO_DIGITAL "AUDIO_DIGITAL"
#define BC127_ACK "OK"
#define BC127_WRITE "WRITE"
#define BC127_RESET "RESET"
#define BC127_AUTOCONN "AUTOCONN"
#define BC127_VOLUME "VOLUME"

typedef enum{
    DFOR_I2S=0,
    DFOR_PCM=1,
    DFOR_SDPIF=2,
    DFOR_UNDEF=3,
}BC127DigitalFormat_t;

typedef enum eBc127I2sBusRole_t{
    BC127_I2SMODE_SLAVE  = 0,
    BC127_I2SMODE_MASTER = 1,
    BC127_I2SMODE_UNDEF =2
}Bc127I2sBusRole_t ;

typedef enum eBC127JustifyFormat_t{
    JUST_FMT_LEFT=0,
    JUST_FMT_RIGHT=1,
    JUST_FMT_UNDEF=2,
}BC127JustifyFormat_t;

typedef enum eBC127JustifyResolution_t{
    JUST_RES_16_BIT=0,
    JUST_RES_20_BIT=1,
    JUST_RES_24_BIT=2,
    JUST_RES_RSVD=3,
    JUST_RES_UNDEF=4,
}BC127JustifyResolution_t;

typedef enum eBC127StratSampling_t{
    ST_SAM_LOW_WCLK_PHASE = 0,
    ST_SAM_HIGH_WCLK_PHASE = 1,
    ST_SAM_HIGH_WCLK_PHASE_UNDEF = 2,
}BC127StratSampling_t;

typedef enum eBC127CropEnable_t{
    CROP_EN_17_TO_16_BIT =0,
    CROP_EN_ONLY_16_BIT =1,
    CROP_EN_UNDEF=2,
}BC127CropEnable_t;

typedef enum eBC127ChannelPolarity_t{
    CH_POL_LEFT_WS_HIGH = 0,
    CH_POL_RIGHT_WS_HIGH = 1,
    CH_POL_UNDEF = 2,
}BC127ChannelPolarity_t;

typedef enum eBC127AudioAttenuationEnable_t{
    AUDIO_ATT_EN_17_TO_16_bit = 0,
    AUDIO_ATT_EN_12_15 = 1,
    AUDIO_ATT_EN_UNDEF=2,
}BC127AudioAttenuationEnable_t;

typedef enum eBC127LeftJustifyDelay_t{
    LEFT_JUST_DELAY_MSB_1ST_SCLK  =0,
    LEFT_JUST_DELAY_MSB_2ND_SCLK  =1,
    LEFT_JUST_DELAY_UNDEF=2,
}BC127LeftJustifyDelay_t;

#define ERROR_UNKNOWN        0X0003 // Unknown Error
#define ERROR_NOT_ALLOWED    0x0011 // Command not allowed with the current configuration
#define ERROR_CMD_NOT_FOUND  0x0012 // Command not found
#define ERROR_WRONG_PARAM    0x0013 // Wrong parameter
#define ERROR_WRONG_NUM      0x0014 // Wrong number of parameters
#define ERROR_STATE          0X0015 // Command not allowed in the current state
#define ERROR_ALREADY_CON    0x0016 // Device already connected
#define ERROR_NOT_CONN       0x0017 // Device not connected
#define ERROR_LONG           0X0018 // Command is too long
#define ERROR_NAME           0X0019 // Name not found
#define ERROR_NO_CONF        0X001A // Configuration not found
#define ERROR_BATTERY        0X0100 // Failed to read battery voltage
#define ERROR_MFI            0X1002 // Failed to communicate with the Apple MFI Co-processor
#define ERROR_REG            0X1004 // Failed to register/unregister device
#define ERROR_BLE            0X1005 // BLE request failed
#define ERROR_ENCRYPTION     0x1006 // Insufficient encryption
#define ERROR_AUTHENTICATion 0x1007 // Insufficient authentication
#define ERROR_NOT PERMITTed  0x1008 // Operation not permitted
#define ERROR_HANDLE         0X1009 // Invalid handle
#define ERROR_CRITICAL       0XF000 // Critical Error
#define ERROR_KEY_MISSING    0xFF01 // Melody license key is missing
#define ERROR_KEY_INVALID    0xFF02 // Melody license key is invalid

#endif /* BC127_CONST_H */
