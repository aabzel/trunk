//**************************************************************************************************
// @Module  NAU8814 ASIC Driver
//! \file   nau8814_constants.h
//! \brief  Interface of the NAU8814 ASIC module.
//!             nau8814 constants
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef NAU8814_CONSTANTS_H
#define NAU8814_CONSTANTS_H


//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#include "nau8814_dependencies.h"


//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

// None.



//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

//! NAU8814 SILICON REVISION CODE
#define NAU8814_SILICON_REVISION_CODE 0x00EE

//! NAU8814 REGISTER CNT
#define NAU8814_REGISTER_CNT 55

//! NAU8814 FRAME SIZE
#define NAU8814_FRAME_SIZE 2

//! NAU8814 7BIT I2C ADDRESS
#define NAU8814_7BIT_ADDRESS 0x1A

//! NAU8814 REG SET TRY CNT
#define NAU8814_REG_SET_TRY_CNT 1

//! NAU8814 VERIFY DURATION MS
#define NAU8814_VERIFY_DURATION_MS 1000

//! NAU8814 VERIFY AMP
#define NAU8814_VERIFY_AMP 1000

//! NAU8814 POLL PERIOD US
#define NAU8814_POLL_PERIOD_US 4000000

//! NAU8814 MAX PCM   2^24 = 16777216
#define NAU8814_MAX_PCM (16777216)

//! NAU8814 register storage access
typedef enum
{
    NAU8814_ACCESS_READ_ONLY = 1,
    NAU8814_ACCESS_READ_WRITE = 2,

    NAU8814_ACCESS_UNDEF = 0,
} NAU8814_STORAGE_ACCESS;

//! NAU8814 state
typedef enum
{
    NAU8814_STATE_IDLE = 0,
    NAU8814_STATE_PLAY = 1,
    NAU8814_STATE_RECORD = 2,
    NAU8814_STATE_PLAY_AND_RECORD = 3,
} NAU8814_STATE;

//! for NAU8814 I2S BUS ROLE
typedef enum
{
    NAU8814_BUS_ROLE_MASTER = 1,
    NAU8814_BUS_ROLE_SLAVE = 2,

    NAU8814_BUS_ROLE_UNDEF = 0,
} NAU8814_I2S_BUS_ROLE;

//! All possible I2S register addresses
typedef enum
{
    NAU8814_REGIS_SOFTWARE_RESET = 0x00,      // Software Reset
    NAU8814_REGIS_POWER_MANAGEMENT_1 = 0x01,  // Power Management 1
    NAU8814_REGIS_POWER_MANAGEMENT_2 = 0x02,  // Power Management 2
    NAU8814_REGIS_POWER_MANAGEMENT_3 = 0x03,  // Power Management 3
    NAU8814_REGIS_AUDIO_INTERFACE = 0x04,     // Audio Interface
    NAU8814_REGIS_COMPANDING = 0x05,          // Companding
    NAU8814_REGIS_CLOCK_CONTROL_1 = 0x06,     // Clock Control 1
    NAU8814_REGIS_CLOCK_CONTROL_2 = 0x07,     // Clock Control 2
    NAU8814_REGIS_GPIO_CTRL = 0x08,           // GPIO CTRL
    NAU8814_REGIS_DAC_CTRL = 0x0A,            // DAC CTRL
    NAU8814_REGIS_DAC_VOLUME = 0x0B,          // DAC Volume
    NAU8814_REGIS_ADC_CTRL = 0x0E,            // ADC CTRL
    NAU8814_REGIS_ADC_VOLUME = 0x0F,          // ADC Volume
    NAU8814_REGIS_EQ1_LOW_CUTOFF = 0x12,      // EQ1-Low Cutoff
    NAU8814_REGIS_EQ2_PEAK_1 = 0x13,          // EQ2-Peak 1
    NAU8814_REGIS_EQ3_PEAK_2 = 0x14,          // EQ3-Peak 2
    NAU8814_REGIS_EQ4_PEAK_3 = 0x15,          // EQ4-Peak3
    NAU8814_REGIS_EQ5_HIGH_CUTOFF = 0x16,     // EQ5-High Cutoff
    NAU8814_REGIS_DAC_LIMITER_1 = 0x18,       // DAC Limiter 1
    NAU8814_REGIS_DAC_LIMITER_2 = 0x19,       // DAC Limiter 2
    NAU8814_REGIS_NOTCH_FILTER_0_HIGH = 0x1B, // Notch Filter High
    NAU8814_REGIS_NOTCH_FILTER_0_LOW = 0x1C,  // Notch Filter Low
    NAU8814_REGIS_NOTCH_FILTER_1_HIGH = 0x1D, // Notch Filter High
    NAU8814_REGIS_NOTCH_FILTER_1_LOW = 0x1E,  // Notch Filter Low
    NAU8814_REGIS_ALC_CTRL_1 = 0x20,          // ALC CTRL 1
    NAU8814_REGIS_ALC_CTRL_2 = 0x21,          // ALC CTRL 2
    NAU8814_REGIS_ALC_CTRL_3 = 0x22,          // ALC CTRL 3
    NAU8814_REGIS_NOISE_GATE = 0x23,          // Noise Gate
    NAU8814_REGIS_PLL_N_CTRL = 0x24,          // PLL N CTRL
    NAU8814_REGIS_PLL_K_1 = 0x25,             // PLL K 1
    NAU8814_REGIS_PLL_K_2 = 0x26,             // PLL K 2
    NAU8814_REGIS_PLL_K_3 = 0x27,             // PLL K 3
    NAU8814_REGIS_ATTENUATION_CTRL = 0x28,    // Attenuation CTRL
    NAU8814_REGIS_INPUT_CTRL = 0x2C,          // Input CTRL
    NAU8814_REGIS_PGA_GAIN = 0x2D,            // PGA Gain
    NAU8814_REGIS_ADC_BOOST = 0x2F,           // ADC Boost
    NAU8814_REGIS_OUTPUT_CTRL = 0x31,         // Output CTRL
    NAU8814_REGIS_SPEAKER_MIXER_CTRL = 0x32,  // Speaker Mixer CTRL
    NAU8814_REGIS_SPKOUT_VOLUME = 0x36,       // SPKOUT Volume
    NAU8814_REGIS_MONO_MIXER_CONTROL = 0x38,  // MONO Mixer Control
    NAU8814_REGIS_POWER_MANAGEMENT_4 = 0x3A,  // Power Management 4
    NAU8814_REGIS_TIME_SLOT = 0x3B,           // Time Slot
    NAU8814_REGIS_ADCOUT_DRIVE = 0x3C,        // ADCOUT Drive
    NAU8814_REGIS_SILICON_REVISION = 0x3E,    // Silicon Revision 0011_1110
    NAU8814_REGIS_2_WIRE_ID = 0x3F,           // 2-Wire ID
    NAU8814_REGIS_ADDITIONAL_ID = 0x40,       // Additional ID
    NAU8814_REGIS_RESERVED = 0x41,            // Reserved
    NAU8814_REGIS_HIGH_VOLTAGE_CTRL = 0x45,   // High Voltage CTRL
    NAU8814_REGIS_ALC_ENHANCEMENTS_1 = 0x46,  // ALC Enhancements 1
    NAU8814_REGIS_ALC_ENHANCEMENTS_2 = 0x47,  // ALC Enhancements 2
    NAU8814_REGIS_ADDITIONAL_IF_CTRL = 0x49,  // Additional IF CTRL
    NAU8814_REGIS_POWER_TIE_OFF_CTRL = 0x4B,  // Power/Tie-off CTRL
    NAU8814_REGIS_AGC_P2P_DETECTOR = 0x4C,    // AGC P2P Detector
    NAU8814_REGIS_AGC_PEAK_DETECTOR = 0x4D,   // AGC Peak Detector
    NAU8814_REGIS_CONTROL_AND_STATUS = 0x4E,  // Control and Status
    NAU8814_REGIS_OUTPUT_TIE_OFF_CTRL = 0x4F, // Output tie-off CTRL

    NAU8814_REGIS_UNDEF = 0xFF,
} NAU8814_REGISTER_ADDR;

//! MIC+ pin to the input Boost Stage. Auxiliary to Input Boost Stage
typedef enum
{
    NAU8814_BOOST_GAIN_CODE_DISCONNECTED = 0,
    NAU8814_BOOST_GAIN_CODE_M12 = 1,
    NAU8814_BOOST_GAIN_CODE_M9 = 2,
    NAU8814_BOOST_GAIN_CODE_M6 = 3,
    NAU8814_BOOST_GAIN_CODE_M3 = 4,
    NAU8814_BOOST_GAIN_CODE_0 = 5,
    NAU8814_BOOST_GAIN_CODE_3 = 6,
    NAU8814_BOOST_GAIN_CODE_6 = 7,
} NAU8814_BOOST_GAIN_CODE;

//! Audio Data Format Select AIFMT
typedef enum
{
    NAU8814_AUDIO_DATA_FORMAT_RIGHT_JUSTIFIED = 0,
    NAU8814_AUDIO_DATA_FORMAT_LEFT_JUSTIFIED = 1,
    NAU8814_AUDIO_DATA_FORMAT_I2S = 2,
    NAU8814_AUDIO_DATA_FORMAT_PCM_A = 3,

    NAU8814_AUDIO_DATA_FORMAT_UNDEF = 4,
} NAU8814_AUDIO_DATA_FORMAT;

//! Data phases of FRAME clock DACPHS ADCPHS
typedef enum
{
    NAU8814_DATA_CH_LEFT = 0,
    NAU8814_DATA_CH_RIGHT = 1,

    NAU8814_DATA_CH_UNDEF = 4,
} NAU8814_DATA_FRAME_PHASE;

//! Clock Polarity BCLKP FSP
typedef enum
{
    NAU8814_CLOCK_POLARITY_NORMAL = 0,
    NAU8814_CLOCK_POLARITY_INVERTED = 1,

    NAU8814_CLOCK_POLARITY_UNDEF = 2,
} NAU8814_CLOCK_POLARITY;

//! Word Length Selection WLEN
typedef enum
{
    NAU8814_WORD_LENGTH_16_BIT = 0,
    NAU8814_WORD_LENGTH_20_BIT = 1,
    NAU8814_WORD_LENGTH_24_BIT = 2,
    NAU8814_WORD_LENGTH_32_BIT = 3,

    NAU8814_WORD_LENGTH_UNDEF = 4,
} NAU8814_WORD_LENGTH;

//! Clock Control Register
typedef enum
{
    NAU8814_CLKIOEN_SLAVE_MODE = 0,
    NAU8814_CLKIOEN_MASTER_MODE = 1,

    NAU8814_CLKIOEN_UNDEF = 2
} NAU8814_CLK_IO_EN;


//! General Purpose I/O Selection
typedef enum
{
    // CSb Input
    NAU8814_GPIO_SEL_CSB_INPUT = 0,
    // Jack Insert Detect
    NAU8814_GPIO_SEL_JACK_INSERT_DETECT = 1,
    // Temperature OK
    NAU8814_GPIO_SEL_TEMPERATURE_OK = 2,
    // AMUTE Active
    NAU8814_GPIO_SEL_AMUTE_ACTIVE = 3,
    //PLL CLK Output  (PLL Frequency Output)
    NAU8814_GPIO_SEL_PLL_CLK_OUTPUT = 4,
    NAU8814_GPIO_SEL_PLL_LOCK = 5,
    // PLL Lock (0- Locked, 1 – Not Locked)
    NAU8814_GPIO_SEL_1 = 6,
    // Set HIGH
    NAU8814_GPIO_SEL_0 = 7,
    // Set LOW

    NAU8814_GPIO_SEL_UNDEF = 4,
} NAU8814_GPIO_SEL;


//! PLL Output Clock Divider
typedef enum
{
    NAU8814_GPIO_PLL_DIV1 = 0,
    NAU8814_GPIO_PLL_DIV2 = 1,
    NAU8814_GPIO_PLL_DIV3 = 2,
    NAU8814_GPIO_PLL_DIV4 = 3,

    NAU8814_GPIO_PLL_DIV_UNDEF = 4,
} NAU8814_GPIO_PLL;

//! Reg 0x06 CLKM bit 8
typedef enum
{
    // 0 MCLK (PLL Bypassed)
    NAU8814_CLKM_MCLK = 0,
    // 1 MCLK (PLL Output)
    NAU8814_CLKM_PLL = 1,

    NAU8814_CLKM_UNDEF = 2
} NAU8814_CLK_M;

//! MCLKSEL Master Clock Selection
typedef enum
{
    NAU8814_MCLKSEL_DIV1 = 0,
    NAU8814_MCLKSEL_DIV1_5 = 1,
    NAU8814_MCLKSEL_DIV2 = 2,
    NAU8814_MCLKSEL_DIV3 = 3,
    NAU8814_MCLKSEL_DIV4 = 4,
    NAU8814_MCLKSEL_DIV6 = 5,
    NAU8814_MCLKSEL_DIV8 = 6,
    NAU8814_MCLKSEL_DIV12 = 7,

    NAU8814_MCLKSEL_UNDEF = 2
} NAU8814_M_CLK_SEL;


//! Reg 0x24, PLLMCLK bit:4
typedef enum
{
    // MCLK not divided
    NAU8814_PLLMCLK_MCLK_DIV1 = 0,
    // Divide MCLK by 2 before input PLL
    NAU8814_PLLMCLK_MCLK_DIV2 = 1,

    NAU8814_PLLMCLK_UNDEF = 2
} NAU8814_PLL_MCLK;

//! Reg 0x24 PLLN bit[3:0] PLL Integer Frequency Ratio
typedef enum
{
    NAU8814_PLLN_NOT_VALID_0 = 0,
    NAU8814_PLLN_NOT_VALID_1 = 1,
    NAU8814_PLLN_NOT_VALID_2 = 2,
    NAU8814_PLLN_NOT_VALID_3 = 3,
    NAU8814_PLLN_NOT_VALID_4 = 4,
    NAU8814_PLLN_5 = 5,
    NAU8814_PLLN_6 = 6,
    NAU8814_PLLN_7 = 7,
    NAU8814_PLLN_8 = 8,
    NAU8814_PLLN_9 = 9,
    NAU8814_PLLN_10 = 10,
    NAU8814_PLLN_11 = 11,
    NAU8814_PLLN_12 = 12,
    NAU8814_PLLN_13 = 13,
    NAU8814_PLLN_NOT_VALID_14 = 14,
    NAU8814_PLLN_NOT_VALID_15 = 15,

    NAU8814_PLLN_UNDEF = 16
} NAU8814_PLL_N;

//! NAU8814 CTRL
typedef enum
{
    NAU8814_CTRL_OFF = 0,
    NAU8814_CTRL_ON = 1,

    NAU8814_CTRL_UNDEF = 2,
} NAU8814_CTRL;

//! NAU8814 MUTE
typedef enum
{
    NAU8814_MUTE_OFF = 0,
    NAU8814_MUTE_ON = 1,

    NAU8814_MUTE_UNDEF = 2,
} NAU8814_MUTE;

//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************

// None.



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

// None.



#endif // #ifndef NAU8814_CONSTANTS_H
//******************************* end of file ******************************************************
