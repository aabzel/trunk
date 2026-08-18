#include "max9860_dac_diag.h"

#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "log.h"
#include "max9860_drv.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

/*The gain set by DVG adds to the level set by DVA*/
const char* DacGainToStr(DacGainCode_t dvg_code) {
    const char* name = "?";
    switch((uint8_t)dvg_code) {
    case DAC_GAIN_0:
        name = "0";
        break;
    case DAC_GAIN_6:
        name = "+6";
        break;
    case DAC_GAIN_12:
        name = "+12";
        break;
    case DAC_GAIN_18:
        name = "+18";
        break;
    default:
        break;
    }
    return name;
}

const char* AdcSideToneGainToStr(uint8_t dvst_code) {
    static char name[10] = "";
    sprintf(name, "%d", AdcSideToneCode2Gain(dvst_code));
    return name;
}

const char* DacLevelAttenuationToStr(uint8_t dva_code) {
    static char name[10] = "";
    sprintf(name, "%d", DacLevelAttenuation2Gain(dva_code));
    return name;
}

/*DAC Delay Mode*/
const char* DacDelayModeToStr(DacDelay_t ddly) {
    const char* name = "?";
    switch((uint8_t)ddly) {
    case DDLY_1ST_BCLK:
        name = "SdIn1StBitClk";
        break;
    case DDLY_2ND_BCLK:
        name = "SdIn2ndBitClk";
        break;

    default:
        break;
    }
    return name;
}

/*DAC BCLK Invert*/
const char* DacBitClockInvertToStr(DacBitClkInvert_t dbci) {
    const char* name = "?";
    switch((uint8_t)dbci) {
    case DBCI_SDOUT_VALID_ON_BCLK_RISING_EDGE:
        name = "SdOutValidBCLKRisingEdge";
        break;
    case DBCI_SDOUT_VALID_ON_BCLK_FALLING_EDGE:
        name = "SdOutValidBClkFallingEdge";
        break;

    default:
        break;
    }
    return name;
}
