#include "bc127_diag.h"

#include <stdint.h>

#include "bc127_const.h"
#include "cli_utils.h"
#include "convert.h"
#include "data_utils.h"

#ifndef HAS_BC127
#error "+HAS_BC127"
#endif

char* DigitalFormatToStr(uint8_t digital_format) {
    char* name = "?";
    switch(digital_format) {
    case DFOR_I2S:
        name = "I2S";
        break;
    case DFOR_PCM:
        name = "PCM";
        break;
    case DFOR_SDPIF:
        name = "SDPIF";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

char* Bc127I2sBusRoleToStr(uint8_t bus_mode) {
    char* name = "?";
    switch(bus_mode) {
    case BC127_I2SMODE_SLAVE:
        name = "Slave";
        break;
    case BC127_I2SMODE_MASTER:
        name = "Master";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

char* JustifyFormatToStr(uint8_t bus_mode) {
    char* name = "?";
    switch(bus_mode) {
    case JUST_FMT_LEFT:
        name = "Left";
        break;
    case JUST_FMT_RIGHT:
        name = "Right";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

char* JustifyResolutionToStr(uint8_t code) {
    char* name = "?";
    switch(code) {
    case JUST_RES_16_BIT:
        name = "16";
        break;
    case JUST_RES_20_BIT:
        name = "20";
        break;
    case JUST_RES_24_BIT:
        name = "24";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

char* StartSamplingToStr(uint8_t code) {
    char* name = "?";
    switch(code) {
    case ST_SAM_LOW_WCLK_PHASE:
        name = "LowWclk";
        break;
    case ST_SAM_HIGH_WCLK_PHASE:
        name = "HighWclk";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

char* CropToStr(uint8_t code) {
    char* name = "?";
    switch(code) {
    case CROP_EN_17_TO_16_BIT:
        name = "17to16";
        break;
    case CROP_EN_ONLY_16_BIT:
        name = "only16";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

char* AudioAttenuationToStr(uint8_t code) {
    char* name = "?";
    switch(code) {
    case AUDIO_ATT_EN_17_TO_16_bit:
        name = "17to16";
        break;
    case AUDIO_ATT_EN_12_15:
        name = "12_15";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

char* ChannelPolarityToStr(uint8_t code) {
    char* name = "?";
    switch(code) {
    case CH_POL_LEFT_WS_HIGH:
        name = "LeftWSHight";
        break;
    case CH_POL_RIGHT_WS_HIGH:
        name = "RightWSHight";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

char* LeftJustifyDelayToStr(uint8_t code) {
    char* name = "?";
    switch(code) {
    case LEFT_JUST_DELAY_MSB_1ST_SCLK:
        name = "Msb1stSclk";
        break;
    case LEFT_JUST_DELAY_MSB_2ND_SCLK:
        name = "Msb2ndSclk";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

bool parse_i2s_param2(uint32_t reg_val) {
    bool res = false;
    Bc127Param2_t Param2;
    Param2.reg_val = reg_val;
    cli_printf("RegVal: 0x%08x 0b%s " CRLF, reg_val, utoa_bin32(reg_val));
    cli_printf("16:23 BitPerSample: %u bit" CRLF, Param2.bits_per_sample);
    cli_printf("12-15 AudioAtten: %u dB" CRLF, Param2.audio_attenuation * 6);
    cli_printf("11 I2sBusRole: %u %s" CRLF, Param2.mode, Bc127I2sBusRoleToStr(Param2.mode));
    cli_printf("10 JustifyFormat: %u %s" CRLF, Param2.justify_format, JustifyFormatToStr(Param2.justify_format));
    cli_printf("9 LeftJustDelay: %u %s" CRLF, Param2.left_justify_delay,
               LeftJustifyDelayToStr(Param2.left_justify_delay));
    cli_printf("8 ChannelPolarity: %u %s" CRLF, Param2.channel_polarity, ChannelPolarityToStr(Param2.channel_polarity));
    cli_printf("7 AudioAttenuation: %u %s" CRLF, Param2.audio_attenuation_enable,
               AudioAttenuationToStr(Param2.audio_attenuation_enable));
    /*5:6 res */
    cli_printf("3:4 JustifyResolution: %u %s bit" CRLF, Param2.justify_resolution,
               JustifyResolutionToStr(Param2.justify_resolution));
    cli_printf("2 Crop: %u %s" CRLF, Param2.crop_enable, CropToStr(Param2.crop_enable));
    cli_printf("1 StartTxSampling: %u %s" CRLF, Param2.start_tx_sampling, StartSamplingToStr(Param2.start_tx_sampling));
    cli_printf("0 StartRxSampling: %u %s" CRLF, Param2.start_rx_sampling, StartSamplingToStr(Param2.start_rx_sampling));

    return res;
}

static const ErrCodeName_t ErrCodeNameLut[] = {
    {.err_code = 0x0003, .name = "UnknownError"},
    {.err_code = 0x0011, .name = "CmdNotAllowedWithCurrCfg"},
    {.err_code = 0x0012, .name = "CmdNotFound"},
    {.err_code = 0x0013, .name = "WrongParameter"},
    {.err_code = 0x0014, .name = "WrongNumberOfParameters"},
    {.err_code = 0x0015, .name = "CmdNotAllowedInTheCurrentState"},
    {.err_code = 0x0016, .name = "DeviceAlreadyConnected"},
    {.err_code = 0x0017, .name = "DeviceNotConnected"},
    {.err_code = 0x0018, .name = "CommandIsTooLong"},
    {.err_code = 0x0019, .name = "NameNotFound"},
    {.err_code = 0x001A, .name = "ConfigurationNotFound"},
    {.err_code = 0x0100, .name = "FailedToReadBatteryVoltage"},
    {.err_code = 0x1002, .name = "FailedToCommunicateWithTheAppleMFICo-processor"},
    {.err_code = 0x1004, .name = "FailedToRegisterUnregisterDev"},
    {.err_code = 0x1005, .name = "BLErequestFailed"},
    {.err_code = 0x1006, .name = "InsufficientEncryption"},
    {.err_code = 0x1007, .name = "InsufficientAuthentication"},
    {.err_code = 0x1008, .name = "OperationNotPermitted"},
    {.err_code = 0x1009, .name = "InvalidHandle"},
    {.err_code = 0xF000, .name = "CriticalError"},
    {.err_code = 0xFF01, .name = "MelodyLicenseKeyIsMissing"},
    {.err_code = 0xFF02, .name = "MelodyLicenseKeyIsInvalid"}};

const char* ErrorCodeToStr(uint16_t err_code) {
    const char* name = "?";
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(ErrCodeNameLut);
    for(i = 0; i < cnt; i++) {
        if(err_code == ErrCodeNameLut[i].err_code) {
            name = ErrCodeNameLut[i].name;
        }
    }
    return name;
}
