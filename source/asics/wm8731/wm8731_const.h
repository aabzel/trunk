#ifndef WM8731_CONST_H
#define WM8731_CONST_H

#include "wm8731_dep.h"

#define WM8731_PERIOD_US 100000
#define WM8731_7BIT_ADDRESS    (0x1a)
#define WM8731_WRITE_ADDRESS   (0x34)
#define WM8731_READ_ADDRESS    (0x35)
#define WM8731_VERIFY_AMP 200
#define WM8731_MAX_AMP (8388608) // (2^24)/2
#define WM8731_VERIFY_FREQ_HZ 1000.0
#define WM8731_VERIFY_DURATION_MS 1000
#define WM_MAX_VOL_DB (6)
#define WM_MIN_VOL_DB (-73)

typedef enum {
    WM8731_REG_LINVOL =   0x00,
    WM8731_REG_RINVOL =   0x01,
    WM8731_REG_LOUT1V =   0x02,
    WM8731_REG_ROUT1V =   0x03,
    WM8731_REG_APANA  =   0x04,
    WM8731_REG_APDIGI =   0x05,
    WM8731_REG_PWR    =   0x06,
    WM8731_REG_IFACE  =   0x07, /*0x07 Digital audio interface format */
    WM8731_REG_SRATE  =   0x08,
    WM8731_REG_ACTIVE =   0x09,
    WM8731_REG_RESET  =   0x0f,

    WM8731_REG_UNDEF  =   0xFf,
}Wm8731RegAddr_t;


typedef enum {
    MUTE_OFF=0,
    MUTE_ON=1,
    MUTE_UNDEF=2,
}Mute_t;

typedef enum {
    WM8731_STATE_IDLE = 0,
    WM8731_STATE_PLAY = 1,
    WM8731_STATE_RECORD = 2,
}Wm8731State_t;

typedef enum {
    MIC_MUTE_OFF=0,
    MIC_MUTE_ON=1,
    MIC_MUTE_UNDEF=2,
}MicMute_t;

typedef enum {
    CORE_CLK_MCLK=0,
    CORE_CLK_MCLK_DIV_2=1,
    CORE_CLK_UNDEF=2,
}CoreClkDivSel_t;

typedef enum {
    CLK_OUT_CORE_CLK=0,
    CLK_OUT_CORE_CLK_DIV_2=1,
    CLK_OUT_UNDEF=2,
}ClkOutDivSel_t;

typedef enum {
    DAC_SW_MUTE_OFF=0,
    DAC_SW_MUTE_ON=1,
    DAC_SW_MUTE_UNDEF=2,
}DacSoftMute_t;

//De-emphasis Control
typedef enum {
    DE_EMPH_48000HZ=3,
    DE_EMPH_44100HZ=2,
    DE_EMPH_32000HZ=1,
    DE_EMPH_OFF=0,

    DE_EMPH_UNDEF=4,
}DeEmphasis_t;

typedef enum {
    DC_OFFSET_STORE=1,
    DC_OFFSET_CLEAR=0,
    DC_OFFSET_UNDEF=2,
}DcOffSet_t;

/*Digital Audio Path Control*/
typedef enum {
    ADC_HI_PASS_FILT_OFF = 1,
    ADC_HI_PASS_FILT_ON = 0,

    ADC_HI_PASS_FILT_UNDEF = 2,
}AdcHiPassFilt_t;

typedef enum {
    FMT_DSP=3,
    FMT_I2S=2,
    FMT_MSB_F_LEFT=1,
    FMT_MSB_F_RIGHT=0,
    FMT_UNDEF=4,
}AudioDataFormat_t;

/* Digital Audio Interface Format Input Audio Data Bit Length*/
typedef enum {
    AUD_BIT_32=3,
    AUD_BIT_24=2,
    AUD_BIT_20=1,
    AUD_BIT_16=0,

    AUD_BIT_UNDEF=4,
}AudioBittness_t;

typedef enum {
    I2S_DAC_PHASE_RIGHT_CH_DAC_DACLRC_HI=1,
    I2S_DAC_PHASE_RIGHT_CH_DAC_DACLRC_LO=0,

    I2S_DAC_PHASE_UNDEF=2,
}I2sDacLrPhase_t;

typedef enum {
    I2S_DSP_MSB_2ND_BCLK_RISING=1,
    I2S_DSP_MSB_1ST_BCLK_RISING=0,
    I2S_DSP_UNDEF=2,
}DspAbSel_t;

typedef enum {
    MODE_NORMAL=0,
    MODE_USB=1,
    MODE_UNDEF=2,
}Wm8731Mode_t;

typedef enum {
    DAC_LR_CLK_LEFT=1,
    DAC_LR_CLK_RIGHT=0,
    DAC_LR_CLK_UNDEF=2,
}DacLRclockSwap_t;

typedef enum {
    BUS_MODE_MASTER=1,
    BUS_MODE_SLAVE=0,
    BUS_MODE_UNDEF=3,
}Wm8731BusRole_t;

typedef enum {
    BIT_CLOCK_INVERT=1,
    BIT_CLOCK_NORMAL=0,
    BIT_CLOCK_UNDEF=3,
}BitClockInv_t;

typedef enum {
    MIC_IN_BOOST_ON=1,
    MIC_IN_BOOST_OFF=0,
    MIC_IN_BOOST_UNDEF=2,
}MicInBoost_t;

typedef enum {
    ADC_IN_SEL_MIC=1,
    ADC_IN_SEL_LINE=0,

    ADC_IN_SEL_UNDEF=2,
}AdcInSelect_t;

typedef enum {
    SIDE_TONE_ON = 1,
    SIDE_TONE_OFF = 0,

    SIDE_TONE_UNDEF = 2,
}SideTone_t;

typedef enum {
    DAC_SEL_ON=1,
    DAC_SEL_OFF=0,
    DAC_SEL_UNDEF=2,
}DacSel_t;

typedef enum {
    BYPASS_SW_OFF=0,
    BYPASS_SW_ON=1,
    BYPASS_SW_UNDEF=2,
}BypassSwitch_t;

/*see Side Tone Attenuation*/
typedef enum {
    SIDE_TONE_ATTEN_MIN_6_DB=0,
    SIDE_TONE_ATTEN_MIN_9_DB=1,
    SIDE_TONE_ATTEN_MIN_12_DB=2,
    SIDE_TONE_ATTEN_MIN_15_DB=3,

    SIDE_TONE_ATTEN_UNDEF=4,
}SideToneAttenuation_t;

typedef enum {
    USB_BASE_OVER_SAMPLE_RATE_250FS=0,
    USB_BASE_OVER_SAMPLE_RATE_272FS=1,
    USB_BASE_OVER_SAMPLE_RATE_UNDEF=2,
}UsbBaseOverSampRate_t;

typedef enum {
    NORM_BASE_OVER_SAMPLE_RATE_256FS=0,
    NORM_BASE_OVER_SAMPLE_RATE_384FS=1,
    NORM_BASE_OVER_SAMPLE_RATE_UNDEF=2,
}NormalBaseOverSampRate_t;

typedef enum {
    WM_NORM_SAMPLE_RATE_8000_HZ=3,
    WM_NORM_SAMPLE_RATE_32000_HZ=6,
    WM_NORM_SAMPLE_RATE_48000_HZ=0,
    WM_NORM_SAMPLE_RATE_96000_HZ=7,
    WM_NORM_SAMPLE_RATE_UNDEF=200,
}NormSampRate_t;

/*Table 21 USB Mode Sample Rate Look-up Table*/
typedef enum {
    WM_USB_SAMPLE_RATE_8000_HZ=3,
    WM_USB_SAMPLE_RATE_48000_HZ=0,
    WM_USB_SAMPLE_RATE_32000_HZ=6,
    WM_USB_SAMPLE_RATE_96000_HZ=7,
    WM_USB_SAMPLE_RATE_88200_HZ=15,
    WM_USB_SAMPLE_RATE_UNDEF=200,
}UsbSampRate_t;

#endif /* WM8731_CONST_H */
