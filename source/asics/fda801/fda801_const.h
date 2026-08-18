#ifndef FDA801_CONST_H
#define FDA801_CONST_H

#define FDA801_CHANNEL_COUNT 4
#define FDA801_REG_CNT 23U

#define FDA801_BITTNESS 24U
#define FDA801_MAX_AMPLITUDE 8388608 /*(2^24)/2   (2**24)/ 2  */

#define FDA801_ADDRESS1 0x6C
#define FDA801_ADDRESS2 0x6D
#define FDA801_ADDRESS3 0x6E
#define FDA801_ADDRESS4 0x6F

#define FDA801_POLL_PERIOD_S 2

#define REG_INTERFACE 0              /*Table 13*/
#define REG_CR1 1                    /*Table 14*/
#define REG_DIAG 2                   /*Table 15*/
#define REG_CR2 3                    /*Table 16.*/
#define REG_DIAGSEL 4                /*Table 17 */
#define REG_CHN1CNTR 5               /*Table 18*/
#define REG_CHN2CNTR 6               /*Table 19*/
#define REG_CHN3CNTR 7               /*Table 20*/
#define REG_CHN4CNTR 8               /*Table 21*/
#define REG_DIAGPHASEDELAYCNTRCH1 9  /*Table 22*/
#define REG_DIAGPHASEDELAYCNTRCH2 10 /*Table 23*/
#define REG_DIAGPHASEDELAYCNTRCH3 11 /*Table 24*/
#define REG_DIAGPHASEDELAYCNTRCH4 12 /*Table 25*/
#define REG_DIGITAL 13               /*Table 26*/
#define REG_LCFILTERSETUP 14         /*Table 27*/
#define REG_SENSOR 32                /*Table 28*/
#define REG_THERMALWARNING 33        /*Table 29*/
#define REG_CHN1DCOUT 34             /*Table 30*/
#define REG_CHN2DCOUT 35             /*Table 31*/
#define REG_CHN3DCOUT 36             /*Table 32*/
#define REG_CHN4DCOUT 37             /*Table 33*/
#define REG_CH1CH2ACDIAGRES 38       /*Table 34*/
#define REG_CH3CH4ACDIAGRES 39       /*Table 35*/

typedef enum {
    AC_DIAG_NORMAL = 0,
    AC_DIAG_PULSE_END = 1,
    AC_DIAG_UNDEF = 2,
} Fda801AcDiagOps_t;

typedef enum {
    AC_DIAG_DATA_DUD = 0,
    AC_DIAG_DATA_VALID = 1,
    AC_DIAG_DATA_UNDEF = 2,
} Fda801AcDiagValid_t;

typedef enum {
    AC_DIAG_TWEETTER = 0,
    AC_DIAG_NO_TWEETER = 1,
    AC_DIAG_TWEETER_UNDEF = 2,
} Fda801AcDiagTweeter_t;

typedef enum {
    AC_DIAG_NO_WARNING = 0,
    AC_DIAG_WARNING = 1,
    AC_DIAG_WARNING_UNDEF = 2,
} Fda801AcDiagWarning_t;

typedef enum {
    I2S_WS_WATCHDOG_ENABLE = 0,
    I2S_WS_WATCHDOG_DISABLE = 1,
    I2S_WS_WATCHDOG_UNDEF = 2,
} Fda801WsWatchDog_t;

typedef enum {
    FDA_CHANNEL_UNDEF = 0,
    FDA_CHANNEL_1 = 1,
    FDA_CHANNEL_2 = 2,
    FDA_CHANNEL_3 = 3,
    FDA_CHANNEL_4 = 4,
    FDA_CHANNEL_CNT = 4,
} Fda801ChannelNum_t;

typedef enum {
    DC_DIAG_OK = 0,
    DC_DIAG_OPEN_LOAD = 1,
    DC_DIAG_SHORT_LOAD = 2,
    DC_DIAG_SHORT_GND = 3,
    DC_DIAG_SHORT_VCC = 4,
    DC_DIAG_OVERCURRTNT = 5,
    DC_DIAG_UNDEF = 6,
} Fda801DcDiag_t;

typedef enum {
    CH_STATE_MUTE = 0,
    CH_STATE_PLAY = 1,
    CH_STATE_UNDEF = 2,
} Fda801ChannelState_t;

typedef enum {
    CH_AC_DC_DIAG_DISABLE = 0,
    CH_AC_DC_DIAG_START = 1,
    CH_AC_DC_DIAG_UNDEF = 2,
} Fda801ChannelAcDcDiag_t;

typedef enum {
    DC_DIAG_DATA_DUD = 0,
    DC_DIAG_DATA_VALID = 1,
    DC_DIAG_DATA_UNDEF = 3,
} Fda801DcDiagData_t;

typedef enum {
    CH_DIAG_SPEAKER = 0,
    CH_DIAG_LINE_DRIVER = 1,
    CH_DIAG_UNDEF = 2,
} Fda801ChannelDiag_t;

typedef enum {
    DIGITAL_MUTE_ENABLE = 0,
    DIGITAL_MUTE_DISABLE = 1,
    DIGITAL_MUTE_UNDEF = 2,
} Fda801DigitalMute_t;

typedef enum {
    AC_DIAG_STANDART = 0,
    AC_DIAG_REDUSED_AMPLITUDE = 1,
    AC_DIAG_SIG_LVL_UNDEF = 2,
} Fda801AcDiagSignalLevel_t;

typedef enum {
    WDT_I2S_WS_ENABLE = 0,
    WDT_I2S_WS_DISABLE = 1,
    WDT_I2S_WS_UNDEF = 2,
} Fda801WatchDogI2sWs_t;

typedef enum {
    CH_PWM_OFF = 0,
    CH_PWM_ON = 1,
    CH_PWM_UNDEF = 2,
} Fda801ChannelPwm_t;

typedef enum {
    PWM_IN_PHASE = 0,
    PWM_OUT_OF_PHASE = 1,
    PWM_PHASE_UNDEF = 2,
} Fda801PwmPhase_t;

typedef enum {
    FIRST_SETUP_NOT_PROG = 0,
    FIRST_SETUP_PROG = 1,
    FIRST_SETUP_UNDEF = 2,
} Fda801FirstSetUpProg_t;

typedef enum {
    PWM_AMP_CLOCK_NOT_DITHERED = 0,
    PWM_AMP_CLOCK_DITHERED = 1,
    PWM_AMP_CLOCK_DITH_UNDEF = 2,
} Fda801PwmAmpClockDithered_t;

typedef enum {
    LC_FILT_INTERNAL1 = 0,
    LC_FILT_10UH_2_2_UF_OUT = 1,
    LC_FILT_10UH_2_2_UF_IN = 2,
    LC_FILT_10UH_3_3_UF_OUT = 3,
    LC_FILT_10UH_3_3_UF_IN = 4,
    LC_FILT_10UH_4_7_UF_OUT = 5,
    LC_FILT_10UH_4_7_UF_IN = 6,
    LC_FILT_INTERNAL2 = 7,
    LC_FILT_UNDEF = 8,
} Fda801LcFilterSetup_t;

typedef enum {
    I_PROT_11_A = 0,
    I_PROT_8_A = 1,
    I_PROT_5_5_A = 2,
    I_PROT_4_5_A = 3,
    I_PROT_UNDEF = 6,
} Fda801Iprot_t;

typedef enum {
    GAIN_SEL_GV1 = 0,   /**/
    GAIN_SEL_GV2 = 1,   /**/
    GAIN_SEL_GV3 = 2,   /**/
    GAIN_SEL_GV4 = 3,   /**/
    GAIN_SEL_UNDEF = 4, /**/
} Fda801ChannelGain_t;

typedef enum {
    DIAG_TIME_SEL_NORM = 0,
    DIAG_TIME_SEL_X2 = 1,
    DIAG_TIME_SEL_X4 = 2,
    DIAG_TIME_SEL_D2 = 3,
    DIAG_TIME_SEL_UNDEF = 4,
} DiagTimeSel_t;

typedef enum {
    DIAG_HOLD_TIME_NORM = 0,
    DIAG_HOLD_TIME_X2 = 1,
    DIAG_HOLD_TIME_X4 = 2,
    DIAG_HOLD_TIME_D2 = 3,
    DIAG_HOLD_TIME_UNDEF = 6,
} Fda801HoldTime_t;

typedef enum {
    DIAG_RAMP_TIME_NORM = 0,
    DIAG_RAMP_TIME_X2 = 1,
    DIAG_RAMP_TIME_X4 = 2,
    DIAG_RAMP_TIME_D2 = 3,
    DIAG_RAMP_TIME_UNDEF = 6,
} Fda801RampTime_t;

typedef enum {
    DAC_LEV_CTRL_INTERNALY = 0,
    DAC_LEV_CTRL_LOW = 1,
    DAC_LEV_CTRL_MEDIUM = 2,
    DAC_LEV_CTRL_HIGH = 3,
    DAC_LEV_CTRL_UNDEF = 4,
} Fda801DacLevCntrl_t;

typedef enum {
    MUTE_TIMEING_SETUP_3_MS = 0,
    MUTE_TIMEING_SETUP_45_MS = 1,
    MUTE_TIMEING_SETUP_90_MS = 2,
    MUTE_TIMEING_SETUP_185_MS = 3,
    MUTE_TIMEING_SETUP_UNDEF = 4,
} Fda801MuteTimeSetup_t;

typedef enum {
    TEMP_WARN_INFO_TW1 = 0,
    TEMP_WARN_INFO_TW2 = 1,
    TEMP_WARN_INFO_TW3 = 2,
    TEMP_WARN_INFO_TW4 = 3,
    TEMP_WARN_INFO_UNDEF = 4,
} Fda801TempWarnInfo_t;

typedef enum {
    SWITCH_FREQ_ON_44_1_KHZ_308_7_KHZ = 0,
    SWITCH_FREQ_ON_44_1_KHZ_352_8_KHZ = 1,
    SWITCH_FREQ_ON_44_1_KHZ_396_9_KHZ = 2,
    SWITCH_FREQ_ON_44_1_KHZ_UNDEF = 4,
} Fda801SwFreqOn44_1_t;

typedef enum {
    SWITCH_FREQ_ON_48KHZ_336_KHZ = 0,
    SWITCH_FREQ_ON_48KHZ_384_KHZ = 1,
    SWITCH_FREQ_ON_48KHZ_432_KHZ = 2,
    SWITCH_FREQ_ON_48KHZ_UNDEF = 4,
} Fda801SwFreqOn48_t;

typedef enum {
    SWITCH_FREQ_ON_96KHZ_384_KHZ = 0,
    SWITCH_FREQ_ON_96KHZ_UNDEF = 4,
} Fda801SwFreqOn96_t;

typedef enum {
    SWITCH_FREQ_ON_192KHZ_384_KHZ = 0,
    SWITCH_FREQ_ON_192KHZ_UNDEF = 4,
} Fda801SwFreqOn192_t;

typedef enum {
    DIGITAL_INPUT_FRAME_SYN_FREQ_44_1_KHZ = 0,
    DIGITAL_INPUT_FRAME_SYN_FREQ_48_KHZ = 1,
    DIGITAL_INPUT_FRAME_SYN_FREQ_96_KHZ = 2,
    DIGITAL_INPUT_FRAME_SYN_FREQ_192_KHZ = 3,
    DIGITAL_INPUT_FRAME_SYN_FREQ_UNDEF = 4,
} Fda801DigitalInputFrameSyncFreq_t;

typedef enum {
    DIG_IN_SETTINGS_I2S = 0,
    DIG_IN_SETTINGS_TDM_4_CH = 1,
    DIG_IN_SETTINGS_TDM_8_CH_MODE_1 = 2,
    DIG_IN_SETTINGS_TDM_8_CH_MODE_2 = 3,
    DIG_IN_SETTINGS_UNDEF = 4,
} Fda801DigitalInputSettings_t;

#endif /* FDA801_CONST_H */
