#include "fda801_diag.h"

#include <stdio.h>

#include "fda801_const.h"
#ifdef HAS_LOG
#include "log.h"
#endif
#include "fda801_drv.h"
#include "common_diag.h"

const char* AcDiagOpToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case 0:name="normal"; break;
    case 1:name="Tdm4Ch"; break;
    }
    return name;
}

const char* DigitalInSetToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case DIG_IN_SETTINGS_I2S:name="I2S"; break;
    case DIG_IN_SETTINGS_TDM_4_CH:name="Tdm4Ch"; break;
    case DIG_IN_SETTINGS_TDM_8_CH_MODE_1: name="Tdm8ChM1";break;
    case DIG_IN_SETTINGS_TDM_8_CH_MODE_2: name="Tdm8ChM2";break;
    }
    return name;
}

char* TemperWarningInfoToStr(uint8_t code){
    char *name="?";
    switch(code){
      case TEMP_WARN_INFO_TW1: name="TW1"; break;
      case TEMP_WARN_INFO_TW2: name="TW2"; break;
      case TEMP_WARN_INFO_TW3: name="TW3"; break;
      case TEMP_WARN_INFO_TW4: name="TW4"; break;
    }
    return name;
}

uint32_t DigitalFrameSync2Num(uint8_t code){
	uint32_t sampling_rate_hz=0;
    switch(code){
    case DIGITAL_INPUT_FRAME_SYN_FREQ_44_1_KHZ:sampling_rate_hz=44100; break;
    case DIGITAL_INPUT_FRAME_SYN_FREQ_48_KHZ:sampling_rate_hz=48000; break;
    case DIGITAL_INPUT_FRAME_SYN_FREQ_96_KHZ: sampling_rate_hz=96000;break;
    case DIGITAL_INPUT_FRAME_SYN_FREQ_192_KHZ: sampling_rate_hz=192000;break;
    }
    return sampling_rate_hz;
}

uint32_t SwFreq44kHz2Num(uint8_t code){
	uint32_t switching_freq_hz=0;
    switch(code){
    case SWITCH_FREQ_ON_44_1_KHZ_308_7_KHZ: switching_freq_hz=308700; break;
    case SWITCH_FREQ_ON_44_1_KHZ_352_8_KHZ: switching_freq_hz=352800; break;
    case 3:
    case 4:
    	switching_freq_hz = 396900;
    	break;
    }
    return switching_freq_hz;
}

uint32_t SwFreq48kHz2Num(uint8_t code){
	uint32_t switching_freq_hz=0;
    switch(code){
    case SWITCH_FREQ_ON_48KHZ_336_KHZ: switching_freq_hz=336000; break;
    case SWITCH_FREQ_ON_48KHZ_384_KHZ: switching_freq_hz=384000; break;
    case 2:
    case 3:
    	switching_freq_hz = 432000;break;
    }
    return switching_freq_hz;
}

uint32_t SwFreq96kHz2Num(uint8_t code){
	uint32_t switching_freq_hz=0;
    switch(code){
    case 0:
    case 1:
    case 2:
    case 3:
    	switching_freq_hz=384000; break;
    }
    return switching_freq_hz;
}


uint32_t SwFreq192kHz2Num(uint8_t code){
	uint32_t switching_freq_hz=0;
    switch(code){
    case 0:
    case 1:
    case 2:
    case 3:
    	switching_freq_hz=384000; break;
    }
    return switching_freq_hz;
}

const char* IprotToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case I_PROT_11_A:name="11A"; break;
    case I_PROT_8_A:name="8A"; break;
    case I_PROT_5_5_A: name="5.5A";break;
    case I_PROT_4_5_A: name="4.5A";break;
    }
    return name;
}

const char* GainSelToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case GAIN_SEL_GV1:name="Gv1"; break;
    case GAIN_SEL_GV2:name="Gv2"; break;
    case GAIN_SEL_GV3: name="Gv3";break;
    case GAIN_SEL_GV4: name="Gv4";break;
    }
    return name;
}

const char* ShortVccToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case 0:name="."; break;
    case 1:name="ShVcc"; break;
    }
    return name;
}

const char* LoadOpenToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case 0:name="Ok!"; break;
    case 1:name="OpenLd"; break;
    }
    return name;
}

const char* OverCurrentToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case 0:name="."; break;
    case 1:name="OverCurr"; break;
    }
    return name;
}

const char* ShortLoadToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case 0:name="."; break;
    case 1:name="ShLoad"; break;
    }
    return name;
}

const char* ShortGndToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case 0:name="."; break;
    case 1:name="ShGnd"; break;
    }
    return name;
}

const char* ChanDiagToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case 0:name="Speaker"; break;
    case 1:name="LineDriver"; break;
    }
    return name;
}

uint8_t MuteTimeSetup2Ms(uint8_t code){
	uint8_t mute_time=0;
    switch(code){
    case MUTE_TIMEING_SETUP_3_MS:   mute_time=3;  break;
    case MUTE_TIMEING_SETUP_45_MS:  mute_time=45; break;
    case MUTE_TIMEING_SETUP_90_MS:  mute_time=90; break;
    case MUTE_TIMEING_SETUP_185_MS: mute_time=185;break;
    }
    return mute_time;
}

const char* LcFiltSetupToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case LC_FILT_10UH_2_2_UF_OUT: name="10uH+2.2uF_Out"; break;
    case LC_FILT_10UH_2_2_UF_IN:  name="10uH+2.2uF_in"; break;
    case LC_FILT_10UH_3_3_UF_OUT: name="10uH+3.3uF_Out";break;
    case LC_FILT_10UH_3_3_UF_IN:  name="10uH+3.3uF_in";break;
    case LC_FILT_10UH_4_7_UF_OUT: name="10uH+4.7uF_Out";break;
    case LC_FILT_10UH_4_7_UF_IN:  name="10uH+4.7uF_in";break;
    }
    return name;
}


const char* PwmPaseToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case PWM_IN_PHASE: name="InPhase"; break;
    case PWM_OUT_OF_PHASE:  name="OutOfPhase"; break;
    }
    return name;
}

const char* ChannelFaultToStr(uint8_t code){
    const char *name="?";


    return name;
}

const char* OpenLoadToStr(uint8_t code){
    const char* name="?";
    switch(code){
    case 1: name="Open"; break;
    case 0:  name="Ok"; break;
    }
    return name;
}

const char* DcDiagDataValidToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case DC_DIAG_DATA_DUD: name="Dud"; break;
    case DC_DIAG_DATA_VALID:  name="Valid"; break;
    }
    return name;
}

const char* AcDiagWarnToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case 0:  name="NoWarn"; break;
    case 1:  name="Warn"; break;
    }
    return name;
}

const char* AcDiagTweetToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case 0: name="Tweet"; break;
    case 1:  name="NoTweet"; break;
    }
    return name;
}

const char* AcDiagDataValidToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case AC_DIAG_DATA_DUD: name="Dud"; break;
    case AC_DIAG_DATA_VALID:  name="Valid"; break;
    }
    return name;
}


const char* ChannelStateToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case CH_STATE_MUTE: name="Mute"; break;
    case CH_STATE_PLAY:  name="Play"; break;
    }
    return name;
}

const char* PwmAmplifierToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case 0: name="not"; break;
    case 1:  name=""; break;
    }
    return name;
}

const char*  DoubleChOperToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case 0: name="normal"; break;
    case 1:  name="parallel"; break;
    }
    return name;
}

const char* LowBatMuteToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case 0: name="low"; break;
    case 1:  name="high"; break;
    }
    return name;
}


const char* LowSidePowerHalvingToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case 0: name="and CMC internal control"; break;
    case 1:  name="I2C controlled"; break;
    }
    return name;
}

const char* fda801_get_reg_name(uint8_t addr){
    uint32_t i=0;
    const char *name="?";
    uint32_t reg_cnt=fda801_reg_cnt( );
    for(i=0;i<reg_cnt;i++) {
        if(Fda801RegMap[i].reg_addr==addr){
            name = Fda801RegMap[i].name;
            break;
        }
    }
    return name;
}

const char* CmcToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case 0: name="fully differential"; break;
    case 1:  name="single ended"; break;
    }
    return name;
}

const char* PowerDiagSelToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case 0: name="Full"; break;
    case 1: name="Half"; break;
    }
    return name;
}

const char* PlayMuteToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case 0: name="Mute"; break;
    case 1: name="Play"; break;
    }
    return name;
}

const char* FirstSetUpToStr(uint8_t code){
    const char *name = "?";
    switch(code){
      case 0: name = "NotProgrammedViaI2C"; break;
      case 1: name = "ProgrammedReadyToWork"; break;
    }
    return name;
}

const char* EnableToStr(uint8_t code){
    char *name = "?";
    switch(code){
      case 0: name = "Enabled"; break;
      case 1: name = "Disabled"; break;
    }
    return name;
}


const char* DigitalMuteToStr(uint8_t code){
    return EnableToStr(  code);
}

const char* WatchDogI2sWsToStr(uint8_t code){
    return EnableToStr(  code);
}




const char* AcDigSigLvlToStr(uint8_t code){
    const char *name="?";
    switch(code){
      case 0: name="Std"; break;
      case 1: name="RdcdAmpl"; break;
    }
    return name;
}

const char* DcOperationToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case 0: name="Normal"; break;
    case 1: name="DcDiagPulseEnded"; break;
    }
    return name;
}

const char* AcOperationToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case 0: name="Normal"; break;
    case 1: name="AcDiagPulseEnd"; break;
    }
    return name;
}

char* DacLevelToStr(uint8_t code){
    char *name="?";
    switch(code){
    case DAC_LEV_CTRL_INTERNALY: name="internally"; break;
    case DAC_LEV_CTRL_LOW:       name="low"; break;
    case DAC_LEV_CTRL_MEDIUM:    name="medium"; break;
    case DAC_LEV_CTRL_HIGH:      name="high"; break;
    }
    return name;
}

bool fda801_parse_cr2(uint8_t reg_val, char *keyWord1){
    bool res = false;
    Fda801RegIb3Addr_t Reg;
    char line[80]="";
    Reg.reg_val = reg_val;
    snprintf(line, sizeof(line),"%u PwrDiagSel %s", Reg.power_diag_sel,PowerDiagSelToStr(Reg.power_diag_sel));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line, sizeof(line),"%u DAC %s", Reg.dac_level_ctrl,DacLevelToStr(Reg.dac_level_ctrl));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line, sizeof(line),"%u CMC %s", Reg.cmc_fully_differential,CmcToStr(Reg.cmc_fully_differential));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line, sizeof(line),"%u Mute timing setup %u ms", Reg.cmc_fully_differential,MuteTimeSetup2Ms(Reg.cmc_fully_differential));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line, sizeof(line),"%u Low side power halving %s", Reg.low_side_power_control,LowSidePowerHalvingToStr(Reg.low_side_power_control));
    log_print_conditional(FDA801, line, keyWord1, NULL);
    return res;
}

char* DiagTimeSelToStr(uint8_t code){
    char *name="?";
    switch(code){
    case DIAG_TIME_SEL_NORM:name="Norm"; break;
    case DIAG_TIME_SEL_X2:  name="x2"; break;
    case DIAG_TIME_SEL_X4:  name="x4";break;
    case DIAG_TIME_SEL_D2:  name="/2";break;
    }
    return name;
}

/*
  Table 30
  Table 31
  Table 32
  Table 33
  */
bool fda801_parse_ch_dc_out(uint8_t reg_val,uint8_t channel, char *keyWord1){
    bool res = false;
    Fda801RegChannelDCOutputs_t Reg;
    Reg.reg_val = reg_val;
    char line[80]="";

    snprintf(line,sizeof(line),"CH%u in %u=%s ",channel, Reg.state, PlayMuteToStr(Reg.state));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"CH%u LoadOpen %u=%s ",channel, Reg.load_open, OnOffToStr(Reg.load_open));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"CH%u LoadShort %u=%s ",channel, Reg.load_short, OnOffToStr(Reg.load_short));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"CH%u ShortGND %u=%s ",channel, Reg.short_gnd, OnOffToStr(Reg.short_gnd));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"CH%u ShortVcc %u=%s ",channel, Reg.short_vcc, OnOffToStr(Reg.short_vcc));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"CH%u OverCurrent %u=%s ",channel, Reg.overcurrent, OnOffToStr(Reg.overcurrent));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"CH%u DiagValid %u=%s ",channel, Reg.diag_valid, OnOffToStr(Reg.diag_valid));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"CH%u Operation %u=%s ",channel, Reg.operation, DcOperationToStr(Reg.operation));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    return res;
}

bool fda801_parse_ch_ctrl(uint8_t reg_val,uint8_t channel, char *keyWord1){
    bool res = false;
    Fda801RegChannelCtrl_t  Reg;
    Reg.reg_val = reg_val;
    char line[80]="";
    snprintf(line,sizeof(line),"CH%u in %u=%s",channel, Reg.chx_status, PlayMuteToStr(Reg.chx_status));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"CH%u AcDiag %u=%s",channel, Reg.chx_ac_diag, OnOffToStr(Reg.chx_ac_diag));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"CH%u DcDiag %u=%s",channel, Reg.chx_dc_diag, OnOffToStr(Reg.chx_dc_diag));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"CH%u %u=%s Diag",channel, Reg.chx_diag, ChanDiagToStr(Reg.chx_diag));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"CH%u PWM %u=%s ",channel, Reg.chx_pwm, OnOffToStr(Reg.chx_pwm));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"CH%u GainSel %u=%s ",channel, Reg.chx_gain_sel, GainSelToStr(Reg.chx_gain_sel));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"CH%u AcExtTestFlag %u=%s ",channel, Reg.chx_ac_ext_test, OnOffToStr(Reg.chx_ac_ext_test));
    log_print_conditional(FDA801, line, keyWord1, NULL);
    return res;
}

bool fda801_parse_ch_diag_phase_sel_ctrl(uint8_t reg_val,uint8_t channel, char *keyWord1){
    bool res = false;
    Fda801PhaseDelayCtrl_t Reg;
    Reg.reg_val = reg_val;
    char line[80]="";
    snprintf(line,sizeof(line),"CH%u DiagPhaseDelayCtrl %u", channel, Reg.diag_phase_delay_ctrl);
    log_print_conditional(FDA801, line, keyWord1, NULL);
    return res;
}

bool fda801_parse_ch1_ctrl(uint8_t reg_val, char *keyWord1){
    bool res = false;
    res = fda801_parse_ch_ctrl(reg_val, 1, keyWord1);
    return res;
}

bool fda801_parse_ch2_ctrl(uint8_t reg_val, char *keyWord1){
    bool res = false;
    res = fda801_parse_ch_ctrl(reg_val, 2, keyWord1);
    return res;
}

bool fda801_parse_ch3_ctrl(uint8_t reg_val, char *keyWord1){
    bool res = false;
    res = fda801_parse_ch_ctrl(reg_val, 3, keyWord1);
    return res;
}



bool fda801_parse_ch1_dc_out(uint8_t reg_val, char *keyWord1){
    bool res = false;
    res = fda801_parse_ch_dc_out(reg_val, 1, keyWord1);
    return res;
}
bool fda801_parse_ch2_dc_out(uint8_t reg_val, char *keyWord1){
    bool res = false;
    res = fda801_parse_ch_dc_out(reg_val, 2, keyWord1);
    return res;
}
bool fda801_parse_ch3_dc_out(uint8_t reg_val, char *keyWord1){
    bool res = false;
    res = fda801_parse_ch_dc_out(reg_val, 3, keyWord1);
    return res;
}
bool fda801_parse_ch4_dc_out(uint8_t reg_val, char *keyWord1){
    bool res = false;
    res = fda801_parse_ch_dc_out(reg_val, 4, keyWord1);
    return res;
}


bool fda801_parse_ch1_diag_phase_sel_ctrl(uint8_t reg_val, char *keyWord1){
    bool res = false;
    res = fda801_parse_ch_diag_phase_sel_ctrl(reg_val, 1, keyWord1);
    return res;
}

bool fda801_parse_ch2_diag_phase_sel_ctrl(uint8_t reg_val, char *keyWord1){
    bool res = false;
    res = fda801_parse_ch_diag_phase_sel_ctrl(reg_val, 2, keyWord1);
    return res;
}

bool fda801_parse_ch3_diag_phase_sel_ctrl(uint8_t reg_val, char *keyWord1){
    bool res = false;
    res = fda801_parse_ch_diag_phase_sel_ctrl(reg_val, 3, keyWord1);
    return res;
}

bool fda801_parse_ch4_diag_phase_sel_ctrl(uint8_t reg_val, char *keyWord1){
    bool res = false;
    res = fda801_parse_ch_diag_phase_sel_ctrl(reg_val, 4, keyWord1);
    return res;
}

bool fda801_parse_ch4_ctrl(uint8_t reg_val, char *keyWord1){
    bool res = false;
    res = fda801_parse_ch_ctrl(reg_val, 4,keyWord1);
    return res;
}

#define CHX_CHY_DIAG_RES(CHX)                                                                                                            \
   do{                                                                                                                                   \
       char line[80]="";                                                                                                                 \
       snprintf(line,sizeof(line),"Ch%u %u=%s ErrWarn",CHX,Reg.ch##CHX##_error_warning , YesNoToStr(Reg.ch##CHX##_error_warning ));       \
       log_print_conditional(FDA801, line, keyWord1, NULL);                                                                              \
       snprintf(line,sizeof(line),"Ch%u %u=%s Tweeter present",CHX,Reg.ch##CHX##_tweeter , YesNoToStr(!Reg.ch##CHX##_tweeter ));          \
       log_print_conditional(FDA801, line, keyWord1, NULL);                                                                              \
       snprintf(line,sizeof(line),"Ch%u AcDiagData %u=%s Valid",CHX,Reg.ch##CHX##_ac_diag_data , YesNoToStr(Reg.ch##CHX##_ac_diag_data ));\
       log_print_conditional(FDA801, line, keyWord1, NULL);                                                                              \
       snprintf(line,sizeof(line),"Ch%u Operation %u=%s",CHX ,Reg.ch##CHX##_operation, AcOperationToStr(Reg.ch##CHX##_operation));        \
       log_print_conditional(FDA801, line, keyWord1, NULL);                                                                              \
   }while(0);

/*Table 34*/
bool fda801_parse_ch1ch2_ac_diag(uint8_t reg_val, char *keyWord1){
    bool res = false;
    Fda801RegCh1Ch2AcDiag_t Reg;
    Reg.reg_val = reg_val;
    CHX_CHY_DIAG_RES(1);
    CHX_CHY_DIAG_RES(2);
    return res;
}

/*Table 35*/
bool fda801_parse_ch3ch4_ac_diag(uint8_t reg_val, char *keyWord1){
    bool res = false;
    Fda801RegCh3Ch4AcDiag_t Reg;
    Reg.reg_val = reg_val;
    CHX_CHY_DIAG_RES(3);
    CHX_CHY_DIAG_RES(4);
    return res;
}

/*T able 29*/
bool fda801_parse_termal(uint8_t reg_val, char *keyWord1){
    bool res = false;
    Fda801RegDb1Addr_t  Reg;
    Reg.reg_val = reg_val;
    char line[80]="";
    snprintf(line,sizeof(line),"%u Thermal warning 1 %s active",Reg.thermal_warning_1_not_active, YesNoToStr(Reg.thermal_warning_1_not_active ));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"%u Thermal warning 2 %s active",Reg.thermal_warning_2_not_active, YesNoToStr(Reg.thermal_warning_2_not_active ));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"%u Thermal warning 3 %s active",Reg.thermal_warning_3_not_active, YesNoToStr(Reg.thermal_warning_3_not_active ));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"%u Thermal warning 4 %s active",Reg.thermal_warning_4_not_active, YesNoToStr(Reg.thermal_warning_4_not_active ));
    log_print_conditional(FDA801, line, keyWord1, NULL);
    return res;
}

/*Table 28*/
bool fda801_parse_sensor(uint8_t reg_val, char *keyWord1){
    bool res = false;
    Fda801RegDb0Addr_t Reg;
    Reg.reg_val = reg_val;
    char line[80]="";
    snprintf(line,sizeof(line),"%u PllLock %s",Reg.pll_lock, OnOffToStr(Reg.pll_lock));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"%u UVLO %s detected",Reg.uvlo_sens, YesNoToStr(Reg.uvlo_sens));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"%u %s DumpPulsesDetected",Reg.dump_pulses_sens, YesNoToStr(Reg.dump_pulses_sens));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"%u Clipping %s reached",Reg.clipping_sens, YesNoToStr(Reg.clipping_sens));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"%u %s DC component present on output signal",Reg.output_offset_sens, YesNoToStr(Reg.output_offset_sens));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"%u %s DC component present on input signal",Reg.input_offset_sens, YesNoToStr(Reg.input_offset_sens));
    log_print_conditional(FDA801, line, keyWord1, NULL);
    return res;
}

bool fda801_parse_lc_filt_set(uint8_t reg_val, char *keyWord1){
    bool res = false;
    Fda801RegIb14Addr_t Reg;
    Reg.reg_val = reg_val;
    char line[80]="";
    snprintf(line,sizeof(line),"%u FirstSetUp %s",Reg.first_setup, FirstSetUpToStr(Reg.first_setup ));
    log_print_conditional(FDA801, line, keyWord1, NULL);
    snprintf(line,sizeof(line),"%u LcFilterSetUp %s",Reg.lc_filetr_setup, LcFiltSetupToStr(Reg.lc_filetr_setup ));
    log_print_conditional(FDA801, line, keyWord1, NULL);
    return res;
}

/*Table 26*/
bool fda801_parse_digital2(uint8_t reg_val, char *keyWord1){
    bool res = false;
    Fda801RegIb13Addr_t  Reg;
    Reg.reg_val = reg_val;
    char line[80]="";
    snprintf(line,sizeof(line),"%u DigitalMute %s",Reg.digital_mute, DigitalMuteToStr(Reg.digital_mute));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"%u AcDigitalSignalLvl %s",Reg.ac_diag_signal_level, AcDigSigLvlToStr(Reg.ac_diag_signal_level));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"%u CmdPWMPeak %s",Reg.cmdpwm_peak, OnOffToStr(Reg.cmdpwm_peak));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"%u WatchDogOnI2Sws %s",Reg.watchdog_on_i2sws_signal, WatchDogI2sWsToStr(Reg.watchdog_on_i2sws_signal));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    return res;
}

bool fda801_parse_diagsel(uint8_t reg_val, char *keyWord1){
    bool res = false;
    Fda801RegIb4Addr_t Reg;
    Reg.reg_val = reg_val;
    char line[80]="";
    snprintf(line,sizeof(line),"%u DiagRampTimeSel %s",Reg.diag_ramp_time_sel,DiagTimeSelToStr(Reg.diag_ramp_time_sel));
    log_print_conditional(FDA801, line, keyWord1, NULL);
    snprintf(line,sizeof(line),"%u DiagHoldTimeSel %s",Reg.diag_hold_time_sel,DiagTimeSelToStr(Reg.diag_hold_time_sel));
    log_print_conditional(FDA801, line, keyWord1, NULL);
    return res;
}

bool fda801_parse_diag(uint8_t reg_val, char *keyWord1){
    bool res = false;
    Fda801RegIb2Addr_t Reg;
    Reg.reg_val = reg_val;
    char line[80]="";
    snprintf(line,sizeof(line),"%u %s Temperature warning information on CD/DIAG pin:",Reg.temperature_warning_information,TemperWarningInfoToStr(Reg.temperature_warning_information));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"%u %s fault information on CD/DIAG pin",Reg.fault_information,YesNoToStr(Reg.fault_information));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"%u %s Input Offset information on CD/DIAG pin",Reg.input_offset_information,YesNoToStr(Reg.input_offset_information));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"%u %s Output Offset information on CD/DIAG pin",Reg.output_offset_information,YesNoToStr(Reg.output_offset_information));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line,sizeof(line),"%u %s Clipping information on CD/DIAG pin",Reg.clipping_information,YesNoToStr(Reg.clipping_information));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    return res;
}

bool fda801_parse_cr1(uint8_t reg_val, char *keyWord1){
    bool res = false;
    Fda801RegIb1Addr_t Reg;
    Reg.reg_val = reg_val;
    char line[80]="";

    snprintf(line, sizeof(line),"%u Output offset detector %s", Reg.output_offset_detector,OnOffToStr(Reg.output_offset_detector));
    log_print_conditional(FDA801, line, keyWord1, NULL);
    snprintf(line, sizeof(line),"%u Input offset detector %s", Reg.input_offset_detector,OnOffToStr(Reg.input_offset_detector));
    log_print_conditional(FDA801, line, keyWord1, NULL);
    snprintf(line, sizeof(line),"%u %s High-pass in the DAC", Reg.high_pass_in_the_dac,YesNoToStr(Reg.high_pass_in_the_dac));
    log_print_conditional(FDA801, line, keyWord1, NULL);
    snprintf(line, sizeof(line),"%u Low radiation function %s", Reg.low_radiation_function,OnOffToStr(Reg.low_radiation_function));
    log_print_conditional(FDA801, line, keyWord1, NULL);
    snprintf(line, sizeof(line),"%u Low battery mute and UVLO at %s level", Reg.low_battery_mute_and_uvlo,LowBatMuteToStr(Reg.low_battery_mute_and_uvlo));
    log_print_conditional(FDA801, line, keyWord1, NULL);
    snprintf(line, sizeof(line),"%u Noise gate %s", Reg.noise_gate,OnOffToStr(Reg.noise_gate));
    log_print_conditional(FDA801, line, keyWord1, NULL);
    snprintf(line, sizeof(line),"%u Ch3Ch4 %s operation", Reg.ch3_and_ch4_operation,DoubleChOperToStr(Reg.ch3_and_ch4_operation));
    log_print_conditional(FDA801, line, keyWord1, NULL);
    snprintf(line, sizeof(line),"%u Ch1Ch2 %s operation", Reg.ch1_and_ch2_operation,DoubleChOperToStr(Reg.ch1_and_ch2_operation));
    return res;
}

bool fda801_parse_if(uint8_t reg_val, char *keyWord1){
    bool res = false;
    Fda801RegInterface_t Reg;
    Reg.reg_val = reg_val;
    char line[80]="";

    snprintf(line, sizeof(line), "Digital input setting  %u %s",Reg.digital_input_settings, DigitalInSetToStr(Reg.digital_input_settings));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    snprintf(line, sizeof(line), "Fs %u %u Hz",(unsigned int)Reg.fs, (unsigned int)DigitalFrameSync2Num(Reg.fs));
    log_print_conditional(FDA801, line, keyWord1, NULL);

    switch(Reg.fs){
    case DIGITAL_INPUT_FRAME_SYN_FREQ_44_1_KHZ:
        snprintf(line, sizeof(line), "%u Switching frequency %u",(unsigned int)Reg.switching_frequency,(unsigned int) SwFreq44kHz2Num(Reg.switching_frequency));
        log_print_conditional(FDA801, line, keyWord1, NULL);
        break;
    case DIGITAL_INPUT_FRAME_SYN_FREQ_48_KHZ:
        snprintf(line, sizeof(line), "%u Switching frequency %u",(unsigned int)Reg.switching_frequency, (unsigned int)SwFreq48kHz2Num(Reg.switching_frequency));
        log_print_conditional(FDA801, line, keyWord1, NULL);
        break;
    case DIGITAL_INPUT_FRAME_SYN_FREQ_96_KHZ:
        snprintf(line, sizeof(line), "%u Switching frequency %u",(unsigned int)Reg.switching_frequency, (unsigned int)SwFreq96kHz2Num(Reg.switching_frequency));
        log_print_conditional(FDA801, line, keyWord1, NULL);
        break;
    case DIGITAL_INPUT_FRAME_SYN_FREQ_192_KHZ:
        snprintf(line, sizeof(line), "%u Switching frequency %u",(unsigned int)Reg.switching_frequency, (unsigned int)SwFreq192kHz2Num(Reg.switching_frequency));
        log_print_conditional(FDA801, line, keyWord1, NULL);
        break;
    }
    snprintf(line, sizeof(line), "%u PWM amplifier %s dithered",Reg.pwm_amplifier_clock, PwmAmplifierToStr(Reg.pwm_amplifier_clock));
    log_print_conditional(FDA801, line, keyWord1, NULL);
    snprintf(line, sizeof(line), "%u PWM %10s phase",Reg.pwm_phase, PwmPaseToStr(Reg.pwm_phase));
    log_print_conditional(FDA801, line, keyWord1, NULL);
    return res;
}

const char* ChPwmToStr(uint8_t code){
    const char *name="?";
    switch(code){
    case CH_PWM_OFF:name="PwmOff"; break;
    case CH_PWM_ON:  name="PwmOn"; break;
    }
    return name;
}

char* ChannelToStr(Fda801ChannelNum_t Channel){
    static char name[5]="Ch?";
    bool res = fda801_is_valid_channel(Channel);
    if(res){
        snprintf(name, sizeof(name), "Ch%1u", Channel);
    }
    return name;
}
