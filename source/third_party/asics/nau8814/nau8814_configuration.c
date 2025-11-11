//*************************************************************************************************
// @Module  NAU8814 ASIC Driver
//! \file   nau8814_configuration.c
//! \par    Platform
//!             Any with nau8814 chip
//! \par    Compatible
//!             Any
//! \brief  That is a configuration node for multiple NAU8814 audio codecs
//!
//! \par    Abbreviations
//!             ASIC - Application-specific integrated circuit
//!             I2S - Inter-Integrated Circuit Sound
//!             I2C - Inter-Integrated Circuit
//!             PCB - Printed circuit board
//!             RAM - Random-access memory
//!             ROM - Read-only memory
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************


//**************************************************************************************************
//! \defgroup   NAU8814 Name of Module
//! \brief      nau8814 configuration structures
//! \addtogroup NAU8814
//! @{
//! \file nau8814_configuration.c
//! \file nau8814_configuration.h
//! @}
//**************************************************************************************************



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#include "nau8814_configuration.h"

#include "general_macros.h"
#include "nau8814_type.h"

//**************************************************************************************************
// Verification of the imported configuration parameters
//**************************************************************************************************


//**************************************************************************************************
// Definitions of global (public) variables
//**************************************************************************************************


//**************************************************************************************************
// Declarations of local (private) data types
//**************************************************************************************************


//**************************************************************************************************
// Definitions of local (private) constants
//**************************************************************************************************


//! Nau8814 Register Configuration
static const NAU8814_REGISTER_VAL Nau8814RegConfig[] = {
    {
        .addr = NAU8814_REGIS_POWER_MANAGEMENT_1,
        .Reg.PowerManagement1 =
            {
                .refimp = 1,
                .iobufen = 1,
                .abiasen = 1,
                .micbiasen = NAU8814_CTRL_ON,
                .pllen = NAU8814_CTRL_ON,
                .auxen = NAU8814_CTRL_OFF,

                .dcbufen = 1,
            },
    },
    {
        .addr = NAU8814_REGIS_POWER_MANAGEMENT_2,
        .Reg.PowerManagement2 =
            {
                .adcen = NAU8814_CTRL_ON,
                .pgaen = NAU8814_CTRL_ON,
                .bsten = NAU8814_CTRL_ON,
            },
    },

    {
        .addr = NAU8814_REGIS_POWER_MANAGEMENT_3,
        .Reg.PowerManagement3 =
            {
                .dacen = NAU8814_CTRL_ON,
                .spkmxen = NAU8814_CTRL_ON,
                .moutmxen = NAU8814_CTRL_ON,
                .pspken = NAU8814_CTRL_ON,
                .nspken = NAU8814_CTRL_ON,
                .mouten = NAU8814_CTRL_ON,
            },
    },

    {
        .addr = NAU8814_REGIS_AUDIO_INTERFACE,
        .Reg.AudioInterface =
            {
                .adcphs = NAU8814_DATA_CH_LEFT,
                .dacphs = NAU8814_DATA_CH_LEFT,
                .aifmt = NAU8814_AUDIO_DATA_FORMAT_I2S,
                .wlen = NAU8814_WORD_LENGTH_16_BIT,
                .fsp = NAU8814_CLOCK_POLARITY_NORMAL,
                .bclkp = NAU8814_CLOCK_POLARITY_NORMAL,
            },
    },

    {
        .addr = NAU8814_REGIS_COMPANDING,
        .Reg.Companding =
            {
                .addap = 0,
                .adccm = 0,
                .daccm = 0,
            },
    },

    {
        .addr = NAU8814_REGIS_CLOCK_CONTROL_1,
        .Reg.ClockControl1 =
            {
                .clkioen = NAU8814_CLKIOEN_SLAVE_MODE,
                .bclksel = 0, // Bit Clock Select
                .mclksel = NAU8814_MCLKSEL_DIV1,
                .clkm = NAU8814_CLKM_PLL,
            },
    },

    {
        .addr = NAU8814_REGIS_CLOCK_CONTROL_2,
        .Reg.ClockControl2 =
            {
                .sclken = 0,
                .smplr = 0,
            },
    },

    {
        .addr = NAU8814_REGIS_GPIO_CTRL,
        .Reg.GpioControl =
            {
                .gpiosel = NAU8814_GPIO_SEL_PLL_CLK_OUTPUT,
                .gpiopl = NAU8814_CLOCK_POLARITY_NORMAL,
                .gpiopll = NAU8814_GPIO_PLL_DIV4,
            },
    },

    {
        .addr = NAU8814_REGIS_DAC_CTRL,
        .Reg.DacControl =
            {
                .dacpl = 0,
                .automt = NAU8814_MUTE_OFF,
                .dacos = 0,
                .deemp = 0,
                .dacmt = NAU8814_MUTE_OFF,
            },
    },

    {
        .addr = NAU8814_REGIS_DAC_VOLUME,
        .Reg.DacVolume =
            {
                .dacgain = 0xff,
            },
    },

    {
        .addr = NAU8814_REGIS_INPUT_CTRL,
        .Reg.InputControl =
            {
                .auxm = 1,
                .nmicpga = 1,
                .pmicpga = 1,
                .auxpga = 0,
                .micbiasv = 0,
            },
    },

    {
        .addr = NAU8814_REGIS_ADC_CTRL,
        .Reg.AdcControl =
            {
                .adcpl = 0,
                .adcos = 0,
                .hpf = 0,
                .hpfam = 1,
                .hpfen = NAU8814_CTRL_ON,
            },
    },

    {
        .addr = NAU8814_REGIS_ADC_VOLUME,
        .Reg.AdcVolume =
            {
                .adcgain = 0xFF,
            },
    },

    {
        .addr = NAU8814_REGIS_DAC_LIMITER_1,
        .Reg.DacLimiter1 =
            {
                .daclimatk = 0,
                .daclimdcy = 0,
                .daclimen = 0,
            },
    },

    {
        .addr = NAU8814_REGIS_DAC_LIMITER_2,
        .Reg.DacLimiter2 =
            {
                .daclimbst = 0,
                .daclimthl = 7,
            },
    },

    {
        .addr = NAU8814_REGIS_ALC_CTRL_1,
        .Reg.AlcControl1 =
            {
                .alcmngain = 0,
                .alcmxgain = 3,
                .alcen = 0,
            },
    },

    {
        .addr = NAU8814_REGIS_ALC_CTRL_2,
        .Reg.AlcControl2 =
            {
                .alcsl = 0xB,
                .alcht = 0,
                .alczc = 0,
            },
    },

    {
        .addr = NAU8814_REGIS_ALC_CTRL_3,
        .Reg.AlcControl3 =
            {
                .alcatk = 0x2,
                .alcdcy = 3,
                .alcm = 0,
            },
    },

    {
        .addr = NAU8814_REGIS_NOISE_GATE,
        .Reg.NoiseGate =
            {
                .alcnth = 0,
                .alcnen = NAU8814_CTRL_ON,

            },
    },

    {
        .addr = NAU8814_REGIS_PLL_N_CTRL,
        .Reg.PllNControl =
            {
                .plln = NAU8814_PLLN_8,
                .pllmclk = NAU8814_PLLMCLK_MCLK_DIV1,
            },
    },

    {
        .addr = NAU8814_REGIS_ATTENUATION_CTRL,
        .Reg.AttenuationControl =
            {
                .spkatt = 0,
                .moutatt = 0,
            },
    },

    {
        .addr = NAU8814_REGIS_PGA_GAIN,
        .Reg.PgaGain =
            {
                .pgagain = 0x10,
                .pgamt = NAU8814_MUTE_OFF,
                .pgazc = 0,
            },
    },

    {
        .addr = NAU8814_REGIS_ADC_BOOST,
        .Reg.AdcBoost =
            {
                .auxbstgain = 0,
                .pmicbstgain = 0,
                .pgabst = 1,
            },
    },

    {
        .addr = NAU8814_REGIS_OUTPUT_CTRL,
        .Reg.OutputControl =
            {
                .aoutimp = 0,
                .tsen = NAU8814_CTRL_ON,
                .spkbst = 0,
                .moutbst = 1,
            },
    },

    {
        .addr = NAU8814_REGIS_SPEAKER_MIXER_CTRL,
        .Reg.SpeakerMixerControl =
            {
                .dacspk = NAU8814_CTRL_ON,
                .bypspk = 0,
                .auxspk = 0,
            },
    },
    {
        .addr = NAU8814_REGIS_SPKOUT_VOLUME,
        .Reg.SpkOutVolume =
            {
                .spkgain = 0x39,
                .spkmt = NAU8814_MUTE_OFF,
                .spkzc = 0,
            },
    },

    {
        .addr = NAU8814_REGIS_MONO_MIXER_CONTROL,
        .Reg.MonoMixerControl =
            {
                .dacmout = 1, // Connected
                .bypmout = 0,
                .auxmout = 0,
                .moutmt = NAU8814_MUTE_OFF,
            },
    },

    {
        .addr = NAU8814_REGIS_POWER_MANAGEMENT_4,
        .Reg.PowerManagement4 =
            {
                .ibadj = 0,
                .trimreg = 0,
                .micbiasm = 0,
                .lpdac = 0,
                .lpspkd = 0,
                .lpadc = 0,
                .lpipbst = 0,
            },
    },

    {
        .addr = NAU8814_REGIS_TIME_SLOT,
        .Reg.TimeSlot =
            {
                .tslot = 0,
            },
    },

    {
        .addr = NAU8814_REGIS_ADCOUT_DRIVE,
        .Reg.AdcOutDrive =
            {
                .tslot = 0,
                .pcmb = 0,
                .loutr = 1,
                .pudps = 0,
                .pudpe = 0,
                .pudoen = 0,
                .pcm8bit = 0,
                .tri = 0,
                .pcmtsen = 0,

            },
    },

    {
        .addr = NAU8814_REGIS_HIGH_VOLTAGE_CTRL,
        .Reg.HighVoltageControl =
            {
                .hvop = 0,
                .hvopu = 0,
                .moutmt = NAU8814_MUTE_OFF,
            },
    },

    {
        .addr = NAU8814_REGIS_ALC_ENHANCEMENTS_1,
        .Reg.AlcEnhancements1 =
            {
                .alcgain = 1,
                .alcngsel = 0,
                .alcpksel = 0,
                .alctblsel = 0,
            },
    },

    {
        .addr = NAU8814_REGIS_ALC_ENHANCEMENTS_2,
        .Reg.AlcEnhancements2 =
            {
                .pklimen = 0,
            },
    },

    {
        .addr = NAU8814_REGIS_ADDITIONAL_IF_CTRL,
        .Reg.AdditionalIfControl =
            {
                .dacos256 = 1,
                .plllockp = 1,
                .dacinmt = 1,
                .nfdly = 0,
                .fserrena = 0,
                .fserflsh = 0,
                .fserrval = 0,
                .spien = 0,
            },
    },

    {
        .addr = NAU8814_REGIS_POWER_TIE_OFF_CTRL,
        .Reg.PowerTieOffControl =
            {
                .manvrefl = 0,
                .manvrefm = 0,
                .manvrefh = 0,
                .lpspka = 0,
            },
    },

    {
        .addr = NAU8814_REGIS_OUTPUT_TIE_OFF_CTRL,
        .Reg.OutputTieOffControl =
            {
                .smout = 1,
                .spspk = 1,
                .snspk = 0,
                .sbufl = 0,
                .sbufh = 0,
                .manouten = 0,
            },
    },
};

//! Nau8814 ROM configurations
const NAU8814_CONFIG Nau8814_configuration[] = {
    {
        .num = 1,
        .adcOn = TRUE,
        .mclkFreqHz = 10000000.0,
        .ddsNum = NAU8814_1_SW_DAC_NUM,
        .i2sRole = NAU8814_1_I2S_BUS_ROLE,
        .i2cNum = NAU8814_1_I2C_NUM,
        .i2sNum = NAU8814_1_I2S_NUM,
        .pllN = 5,
        .pMicGain = NAU8814_1_P_MIC_GAIN,
        .pgaGain = NAU8814_1_PGA_GAIN,
        .dacGain = NAU8814_1_DAC_GAIN,
        .spkGain = NAU8814_1_SPK_GAIN,
        .auxGain = NAU8814_1_AUX_GAIN,
        .RegVals = Nau8814RegConfig,
        .regValCnt = SIZE_OF_ARRAY(Nau8814RegConfig),
        .chipAddr = 0x1a,
        .name = "NAU8814YG",
        .valid = TRUE,
    },
};

//! NAU8814 RAM instances
NAU8814_HANDLE NAU8814_instance[] = {
    {
        .num = 1,
        .valid = TRUE,
        .init = FALSE,
    }
};

//**************************************************************************************************
// Declarations of local (private) functions
//**************************************************************************************************


//**************************************************************************************************
//==================================================================================================
// Definitions of global (public) functions
//==================================================================================================
//**************************************************************************************************


//**************************************************************************************************
//! Get number of NAU8814 chips supported by this PCB
//!
//! \note       Get number of NAU8814 chips supported by this PCB
//!
//! \param[in]  none
//!
//! \return     Number of NAU8814 chips supported by this PCB
//**************************************************************************************************
U32 NAU8814_GetCnt(void)
{
    U8 cnt = 0;
    cnt = SIZE_OF_ARRAY(Nau8814_configuration);
    return cnt;
} // end of NAU8814_GetCnt()



//******************************* end of file ******************************************************
