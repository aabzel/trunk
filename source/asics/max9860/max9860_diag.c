#include "max9860_diag.h"

#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "log.h"

#ifdef HAS_MAX9860_ADC
#include "max9860_adc_diag.h"
#endif /**/

#ifdef HAS_MAX9860_DAC
#include "max9860_dac_diag.h"
#endif /**/

#include "max9860_drv.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

/*DBCI*/
const char* DacBitClkInvertToStr(DacBitClkInvert_t dac_bit_clk_invert) {
    const char* name = "";
    switch((uint8_t)dac_bit_clk_invert) {
    case DBCI_SDOUT_VALID_ON_BCLK_RISING_EDGE:
        name = "SdinRisingEdgeBCLK.";
        break;
    case DBCI_SDOUT_VALID_ON_BCLK_FALLING_EDGE:
        name = "SdinFallingEdgeBCLK";
        break;
    default:
        break;
    }
    return name;
}

const char* StereoToStr(Stereo_t stereo) {
    const char* name = "";
    switch((uint8_t)stereo) {
    case ST_MONO_ENABLE:
        name = "Mono";
        break;
    case ST_STEREO_ENABLE:
        name = "StereoOn";
        break;
    default:
        break;
    }
    return name;
}

const char* BitClkToStr(BitClockSelect_t bsel) {
    const char* name = "?";
    switch((uint8_t)bsel) {
    case BSEL_OFF:
        name = "Off";
        break;
    case BSEL_64X_LRCLK:
        name = "64xLRClk";
        break;
    case BSEL_48X_LRCLK:
        name = "48xLRClk";
        break;
    case BSEL_RES:
        name = "Reserved";
        break;
    case BSEL_PCLK_DIV2:
        name = "PCLK/2";
        break;
    case BSEL_PCLK_DIV4:
        name = "PCLK/4";
        break;
    case BSEL_PCLK_DIV8:
        name = "PCLK/8";
        break;
    case BSEL_PCLK_DIV16:
        name = "PCLK/16";
        break;
    }
    return name;
}

const char* Max9860I2sRoleToStr(Max9860I2sRole_t i2s_role) {
    const char* name = "";
    switch(i2s_role) {
    case MAX9860_I2S_ROLE_SLAVE:
        name = "Slave";
        break;
    case MAX9860_I2S_ROLE_MASTER:
        name = "Master";
        break;
    }
    return name;
}

const char* Max9860StereoToStr(MaxStereo_t stereo) {
    const char* name = "?";
    switch((uint8_t)stereo) {
    case MAX_STEREO_OFF:
        name = "Off";
        break;
    case MAX_STEREO_ON:
        name = "On";
        break;
    default:
        break;
    }
    return name;
}

const char* ClipDetectFlagToStr(ClipDetectFlag_t code) {
    const char* name = "";
    switch((uint8_t)code) {
    case CLIP_DETECT_FLAG_ON:
        name = "SignalClipped";
        break;
    case CLIP_DETECT_FLAG_OFF:
        name = "NoClipDetect";
        break;
    }
    return name;
}

/*PLL Enable*/
static const char* PllEnableToStr(PllEnable_t pll_code) {
    const char* name = "";
    switch((int8_t)pll_code) {
    case PLL_LRCLK:
        name = "Off";
        break;
    case PLL_SLAVE_ONLY:
        name = "On";
        break;
    }
    return name;
}

const char* SlewLevelDetectFlagToStr(uint8_t code) {
    const char* name = "";
    switch(code) {
    case SLD_FLAG_ON:
        name = "SlewingCompleted";
        break;
    case SLD_OFF:
        name = "NoSlewLevelDetect";
        break;
    }
    return name;
}

static const char* Freq16kHzModeToStr(LrClk16kHzMode_t f16khz) {
    const char* name = "";
    switch((uint8_t)f16khz) {
    case LRCK_IS_8KHZ:
        name = "LRCLK=8kHz";
        break;
    case LRCK_IS_16KHZ:
        name = "LRCLK=16kHz.";
        break;
    }
    return name;
}

const char* MasterModeToStr(Max9860I2sRole_t mas) {
    const char* name = "";
    switch((uint8_t)mas) {
    case MAX9860_I2S_ROLE_SLAVE:
        name = "I2sSlave";
        break;
    case MAX9860_I2S_ROLE_MASTER:
        name = "I2sMaster";
        break;
    }
    return name;
}

const char* LrClkInvertToStr(WCI_t wci) {
    const char* name = "?";
    switch((uint8_t)wci) {
    case WCI_LEFT_CH_LRCLK_LOW:
        name = "LeftChLRClkLow";
        break;
    case WCI_RIGHT_CH_LRCLK_LOW:
        name = "RightChLRClkLow";
        break;
    }
    return name;
}

const char* TdmModeToStr(TDM_t tdm) {
    const char* name = "";
    switch((uint8_t)tdm) {
    case TDM_LRCLK_LEFT_AND_RIGHT:
        name = "I2S";
        break;
    case TDM_LRCLK_LEFT_OR_RIGHT:
        name = "TDM";
        break;
    }
    return name;
}

const char* MainClkPrescalerToStr(PrescalerClk_t psclk) {
    const char* name = "";
    switch((uint8_t)psclk) {
    case PSCLK_DISABLE:
        name = "Disable";
        break;
    case PSCLK_MCLK_10MHZ_20MHZ:
        name = "10MHz-20MHz";
        break;
    case PSCLK_MCLK_20MHZ_40MHZ:
        name = "20MHz-40MHz";
        break;
    case PSCLK_MCLK_40MHZ_PLUS:
        name = "40MHz+";
        break;
    }
    return name;
}

static const char* IntegerClockModeToStr(IntegerClkMode_t freq) {
    const char* name = "";
    switch((uint8_t)freq) {
    case FREQ_NORMAL_OP:
        name = "ClockingWithPLL,N";
        break;
    case FREQ_PCLK_12MHz:
        name = "PCLK=12MHz";
        break;
    case FREQ_PCLK_13MHz:
        name = "PCLK=13MHz";
        break;
    case FREQ_PCLK_19_2MHz:
        name = "PCLK=19.2MHz";
        break;
    }
    return name;
}

static const char* DigitalPLLUnlockFlagToStr(uint8_t code) {
    const char* name = "";
    switch(code) {
    case ULK_ON:
        name = "PLLunlocked";
        break;
    case ULK_OFF:
        name = "PLLlocked";
        break;
    }
    return name;
}

static const char* VoiceFilterToStr(DigitalFilter_t vflt) {
    const char* name = "";
    switch((uint8_t)vflt) {
    case DIG_FILT_DISABLED:
        name = "FiltDisabled";
        break;
    case DIG_FILT_ELLIPTICAL_8KHZ:
        name = "Elliptical8kHz";
        break;
    case DIG_FILT_ELLIPTICAL_16KHZ:
        name = "Elliptical16kHz";
        break;
    case DIG_FILT_BUTTERWORTH_8KHZ:
        name = "Butterworth8kHz";
        break;
    case DIG_FILT_BUTTERWORTH_16KHZ:
        name = "Butterworth16kHz";
        break;
    case DIG_FILT_BUTTERWORTH_48KHZ:
        name = "Butterworth48kHz";
        break;
    }
    return name;
}

const char* Max9860RegAddr2Name(Max9860RegAddr_t addr) {
    const char* name = "";
    const Max9860RegName_t* Node = max9860RegAddr2Node(addr);
    if(Node) {
        name = Node->name;
    }
    return name;
}

static Gain_t AnthCode2Gain(uint8_t code) {
    Gain_t gain = 0;
    gain = 4 * ((int8_t)code) - 76;
    return gain;
}

static Gain_t AgcthCode2Gain(uint8_t code) {
    Gain_t gain = 0;
    gain = -1 * ((int8_t)code) - 3;
    return gain;
}

static const char* AgcthToStr(uint8_t code) {
    static char name[20] = "?";
    Gain_t gain = AgcthCode2Gain(code);
    sprintf(name, "%d dBFS", gain);
    return name;
}
/*Noise Gate Threshold*/
const char* AnthToStr(uint8_t code) {
    static char name[13] = "?";
    Gain_t gain = AnthCode2Gain(code);
    sprintf(name, "%d dBFS", gain);
    return name;
}

static bool max9860_reg_00_interrupt_status_diag(uint8_t value, const char* const key_word) {
    bool res = true;
    char line[80] = "";
    sprintf(line, "Reg %s, Val 0x%x=%s", Max9860RegAddr2Name(MAX9860_REG_INTERRUPT_STATUS), value, utoa_bin8(value));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    Max9860Reg00InterruptStatus_t Reg;
    Reg.byte = value;
    sprintf(line, "Bit7, CLD %u, %s", Reg.cld, ClipDetectFlagToStr(Reg.cld));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit6, SLD %u, %s", Reg.sld, SlewLevelDetectFlagToStr(Reg.sld));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit5, ULK %u, %s", Reg.ulk, DigitalPLLUnlockFlagToStr(Reg.ulk));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    return res;
}

/*Microphone NG/AGC Readback*/
static bool max9860_reg_01_interrupt_status_diag(uint8_t value, const char* const key_word) {
    /*Microphone NG/AGC Readback*/
    bool res = true;
    LOG_NOTICE(MAX9860, "Microphone NG/AGC Readback RegVal 0x%x=%s", value, utoa_bin8(value));
    Max9860Reg01Gain_t Reg;
    char line[80] = "";
    Reg.byte = value;
#ifdef HAS_MAX9860_ADC
    sprintf(line, "Bit5-7 NoiseGateAttenuation NG %u=%s", Reg.ng, NoiseGateAttenuationToStr(Reg.ng));
#else
    sprintf(line, "Bit5-7 NoiseGateAttenuation NG %u", Reg.ng);
#endif
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit0-4 AutomaticGainControlGain AGC %u", Reg.agc);
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
    return res;
}

/*Interrupt Enable*/
static bool max9860_reg_02_interrupt_enable_diag(uint8_t value, const char* const key_word) {
    bool res = true;
    LOG_NOTICE(MAX9860, "Interrupt Enable RegVal 0x%x=%s", value, utoa_bin8(value));
    Max9860Reg02IntEnable_t Reg;
    char line[80] = "";
    Reg.byte = value;

    sprintf(line, "Bit7 ClipDetect ICLD %u=%s", Reg.icld, OnOffToStr(Reg.icld));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit6 SlewLevelDetect ISLD %u=%s", Reg.isld, OnOffToStr(Reg.isld));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit5 DigitalPLLUnlock IULK %u=%s", Reg.iulk, OnOffToStr(Reg.iulk));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
    return res;
}

/*System Clock*/
static bool max9860_reg_03_system_clock_diag(uint8_t value, const char* const key_word) {
    bool res = true;
    LOG_NOTICE(MAX9860, "System Clock RegVal 0x%x=%s", value, utoa_bin8(value));
    Max9860Reg03SystemClock_t Reg;
    Reg.byte = value;
    char line[80] = "";

    sprintf(line, "Bit4-5 PSCLK %u", Reg.psclk, MainClkPrescalerToStr(Reg.psclk));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit1-2 FREQ %u", Reg.freq, IntegerClockModeToStr(Reg.freq));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit0 16KHZ %u", Reg.f16khz, Freq16kHzModeToStr(Reg.f16khz));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
    return res;
}

static bool max9860_reg_04_stereo_audio_clock_control_high_diag(uint8_t value, const char* const key_word) {
    bool res = true;
    LOG_NOTICE(MAX9860, "Stereo Audio Clock Control High RegVal 0x%x=%s", value, utoa_bin8(value));
    Max9860Reg04StereoAudioClockControlHight_t Reg;
    Reg.byte = value;
    char line[80] = "";

    sprintf(line, "Bit7 PllEnable PLL %u=%s", Reg.pll, PllEnableToStr(Reg.pll));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit0-6 NHI %u", Reg.nhi);
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
    return res;
}

static bool max9860_reg_05_stereo_audio_clock_control_low_diag(uint8_t value, const char* const key_word) {
    bool res = true;
    LOG_NOTICE(MAX9860, "Stereo Audio Clock Control Low RegVal 0x%x=%s", value, utoa_bin8(value));
    Max9860Reg05StereoAudioClockControlLow_t Reg;
    Reg.byte = value;
    char line[80] = "";

    sprintf(line, "Bit0-7 ClockControl NLO %u", Reg.nlo);
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
    return res;
}

/*Interface*/
static bool max9860_reg_06_interface_diag(uint8_t value, const char* const key_word) {
    bool res = true;
    LOG_NOTICE(MAX9860, "Interface RegVal 0x%x=%s", value, utoa_bin8(value));
    Max9860Reg06If1_t Reg;
    Reg.byte = value;
    char line[80] = "";

    sprintf(line, "Bit7 MAS %u=%s", Reg.mas, MasterModeToStr(Reg.mas));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit6 WCI %u=%s", Reg.wci, LrClkInvertToStr(Reg.wci));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit5 DBCI %u=%s", Reg.dbci, DacBitClockInvertToStr(Reg.dbci));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit4 DDLY %u=%s", Reg.ddly, DacDelayModeToStr(Reg.ddly));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

#ifdef HAS_MAX9860_ADC
    sprintf(line, "Bit3 HIZ %u=%s", Reg.hiz, SdOutHighInpedanceModeToStr(Reg.hiz));
#else
    sprintf(line, "Bit3 HIZ %u", Reg.hiz);
#endif
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit2 TDM %u=%s", Reg.tdm, TdmModeToStr(Reg.tdm));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
    return res;
}

static bool max9860_reg_07_interface_diag(uint8_t value, const char* const key_word) {
    bool res = true;
    char line[80] = "";
    LOG_NOTICE(MAX9860, "Interface RegVal 0x%x=%s", value, utoa_bin8(value));
    Max9860Reg07If2_t Reg;
    Reg.byte = value;
#ifdef HAS_MAX9860_ADC
    sprintf(line, "Bit5 AdcBitClkInvert ABCI %u=%s", Reg.abci, AdcBitClkInvertToStr(Reg.abci));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit4 ADLY %u=%s", Reg.adly, AdcDelayToStr(Reg.adly));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
#else  /*HAS_MAX9860_ADC*/
    sprintf(line, "Bit5 AdcBitClkInvert ABCI %u", Reg.abci);
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit4 ADLY %u", Reg.adly);
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
#endif /*HAS_MAX9860_ADC*/

    sprintf(line, "Bit3 Stereo ST %u=%s", Reg.st, StereoToStr(Reg.st));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit3 BitClkSelectBSEL %u=%s", Reg.bsel, BitClkToStr(Reg.bsel));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    return res;
}

/*Voice Filter*/
static bool max9860_reg_08_voice_filter_diag(uint8_t value, const char* const key_word) {
    bool res = true;
    LOG_NOTICE(MAX9860, "Voice Filter RegVal 0x%x=%s", value, utoa_bin8(value));
    Max9860Reg08DigitalFilter_t Reg;
    Reg.byte = value;
    char line[80] = "";

    sprintf(line, "Bit4-7 ADC Voice Filter AVFLT %u=%s", Reg.avflt, VoiceFilterToStr(Reg.avflt));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit0-3 DAC Voice Filter DVFLT %u=%s", Reg.dvflt, VoiceFilterToStr(Reg.dvflt));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    return res;
}

/*DAC Attenuation*/
static bool max9860_reg_09_dac_attenuation_diag(uint8_t value, const char* const key_word) {
    bool res = true;
    LOG_NOTICE(MAX9860, "DAC Attenuation RegVal 0x%x=%s", value, utoa_bin8(value));
    Max9860Reg09DacLevAdj_t Reg;
    Reg.byte = value;
    char line[80] = "";
    sprintf(line, "Bit0-7 DACLevelAdjust DVA %u=%s", Reg.dva, DacLevelAttenuationToStr(Reg.dva));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
    return res;
}

/*Reg ADC Output Levels*/
static bool max9860_reg_0a_adc_output_levels_diag(uint8_t value, const char* const key_word) {
    bool res = true;
    LOG_NOTICE(MAX9860, "ADC Output Levels RegVal 0x%x=%s", value, utoa_bin8(value));
    Max9860Reg0AAdcOutLevel_t Reg;
    Reg.byte = value;
    char line[80] = "";
#ifdef HAS_MAX9860_ADC
    sprintf(line, "Bit4-7 Left ADC Output Level ADCRL %u=%s", Reg.adcrl, AdcOutputLevelToStr(Reg.adcrl));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit0-3 Right ADC Output Level ADCLL %u=%s", Reg.adcll, AdcOutputLevelToStr(Reg.adcll));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
#else  /*HAS_MAX9860_ADC*/
    sprintf(line, "Bit4-7 Left ADC Output Level ADCRL %u", Reg.adcrl);
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit0-3 Right ADC Output Level ADCLL %u", Reg.adcll);
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
#endif /*HAS_MAX9860_ADC*/
    return res;
}

static bool max9860_reg_0b_dac_gain_and_sidetone_diag(uint8_t value, const char* const key_word) {
    LOG_NOTICE(MAX9860, "DAC Gain and Sidetone RegVal 0x%x=%s", value, utoa_bin8(value));
    bool res = true;
    char line[80] = "";
    Max9860Reg0BDacGainSidetone_t Reg;
    Reg.byte = value;

    sprintf(line, "Bit5-6 DAC Gain DVG %u=%s", Reg.dvg, DacGainToStr(Reg.dvg));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit0-4 Sidetone DVST %u=%s", Reg.dvst, AdcSideToneGainToStr(Reg.dvst));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    return res;
}

static bool max9860_reg_0c_microphone_gain_diag(uint8_t value, const char* const key_word) {
    bool res = true;
    LOG_NOTICE(MAX9860, "Microphone Gain RegVal 0x%x=%s", value, utoa_bin8(value));
    Max9860Reg0CMicrophoneGain_t Reg;
    Reg.byte = value;
    char line[80] = "";
#ifdef HAS_MAX9860_ADC
    sprintf(line, "Bit5-6 PAM %u=%s", Reg.pam, MicrophonePreampGainToStr(Reg.pam));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
    sprintf(line, "Bit0-4 PGAM %u=%s", Reg.pgam, MicrophoneProgrammableGainAmplifierToStr(Reg.pgam));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
#else  /*HAS_MAX9860_ADC*/
    sprintf(line, "Bit5-6 PAM %u", Reg.pam);
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
    sprintf(line, "Bit0-4 PGAM %u", Reg.pgam);
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
#endif /*HAS_MAX9860_ADC*/
    return res;
}

/*Table 10. AGC and Noise Gate Registers*/
static bool max9860_reg_0e_microphone_agc_diag(uint8_t value, const char* const key_word) {
    bool res = true;
    char line[80] = "";
    sprintf(line, "Reg %s, Val 0x%x=%s", Max9860RegAddr2Name(MAX9860_REG_MICROPHONE_AGC), value, utoa_bin8(value));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
#ifdef HAS_MAX9860_ADC
    Max9860Reg0EMicrophoneAgc_t Reg;
    Reg.byte = value;
    sprintf(line, "Bit7, AGCSRC %u, %s", Reg.agcsrc, AGCSRCToStr(Reg.agcsrc));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit4-6, AGCRLS %u, %s", Reg.agcrls, AGCReleaseTimeToStr(Reg.agcrls));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit2-3, AGCATK %u, %s", Reg.agcatk, AGCAttackTimeToStr(Reg.agcatk));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit0-1, AGCHLD %u, %s", Reg.agchld, AGCHoldTimeToStr(Reg.agchld));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
#else  /*HAS_MAX9860_ADC*/
    Max9860Reg0EMicrophoneAgc_t Reg;
    Reg.byte = value;
    sprintf(line, "Bit7, AGCSRC %u", Reg.agcsrc);
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit4-6, AGCRLS %u", Reg.agcrls);
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit2-3, AGCATK %u", Reg.agcatk);
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit0-1, AGCHLD %u", Reg.agchld);
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
#endif /*HAS_MAX9860_ADC*/

    return res;
}

static bool max9860_reg_0f_noise_gate_microphone_agc_diag(uint8_t value, const char* const key_word) {
    bool res = true;
    LOG_NOTICE(MAX9860, "Noise Gate, Microphone AGC RegVal 0x%x=%s", value, utoa_bin8(value));
    Max9860Reg0FNoiseGateMicAgc_t Reg;
    Reg.byte = value;

    char line[80] = "";
    sprintf(line, "Bit4-7, ANTH %u, %s", Reg.anth, AnthToStr(Reg.anth));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit0-3, AGCTH %u, %s", Reg.agcth, AgcthToStr(Reg.agcth));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    return res;
}

const char* SwShutDownToStr(SwShutDown_t code) {
    const char* name = "?";
    switch(code) {
    case SHDN_ON:
        name = "FullShutdown";
        break;
    case SHDN_OFF:
        name = "PoweredOn";
        break;
    default:
        name = "Err";
        break;
    }
    return name;
}

const char* DacEnToStr(DacEn_t code) {
    const char* name = "?";
    switch((uint8_t)code) {
    case DACEN_OFF:
        name = "DacOff";
        break;
    case DACEN_ON:
        name = "DacOn";
        break;
    }
    return name;
}

static bool max9860_reg_10_system_shutdown_diag(uint8_t value, const char* const key_word) {
    bool res = true;
    Max9860Reg10SysShutdown_t Reg;
    Reg.byte = value;

    char line[80] = "";
    sprintf(line, "Reg %s, Val 0x%x=%s", Max9860RegAddr2Name(MAX9860_REG_SYSTEM_SHUTDOWN), value, utoa_bin8(value));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit7, %u, %s", Reg.shdn, SwShutDownToStr(Reg.shdn));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit3, %u, %s", Reg.dacen, DacEnToStr(Reg.dacen));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

#ifdef HAS_MAX9860_ADC
    sprintf(line, "Bit1, %u, %s", Reg.adclen, AdcLeftEnToStr(Reg.adclen));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit0, %u, %s", Reg.adcren, AdcRightEnToStr(Reg.adclen));
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
#else  /*HAS_MAX9860_ADC*/
    sprintf(line, "Bit1, %u", Reg.adclen);
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);

    sprintf(line, "Bit0, %u", Reg.adcren);
    log_print_conditional(LOG_LEVEL_INFO, MAX9860, line, key_word, NULL);
#endif /*HAS_MAX9860_ADC*/
    return res;
}

static bool max9860_reg_diag(Max9860RegAddr_t addr, uint8_t value, const char* const key_word) {
    bool res = false;
    LOG_NOTICE(MAX9860, "Interrupt Status Addr 0x%x RegVal 0x%x=%s", addr, value, utoa_bin8(value)); //
    switch((uint8_t)addr) {
    case MAX9860_REG_INTERRUPT_STATUS:
        res = max9860_reg_00_interrupt_status_diag(value, key_word);
        break;
    case MAX9860_REG_MICROPHONE_NG_AGC_READBACK:
        res = max9860_reg_01_interrupt_status_diag(value, key_word);
        break;
    case MAX9860_REG_INTERRUPT_ENABLE:
        res = max9860_reg_02_interrupt_enable_diag(value, key_word);
        break;
    case MAX9860_REG_SYSTEM_CLOCK:
        res = max9860_reg_03_system_clock_diag(value, key_word);
        break;
    case MAX9860_REG_STEREO_AUDIO_CLOCK_CONTROL_HIGH:
        res = max9860_reg_04_stereo_audio_clock_control_high_diag(value, key_word);
        break;
    case MAX9860_REG_STEREO_AUDIO_CLOCK_CONTROL_LOW:
        res = max9860_reg_05_stereo_audio_clock_control_low_diag(value, key_word);
        break;
    case MAX9860_REG_INTERFACE1:
        res = max9860_reg_06_interface_diag(value, key_word);
        break;
    case MAX9860_REG_INTERFACE2:
        res = max9860_reg_07_interface_diag(value, key_word);
        break;
    case MAX9860_REG_VOICE_FILTER:
        res = max9860_reg_08_voice_filter_diag(value, key_word);
        break;
    case MAX9860_REG_DAC_ATTENUATION:
        res = max9860_reg_09_dac_attenuation_diag(value, key_word);
        break;
    case MAX9860_REG_ADC_OUTPUT_LEVELS:
        res = max9860_reg_0a_adc_output_levels_diag(value, key_word);
        break;
    case MAX9860_REG_DAC_GAIN_AND_SIDETONE:
        res = max9860_reg_0b_dac_gain_and_sidetone_diag(value, key_word);
        break;
    case MAX9860_REG_MICROPHONE_GAIN:
        res = max9860_reg_0c_microphone_gain_diag(value, key_word);
        break;
    case MAX9860_REG_MICROPHONE_AGC:
        res = max9860_reg_0e_microphone_agc_diag(value, key_word);
        break;
    case MAX9860_REG_NOISE_GATEMICROPHONE_AGC:
        res = max9860_reg_0f_noise_gate_microphone_agc_diag(value, key_word);
        break;
    case MAX9860_REG_SYSTEM_SHUTDOWN:
        res = max9860_reg_10_system_shutdown_diag(value, key_word);
        break;
    default:
        LOG_ERROR(MAX9860, "Undef Addr %u Reg 0x%x", addr, value);
        res = false;
        break;
    }

    return res;
}

bool max9860_diag_low_level(const char* const key_word) {
    bool res = false;
    LOG_INFO(MAX9860, "LowLevelDiag KeyWord [%s]", key_word);

    res = max9860_reg_read_all();
    if(res) {
        LOG_INFO(MAX9860, "ReadRegsOk");
        log_level_t orig = log_level_get_set(MAX9860, LOG_LEVEL_NOTICE);
        uint8_t i = 0;
        uint8_t ok_cnt = 0;
        for(i = 0; i < MAX9860_REG_CNT; i++) {
            res = max9860_reg_diag(Max9860RegVal[i].addr, Max9860RegVal[i].value.byte, key_word);
            if(res) {
                ok_cnt++;
            }
        }
        if(MAX9860_REG_CNT == ok_cnt) {
            res = true;
        } else {
            res = false;
        }
        set_log_level(MAX9860, orig);
    } else {
        LOG_ERROR(MAX9860, "ReadRegErr");
    }

    return res;
}

bool max9860_reg_map_diag(char* key_word, char* key_word2) {
    bool res = false;
    static const table_col_t cols[] = {{5, "No"}, {6, "addr"}, {6, "val"}, {11, "val [bin]"}, {28, "name"}};
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint8_t i = 0;
    char line_str[120];
    for(i = 0; i < MAX9860_REG_CNT; i++) {
        uint8_t reg_val = 0;
        res = max9860_reg_get(Max9860RegVal[i].addr, &reg_val);
        if(res) {
            strcpy(line_str, TSEP);
            snprintf(line_str, sizeof(line_str), "%s 0x%02x " TSEP, line_str, Max9860RegVal[i].addr);
            snprintf(line_str, sizeof(line_str), "%s 0x%02x " TSEP, line_str, reg_val);
            snprintf(line_str, sizeof(line_str), "%s %9s " TSEP, line_str, utoa_bin8(reg_val));
            snprintf(line_str, sizeof(line_str), "%s %26s " TSEP, line_str, Max9860RegAddr2Name(Max9860RegVal[i].addr));

            res = is_contain(line_str, key_word, key_word2);
            if(res) {
                cli_printf(TSEP " %3u ", num);
                cli_printf("%s" CRLF, line_str);
                num++;
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool max9860_reg_map_hidden_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"},
        {6, "addr"},
        {6, "val"},
        {11, "val [bin]"},
    };
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    int32_t i = 0;
    for(i = 0; i <= 0xFF; i++) {
        uint8_t sone_addr = i;
        res = max9860_is_valid_addr(sone_addr);
        if(false == res) {
            uint8_t reg_val = 0;
            res = max9860_reg_get(sone_addr, &reg_val);
            if(res) {
                char line_str[120] = "";
                if(reg_val) {
                    strcpy(line_str, TSEP);
                    snprintf(line_str, sizeof(line_str), "%s 0x%02x " TSEP, line_str, sone_addr);
                    snprintf(line_str, sizeof(line_str), "%s 0x%02x " TSEP, line_str, reg_val);
                    snprintf(line_str, sizeof(line_str), "%s %9s " TSEP, line_str, utoa_bin8(reg_val));
                    cli_printf(TSEP " %3u ", num);
                    cli_printf("%s" CRLF, line_str);
                    num++;
                }
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool max9860_diag_high_level(void) {
    bool res = false;
    LOG_INFO(MAX9860, "DiagHighLevel");

    res = max9860_is_connected();
    if(res) {
        LOG_INFO(MAX9860, "Connected %s", OnOffToStr(res));

        Gain_t gain = max9860_attenuation_get();
        LOG_INFO(MAX9860, "digital_audio_level %d", gain);

        DigitalFilter_t adc_voice_filter = max9860_voice_filter_get(CONV_ADC);
        LOG_INFO(MAX9860, "AdcVoiceFilter %u", adc_voice_filter);

        DigitalFilter_t dac_voice_filter = max9860_voice_filter_get(CONV_DAC);
        LOG_INFO(MAX9860, "DacVoiceFilter %u", dac_voice_filter);

        Gain_t dac_gain = max9860_dac_gain_get();
        LOG_INFO(MAX9860, "DacGain %d", dac_gain);

        Max9860I2sRole_t i2s_role = max9860_bus_role_get();
        LOG_INFO(MAX9860, "I2sRole %u=%s", i2s_role, Max9860I2sRoleToStr(i2s_role));

        uint32_t reg_cnt = max9860_reg_cnt();
        LOG_INFO(MAX9860, "RegCnt %u", reg_cnt);

        uint8_t volume = max9860_volume_get();
        LOG_INFO(MAX9860, "Volume %u", volume);

        Max9860Item.stereo = max9860_stereo_get();
        LOG_INFO(MAX9860, "Stereo %s", OnOffToStr(Max9860Item.stereo));
    }

    return res;
}
