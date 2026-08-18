#ifndef NAU8814_CONST_H
#define NAU8814_CONST_H

#include "time_mcal.h"
#include "nau8814_dep.h"


#define SILICON_REVISION_CODE 0x00EE
#define NAU8814_REG_CNT 55
#define NAU8814_7BIT_ADDRESS 0x1A

#define REG_SET_TRY_CNT 1
#define NAU8814_VERIFY_DURATION_MS 1000
#define NAU8814_VERIFY_AMP 1000

#define NAU8814_PERIOD_US SEC_2_USEC(4)

#define TWO_POW_24 (16777216)

#ifdef HAS_NAU8814_DAC
#include "nau8814_dac_const.h"
#endif

#ifdef HAS_NAU8814_ADC
#include "nau8814_adc_const.h"
#endif
//13. REGISTER DESCRIPTION
typedef enum {
    NAU8814_REG_SOFTWARE_RESET = 0x00, /*Software Reset*/
    NAU8814_REG_POWER_MANAGEMENT_1 = 0x01, /*Power Management 1*/
    NAU8814_REG_POWER_MANAGEMENT_2 = 0x02, /*Power Management 2*/
    NAU8814_REG_POWER_MANAGEMENT_3 = 0x03, /*Power Management 3*/
    NAU8814_REG_AUDIO_INTERFACE = 0x04, /*Audio Interface*/
    NAU8814_REG_COMPANDING = 0x05, /*Companding*/
    NAU8814_REG_CLOCK_CONTROL_1 = 0x06, /*Clock Control 1*/
    NAU8814_REG_CLOCK_CONTROL_2 = 0x07, /*Clock Control 2*/
    NAU8814_REG_GPIO_CTRL = 0x08, /*GPIO CTRL*/
    NAU8814_REG_DAC_CTRL = 0x0A, /*DAC CTRL*/
    NAU8814_REG_DAC_VOLUME = 0x0B, /*DAC Volume*/
    NAU8814_REG_ADC_CTRL = 0x0E, /*ADC CTRL*/
    NAU8814_REG_ADC_VOLUME = 0x0F, /*ADC Volume*/
    NAU8814_REG_EQ1_LOW_CUTOFF = 0x12, /*EQ1-Low Cutoff*/
    NAU8814_REG_EQ2_PEAK_1 = 0x13, /*EQ2-Peak 1*/
    NAU8814_REG_EQ3_PEAK_2 = 0x14, /*EQ3-Peak 2*/
    NAU8814_REG_EQ4_PEAK_3 = 0x15, /*EQ4-Peak3*/
    NAU8814_REG_EQ5_HIGH_CUTOFF = 0x16, /*EQ5-High Cutoff*/
    NAU8814_REG_DAC_LIMITER_1 = 0x18, /*DAC Limiter 1*/
    NAU8814_REG_DAC_LIMITER_2 = 0x19, /*DAC Limiter 2*/
    NAU8814_REG_NOTCH_FILTER_0_HIGH = 0x1B, /*Notch Filter High*/
    NAU8814_REG_NOTCH_FILTER_0_LOW = 0x1C, /*Notch Filter Low*/
    NAU8814_REG_NOTCH_FILTER_1_HIGH = 0x1D, /*Notch Filter High*/
    NAU8814_REG_NOTCH_FILTER_1_LOW = 0x1E, /*Notch Filter Low*/
    NAU8814_REG_ALC_CTRL_1 = 0x20, /*ALC CTRL 1*/
    NAU8814_REG_ALC_CTRL_2 = 0x21, /*ALC CTRL 2*/
    NAU8814_REG_ALC_CTRL_3 = 0x22, /*ALC CTRL 3*/
    NAU8814_REG_NOISE_GATE = 0x23, /*Noise Gate*/
    NAU8814_REG_PLL_N_CTRL = 0x24, /*PLL N CTRL*/
    NAU8814_REG_PLL_K_1 = 0x25, /*PLL K 1*/
    NAU8814_REG_PLL_K_2 = 0x26, /*PLL K 2*/
    NAU8814_REG_PLL_K_3 = 0x27, /*PLL K 3*/
    NAU8814_REG_ATTENUATION_CTRL = 0x28, /*Attenuation CTRL*/
    NAU8814_REG_INPUT_CTRL = 0x2C, /*Input CTRL*/
    NAU8814_REG_PGA_GAIN = 0x2D, /*PGA Gain*/
    NAU8814_REG_ADC_BOOST = 0x2F, /*ADC Boost*/
    NAU8814_REG_OUTPUT_CTRL = 0x31, /*Output CTRL*/
    NAU8814_REG_SPEAKER_MIXER_CTRL = 0x32, /*Speaker Mixer CTRL*/
    NAU8814_REG_SPKOUT_VOLUME = 0x36, /*SPKOUT Volume*/
    NAU8814_REG_MONO_MIXER_CONTROL = 0x38, /*MONO Mixer Control*/
    NAU8814_REG_POWER_MANAGEMENT_4 = 0x3A, /*Power Management 4*/
    NAU8814_REG_TIME_SLOT = 0x3B, /*Time Slot*/
    NAU8814_REG_ADCOUT_DRIVE = 0x3C, /*ADCOUT Drive*/
    NAU8814_REG_SILICON_REVISION = 0x3E, /*Silicon Revision 0011_1110*/
    NAU8814_REG_2_WIRE_ID = 0x3F, /*2-Wire ID*/
    NAU8814_REG_ADDITIONAL_ID = 0x40, /*Additional ID*/
    NAU8814_REG_RESERVED = 0x41, /*Reserved*/
    NAU8814_REG_HIGH_VOLTAGE_CTRL = 0x45, /*High Voltage CTRL*/
    NAU8814_REG_ALC_ENHANCEMENTS_1 = 0x46, /*ALC Enhancements 1*/
    NAU8814_REG_ALC_ENHANCEMENTS_2 = 0x47, /*ALC Enhancements 2*/
    NAU8814_REG_ADDITIONAL_IF_CTRL = 0x49, /*Additional IF CTRL*/
    NAU8814_REG_POWER_TIE_OFF_CTRL = 0x4B, /*Power/Tie-off CTRL*/
    NAU8814_REG_AGC_P2P_DETECTOR = 0x4C, /*AGC P2P Detector*/
    NAU8814_REG_AGC_PEAK_DETECTOR = 0x4D, /*AGC Peak Detector*/
    NAU8814_REG_CONTROL_AND_STATUS = 0x4E, /*Control and Status*/
    NAU8814_REG_OUTPUT_TIE_OFF_CTRL = 0x4F, /*Output tie-off CTRL*/

    NAU8814_REG_UNDEF = 0xFF,
} Nau8814RegAddr_t;

/* MIC+ pin to the input Boost Stage (NB, when using this path set PMICPGA=0):
 * Auxiliary to Input Boost Stage
 * */
typedef enum {
    BOOST_GAIN_CODE_DISCONNECTED = 0,
    BOOST_GAIN_CODE_M12 = 1,
    BOOST_GAIN_CODE_M9 = 2,
    BOOST_GAIN_CODE_M6 = 3,
    BOOST_GAIN_CODE_M3 = 4,
    BOOST_GAIN_CODE_0 = 5,
    BOOST_GAIN_CODE_3 = 6,
    BOOST_GAIN_CODE_6 = 7,
}BoostGainCode_t;

//Audio Data Format Select AIFMT
typedef enum {
     NAU_AUDIO_DATA_FORMAT_RIGHT_JUSTIFIED = 0,
     NAU_AUDIO_DATA_FORMAT_LEFT_JUSTIFIED = 1,
     NAU_AUDIO_DATA_FORMAT_I2S = 2,
     NAU_AUDIO_DATA_FORMAT_PCM_A = 3,

     NAU_AUDIO_DATA_FORMAT_UNDEF = 4,
}AudioDataFormat_t;

//Data phases of FRAME clock DACPHS ADCPHS
typedef enum {
    DATA_CH_LEFT = 0,
    DATA_CH_RIGHT = 1,

    DATA_CH_UNDEF = 4,
}DataFramePhase_t;

//Clock Polarity BCLKP FSP
typedef enum {
    CLOCK_POLARITY_NORMAL = 0,
    CLOCK_POLARITY_INVERTED = 1,

    CLOCK_POLARITY_UNDEF = 2,
}ClockPolarity_t;


//Word Length Selection WLEN
typedef enum {
    NAU_WORD_LENGTH_16_BIT = 0,
    NAU_WORD_LENGTH_20_BIT = 1,
    NAU_WORD_LENGTH_24_BIT = 2,
    NAU_WORD_LENGTH_32_BIT = 3,
    NAU_WORD_LENGTH_UNDEF=4,
}NAU8814WordLength_t;

//13.3.3. Clock Control Register
typedef enum {
    CLKIOEN_SLAVE_MODE = 0, //
    CLKIOEN_MASTER_MODE = 1, //

    CLKIOEN_UNDEF=2
}NauClkIoEn_t;


//General Purpose I/O Selection
typedef enum {
    GPIO_SEL_CSB_INPUT= 0,    /*CSb Input*/
    GPIO_SEL_JACK_INSERT_DETECT= 1, /*Jack Insert Detect*/
    GPIO_SEL_TEMPERATURE_OK= 2, /*Temperature OK*/
    GPIO_SEL_AMUTE_ACTIVE= 3, /*AMUTE Active */
    GPIO_SEL_PLL_CLK_OUTPUT= 4, /*PLL CLK Output  (PLL Frequency Output)*/
    GPIO_SEL_PLL_LOCK= 5, /*PLL Lock (0- Locked, 1 – Not Locked)*/
    GPIO_SEL_1= 6, /*Set HIGH*/
    GPIO_SEL_0= 7, /*Set LOW*/

    GPIO_SEL_UNDEF= 4,
}NauGpioSel_t;


//PLL Output Clock Divider
typedef enum {
    GPIO_PLL_DIV1= 0,
    GPIO_PLL_DIV2= 1,
    GPIO_PLL_DIV3= 2,
    GPIO_PLL_DIV4= 3,

    GPIO_PLL_DIV_UNDEF= 4,
}NauGpioPll_t;

//reg 0x06 CLKM, bit 8
typedef enum {
    CLKM_MCLK = 0, //0 MCLK (PLL Bypassed)
    CLKM_PLL = 1, //1 MCLK (PLL Output)

    CLKM_UNDEF=2
}NauClkm_t;

//MCLKSEL Master Clock Selection
typedef enum {
    MCLKSEL_DIV1 = 0,
    MCLKSEL_DIV1_5 = 1,
    MCLKSEL_DIV2 = 2,
    MCLKSEL_DIV3 = 3,
    MCLKSEL_DIV4 = 4,
    MCLKSEL_DIV6= 5,
    MCLKSEL_DIV8 = 6,
    MCLKSEL_DIV12 = 7,

    MCLKSEL_UNDEF=2
}NauMclkSel_t;


//reg 0x24 PLLMCLK bit4
typedef enum {
    PLLMCLK_MCLK_DIV1 = 0, /*MCLK not divided*/
    PLLMCLK_MCLK_DIV2 = 1,  /*Divide MCLK by 2 before input PLL*/

    PLLMCLK_UNDEF=2
}NauPllMclk_t;


//reg 0x24 PLLN bit[3:0] PLL Integer Frequency Ratio
typedef enum {
    PLLN_NOT_VALID_0=0,
    PLLN_NOT_VALID_1=1,
    PLLN_NOT_VALID_2=2,
    PLLN_NOT_VALID_3=3,
    PLLN_NOT_VALID_4=4,
    PLLN_5 = 5,  /**/
    PLLN_6 = 6,  /**/
    PLLN_7 = 7,  /**/
    PLLN_8 = 8,  /**/
    PLLN_9 = 9,  /**/
    PLLN_10 = 10,  /**/
    PLLN_11= 11,  /**/
    PLLN_12 = 12,  /**/
    PLLN_13 = 13,  /**/
    PLLN_NOT_VALID_14=14,
    PLLN_NOT_VALID_15=15,

    PLLN_UNDEF=16
}NauPllN_t;


typedef enum {
    CTRL_OFF = 0,
    CTRL_ON = 1,

    CTRL_UNDEF = 2,
}NauCtrl_t;

/*   */
typedef enum {
    NAU_MUTE_OFF = 0,
    NAU_MUTE_ON = 1,

    NAU_MUTE_UNDEF = 2,
}NauMute_t;

#endif /* NAU8814_CONST_H */
