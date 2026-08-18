#ifndef MAX9860_CONST_H
#define MAX9860_CONST_H

#include "time_mcal.h"

#define MAX9860_REG_CNT 18
#define MAX9860_7BIT_ADDRESS 0x10
#define REG_SET_TRY_CNT 1
#define MAX9860_REVISION_CODE 0x40
#define MAX9860_VERIFY_DURATION_MS 1000
#define MAX9860_VERIFY_AMP 1000

#define MAX9860_PERIOD_US SEC_2_USEC(4)

#ifdef HAS_MAX9860_DAC
#include "max9860_dac_const.h"
#endif

#ifdef HAS_MAX9860_ADC
#include "max9860_adc_const.h"
#endif

typedef enum {
    /*Clip Detect Flag. Indicates that a signal has become clipped in the ADC or DAC digital signal paths. CLD also
indicates that the AGC function, when enabled, has set the microphone PGA to 0dB and no further gain reduction
is possible.*/
    CLIP_DETECT_FLAG_ON = 1,
    CLIP_DETECT_FLAG_OFF = 0,

    CLIP_DETECT_FLAG_UNDEF = 2,
} ClipDetectFlag_t;

typedef enum {
    /*Slew Level Detect Flag. When volume or gain changes are made, the slewing circuitry smoothly steps through all
intermediate settings. When SLD is set high, all slewing has completed and the volume or gain is at its final value.*/
    SLD_FLAG_ON = 1,
    SLD_OFF = 0,

    SLD_UNDEF = 2,
} SlewLevelDetectFlag_t;

typedef enum {
    /*Digital PLL Unlock Flag. Indicates that the digital audio PLL for the ADC or DAC has become unlocked and digital
signal data is not reliable. When beginning operation in master mode, this flag goes high and can be cleared by
reading the status register.*/
    ULK_ON = 1,
    ULK_OFF = 0,

    ULK_UNDEF = 2,
} DigitalPLLUnlockFlag_t;

typedef enum {
    CONV_ADC = 1,
    CONV_DAC = 2,

    CONV_UNDEF = 0,
} Converter_t;

typedef enum {
    /* LRCLK Invert */
    WCI_LEFT_CH_LRCLK_LOW = 0,
    WCI_RIGHT_CH_LRCLK_LOW = 1,

    WCI_UNDEF = 2,
} WCI_t;

typedef enum {
    TDM_LRCLK_LEFT_AND_RIGHT = 0, // LRCLK signal polarity indicates left and right audio.

    TDM_LRCLK_LEFT_OR_RIGHT = 1, // LRCLK is a framing pulse which transitions polarity to indicate the start of a frame
                                 // of audio data consisting of multiple channels.

    TDM_UNDEF = 2,
} TDM_t;

/*(page 32) Power Management Register Table 11.*/
typedef enum {
    /* Active-Low Software Shutdown */
    SW_SHDN_FULL_SHUTDOWN = 0, /*MAX9860 is in full shutdown.*/
    SW_SHDN_NORMAL_WORK = 1,   /*MAX9860 is powered on.*/

    SW_SHDN_UNDEF = 0x6,
} SoftwareShutdown_t;

typedef enum {
    DIG_FILT_DISABLED = 0x0,          /**/
    DIG_FILT_ELLIPTICAL_8KHZ = 0x3,   /*Elliptical 8kHz*/
    DIG_FILT_ELLIPTICAL_16KHZ = 0x1,  /*Elliptical 16kHz*/
    DIG_FILT_BUTTERWORTH_8KHZ = 0x4,  /*Butterworth 8kHz*/
    DIG_FILT_BUTTERWORTH_16KHZ = 0x2, /*Butterworth 16kHz*/
    DIG_FILT_BUTTERWORTH_48KHZ = 0x5, /*Butterworth 48kHz*/

    DIG_FILT_UNDEF = 0x6,
} DigitalFilter_t;

typedef enum {
    /*MCLK Prescaler. Divides MCLK down to generate a PCLK between 10MHz and 20MHz. */
    PSCLK_DISABLE = 0,
    PSCLK_MCLK_10MHZ_20MHZ = 1,
    PSCLK_MCLK_20MHZ_40MHZ = 2,
    PSCLK_MCLK_40MHZ_PLUS = 3,

    PSCLK__UNDEF = 0x4,
} PrescalerClk_t;

typedef enum {
    /* Integer Clock Mode. Enables exact integer mode for three predefined PCLK frequencies. Exact integer mode is
    normally intended for master mode, but can be enabled in slave mode if the externally supplied LRCLK exactly */
    FREQ_NORMAL_OP = 0,    // Normal operation (configure clocking with the PLL, NHI, and NLO bits).
    FREQ_PCLK_12MHz = 1,   // Select when PCLK is 12MHz (LRCLK = PCLK/1500 or PCLK/750).
    FREQ_PCLK_13MHz = 2,   // Select when PCLK is 13MHz (LRCLK = PCLK/1625 or PCLK/812.5).
    FREQ_PCLK_19_2MHz = 3, // Select when PCLK is 19.2MHz (LRCLK = PCLK/2400 or PCLK/1200).

    PSCLK_UNDEF = 0x4,
} IntegerClkMode_t;

typedef enum {
    MAX9860_REG_INTERRUPT_STATUS = 0x00,
    MAX9860_REG_MICROPHONE_NG_AGC_READBACK = 0x01,
    MAX9860_REG_INTERRUPT_ENABLE = 0x02,
    MAX9860_REG_SYSTEM_CLOCK = 0x03,
    MAX9860_REG_STEREO_AUDIO_CLOCK_CONTROL_HIGH = 0x04,
    MAX9860_REG_STEREO_AUDIO_CLOCK_CONTROL_LOW = 0x05,
    MAX9860_REG_INTERFACE1 = 0x06,
    MAX9860_REG_INTERFACE2 = 0x07,
    MAX9860_REG_VOICE_FILTER = 0x08,
    MAX9860_REG_DAC_ATTENUATION = 0x09,
    MAX9860_REG_ADC_OUTPUT_LEVELS = 0x0A,
    MAX9860_REG_DAC_GAIN_AND_SIDETONE = 0x0B,
    MAX9860_REG_MICROPHONE_GAIN = 0x0C,
    MAX9860_REG_RESERVED = 0x0D,
    MAX9860_REG_MICROPHONE_AGC = 0x0E,
    MAX9860_REG_NOISE_GATEMICROPHONE_AGC = 0x0F,
    MAX9860_REG_SYSTEM_SHUTDOWN = 0x10,
    MAX9860_REG_REVISION_CODE = 0xFF, /*Table 12. Revision Code Register*/

    MAX9860_REG_UNDEF = 0x22,
} Max9860RegAddr_t;

/*Stereo Enable*/
typedef enum {
    ST_MONO_ENABLE = 0,
    ST_STEREO_ENABLE = 1,

    ST_UNDEF = 2,
} Stereo_t;

/*(page 20) BCLK Select
 * Configures BCLK when operating in master mode.
 * BSEL has no effect in slave mode. Set BSEL = 010,
 * unless sharing the bus with multiple devices.
 */

typedef enum {
    /* BCLK Select. Configures BCLK when operating in master mode.
    BSEL has no effect in slave mode. Set BSEL = 010,
    unless sharing the bus with multiple devices.  */
    BSEL_OFF = 0,        /**/
    BSEL_64X_LRCLK = 1,  /*64x LRCLK (192x internal clock divided by 3)*/
    BSEL_48X_LRCLK = 2,  /*48x LRCLK (192x internal clock divided by 4)*/
    BSEL_RES = 3,        /*Reserved for future use.*/
    BSEL_PCLK_DIV2 = 4,  /*PCLK/2*/
    BSEL_PCLK_DIV4 = 5,  /*PCLK/4*/
    BSEL_PCLK_DIV8 = 6,  /*PCLK/8*/
    BSEL_PCLK_DIV16 = 7, /*PCLK/16*/

    BSEL_UNDEF = 8,
} BitClockSelect_t;

typedef enum {
    /* 16kHz Mode */
    LRCK_IS_8KHZ = 0,  /*LRCLK is exactly 8kHz*/
    LRCK_IS_16KHZ = 1, /*LRCLK is exactly 16kHz*/

    LRCK_UNDEF = 2,
} LrClk16kHzMode_t;

typedef enum {
    /* PLL Enable  */
    PLL_LRCLK = 0,      /* (Valid for slave and master mode)—The frequency of LRCLK is set by the NHI and NLO
                           divider bits. Set PLL = 0 in slave mode only if the externally generated LRCLK can be
                           exactly selected using the LRCLK divider */
    PLL_SLAVE_ONLY = 1, /* (Valid for slave mode only)—Used when the audio master generates an LRCLK not
                        selectable using the LRCLK divider. A digital PLL locks on to the externally supplied
                        LRCLK signal regardless of the MCLK frequency. */

    PLLK_UNDEF = 0x2,
} PllEnable_t;

typedef enum {
    MAX_IF_I2S = 1,
    MAX_IF_TDM = 2,

    MAX_IF_UNDEF = 0,
} Max9860interface_t;

typedef enum {
    MAX9860_I2S_ROLE_SLAVE = 0,
    MAX9860_I2S_ROLE_MASTER = 1,

    MAX9860_I2SMODE_UNDEF = 0,
} Max9860I2sRole_t;

typedef enum {
    SHDN_ON = 0,  /*MAX9860 is in full shutdown*/
    SHDN_OFF = 1, /*MAX9860 is powered on*/

    SHDN_UNDEF = 2,
} SwShutDown_t;

#endif /* MAX9860_CONST_H */
