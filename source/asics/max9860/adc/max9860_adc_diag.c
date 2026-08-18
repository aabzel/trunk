#include "max9860_adc_diag.h"

#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "log.h"
#include "max9860_drv.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

const char* AdcLeftEnToStr(AdcEnable_t code) {
    const char* name = "?";
    switch(code) {
    case ADCEN_OFF:
        name = "LeftAdcOff";
        break;
    case ADCEN_ON:
        name = "LeftAdcOn";
        break;
    }
    return name;
}

const char* AdcRightEnToStr(AdcEnable_t code) {
    const char* name = "?";
    switch(code) {
    case ADCEN_OFF:
        name = "RightAdcOff";
        break;
    case ADCEN_ON:
        name = "RightAdcOn";
        break;
    }
    return name;
}

const char* AGCSRCToStr(AGCSrc_t code) {
    const char* name = "?";
    switch((uint8_t)code) {
    case LEFT_ADC_OUTPUT_FOR_AGC:
        name = "left";
        break;
    case SUM_ADC_OUTPUTS_FOR_AGC:
        name = "sum";
        break;

    default:
        break;
    }
    return name;
}

const char* AGCReleaseTimeToStr(AGCReleaseTime_t code) {
    const char* name = "?";
    switch((uint8_t)code) {
    case AGCRLS_78_MS:
        name = "78ms";
        break;
    case AGCRLS_156_MS:
        name = "156ms";
        break;
    case AGCRLS_312_MS:
        name = "312ms";
        break;
    case AGCRLS_625_MS:
        name = "625ms";
        break;
    case AGCRLS_1_25_S:
        name = "1.25s";
        break;
    case AGCRLS_2_5_S:
        name = "2.5s";
        break;
    case AGCRLS_5_S:
        name = "5s";
        break;
    case AGCRLS_10_S:
        name = "10s";
        break;

    default:
        break;
    }
    return name;
}

const char* AGCAttackTimeToStr(AGCAttackTime_t code) {
    const char* name = "?";
    switch((uint8_t)code) {
    case AGCATK_3_MS:
        name = "3ms";
        break;
    case AGCATK_12_MS:
        name = "12ms";
        break;
    case AGCATK_50_MS:
        name = "50ms";
        break;
    case AGCATK_200_MS:
        name = "200ms";
        break;

    default:
        break;
    }
    return name;
}

const char* AGCHoldTimeToStr(AGCHoldTime_t code) {
    const char* name = "?";
    switch((uint8_t)code) {
    case AGCHLD_AGC_DISABLED:
        name = "disabled";
        break;
    case AGCHLD_50_MS:
        name = "50ms";
        break;
    case AGCHLD_100_MS:
        name = "100ms";
        break;
    case AGCHLD_400_MS:
        name = "400ms";
        break;

    default:
        break;
    }
    return name;
}

const char* MicrophonePreampGainToStr(AdcPreampGain_t pam) {
    const char* name = "?";
    switch((uint8_t)pam) {
    case ADC_PAM_GAIN_DISABLED:
        name = "disabled";
        break;
    case ADC_PAM_GAIN_0_DB:
        name = "0";
        break;
    case ADC_PAM_GAIN_PLUS_20_DB:
        name = "+20";
        break;
    case ADC_PAM_GAIN_PLUS_30_DB:
        name = "+30";
        break;
    default:
        break;
    }
    return name;
}

const char* MicrophoneProgrammableGainAmplifierToStr(uint8_t pgam) {
    static char name[30] = "";
    sprintf(name, "%d", MicrophoneProgrammableGainAmplifierCode2Gain(pgam));
    return name;
}

const char* AdcOutputLevelToStr(uint8_t adc_out_lev) {
    static char name[30] = "";
    sprintf(name, "%d", AdcOutputLevel2Gain(adc_out_lev));
    return name;
}

const char* AdcDelayToStr(AdcDelayMode_t adly) {
    const char* name = "";
    switch((uint8_t)adly) {
    case SDOUT_DATA_VALID_ON_FIRST_BCLK_EDGE:
        name = "SdOutDataValid1stBCLKEdgeLRClkEdge";
        break;
    case SDOUT_DATA_VALID_ON_SECONDT_BCLK_EDGE:
        name = "SdOutDataValid2ndBClkEdge";
        break;
    default:
        break;
    }
    return name;
}

const char* AdcBitClkInvertToStr(AdcBitClkInvert_t abci) {
    const char* name = "";
    switch((uint8_t)abci) {
    case ABCI_SDOUT_RISING_BCLK:
        name = "SdOutValidRisingEdgeBCLK";
        break;
    case ABCI_SDOUT_FALLING_BCLK:
        name = "SdOutValidFallingEdgeBCLK";
        break;
    default:
        break;
    }
    return name;
}

const char* SdOutHighInpedanceModeToStr(HighImpedanceZ_t hiz) {
    const char* name = "";
    switch((uint8_t)hiz) {
    case HIZ_SDOUT_HI_OR_LOW:
        name = "SdOutHiOrLow";
        break;
    case HIZ_SDOUT_HI_IMPEDANCE:
        name = "SdOutHiImpedance";
        break;
    default:
        break;
    }
    return name;
}

const char* NoiseGateAttenuationToStr(NoiseGateAttenuation_t ng_code) {
    const char* name = "";
    switch((uint8_t)ng_code) {
    case NG_ATT_0_DB:
        name = "0dB";
        break;
    case NG_ATT_1_DB:
        name = "1dB";
        break;
    case NG_ATT_2_DB:
        name = "2dB";
        break;
    case NG_ATT_3_DB:
        name = "3dB";
        break;
    case NG_ATT_6_DB:
        name = "6dB";
        break;
    case NG_ATT_8_DB:
        name = "8dB";
        break;
    case NG_ATT_10_DB:
        name = "10dB";
        break;
    case NG_ATT_12_DB:
        name = "12dB";
        break;
    default:
        break;
    }
    return name;
}
