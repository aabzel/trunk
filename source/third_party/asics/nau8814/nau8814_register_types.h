//**************************************************************************************************
//! @Module  NAU8814 ASIC Driver
//! \file   nau8814_register_types.h
//! \brief  Interface of the MODULE module.
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef NAU8814_REGISTER_TYPES_H
#define NAU8814_REGISTER_TYPES_H

//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#include "nau8814_constants.h"


//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

//! 13.9.2. Phase Lock Loop Control (PLL) Registers
typedef union {
    //! PLL K value
    U32 pllK;
    struct
    {
        //! bit: [8:0]
        U32 pllK_8_0 : 9;
        //! bit:  [17:9]
        U32 pllK_17_9 : 9;
        //! bit: K[23:18]
        U32 pllK_23_18 : 6;
        //! reserved
        U32 reserved : 8;
    };
} NAU8814_PLL_K;


//! register 0x4F, Output Tie-off Direct Manual Control REGISTER
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! reserved
        U16 reserved1 : 3;
        //! SMOUT
        U16 smout : 1;
        //! SPSPK
        U16 spspk : 1;
        //! SNSPK
        U16 snspk : 1;
        //! SBUFL
        U16 sbufl : 1;
        //! SBUFH
        U16 sbufh : 1;
        //! MANOUTEN
        U16 manouten : 1;
        //! reserved
        U16 reserved2 : 7;
    };
} NAU8814_REGISTER_OUTPUT_TIE_OFF_CONTROL;


//! Reg 0x4E, AUTOMUTE CONTROL AND STATUS REGISTER
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  Peak limiter indicator
        U16 ftdec : 1;
        //! reserved1
        U16 reserved1 : 1;
        //! Digital Mute function of the DAC
        U16 dmute : 1;
        //! Analog Mute function applied to DAC
        U16 amute : 1;
        //! Logic controlling the Noise Gate
        U16 nsgate : 1;
        //! High voltage detection circuit monitoring VDDSPK voltage
        U16 hvdet : 1;
        //! Select observation point used by DAC output Automute feature
        U16 amtctrl : 1;
        //! reserved2
        U16 reserved2 : 9;
    };
} NAU8814_REGISTER_CONTROL_AND_STATUS;


//! Reg 0x4D (Read ONLY Register), AGC PEAK OUT REGISTER
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  instantaneous value contained in the peak detector amplitude
        U16 pdet : 9;
        //! reserved
        U16 reserved : 7;
    };
} NAU8814_REGISTER_AGC_PEAK_DETECTOR;


//! Reg 0x4C  (Read ONLY Register), AGC PEAK-TO-PEAK OUT REGISTER
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  instantaneous value contained in the peak-to-peak amplitude
        U16 p2pdet : 9;
        //! reserved
        U16 reserved : 7;
    };
} NAU8814_REGISTER_AGC_P2P_DETECTOR;


//! Reg 0x4B, Output Tie-Off REGISTER
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  Direct manual control for switch for VREF 6k-ohm resistor to ground
        U16 manvrefl : 1;
        //! bit 0  Direct manual control for switch for VREF 160k-ohm resistor to ground
        U16 manvrefm : 1;
        //! bit 0  Direct manual control of switch for VREF 600k-ohm resistor to ground
        U16 manvrefh : 1;
        //! bit 0 reserved
        U16 reserved1 : 4;
        //! bit 0  Amplifier Stage
        U16 lpspka : 1;
        //! bit 0 reserved
        U16 reserved2 : 8;
    };
} NAU8814_REGISTER_POWER_TIE_OFF_CONTROL;

//! Reg 0x49, MISC CONTROL REGISTER
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  Set DAC to use 256x oversampling rate
        U16 dacos256 : 1;
        //! bit 1  Enable control to use PLL output when PLL is not in phase locked condition
        U16 plllockp : 1;
        //! bit 2  Enable control to mute DAC limiter output when softmute is enabled
        U16 dacinmt : 1;
        //! bit 3  Enable control to delay use of notch filter output when filter is enabled
        U16 nfdly : 1;
        //! bit 4  Enable control for short frame cycle detection logic
        U16 fserrena : 1;
        //! bit 5  Enable DSP state flush on short frame sync event
        U16 fserflsh : 1;
        //! bit 7-6  Short frame sync detection period value trigger if frame time less than
        U16 fserrval : 2;
        //! bit 8  Set SPI control bus mode regardless of state of Mode pin
        U16 spien : 1;
        //! bit  15-9 reserved
        U16 reserved : 7;
    };
} NAU8814_REGISTER_ADDITIONAL_IF_CONTROL;


//! Reg 0x47, ALC Enhanced 2 Register
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0 reserved1
        U16 reserved1 : 8;
        //! bit 8 PKLIMEN Enable control for ALC fast peak limiter function
        U16 pklimen : 1;
        //! bit 15:9 reserved2
        U16 reserved2 : 7;
    };
} NAU8814_REGISTER_ALC_ENHANCEMENTS2;

//! Reg 0x46, ALC1 Enhanced Register
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! ALCGAIN ( ONLY)
        U16 alcgain : 6;
        //! ALCNGSEL
        U16 alcngsel : 1;
        //! ALCPKSEL
        U16 alcpksel : 1;
        //! ALCTBLSEL
        U16 alctblsel : 1;
        //! reserved
        U16 reserved : 7;
    };
} NAU8814_REGISTER_ALC_ENHANCEMENTS1;


//! REg 0x45, OUTPUT Driver Control Register
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  Override to automatic 3V/5V bias selection
        U16 hvop : 1;
        //! bit 1 reserved
        U16 reserved1 : 1;
        //! bit 2  High Voltage override
        U16 hvopu : 1;
        //! bit 3 reserved
        U16 reserved2 : 1;
        //! bit 4  Headphone output mute
        U16 moutmt : 1;
        //! bit -5 reserved
        U16 res3 : 11;
    };
} NAU8814_REGISTER_HIGH_VOLTAGE_CONTROL;

//! Reg 0x3C, PCM2 TIMESLOT CONTROL REGISTER
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! TSLOT[9]
        U16 tslot : 1;
        //! bit 1 PCMB  PCM Mode2
        U16 pcmb : 1;
        //! bit 2 LOUTR Left and Right Channel have same data
        U16 loutr : 1;
        //! bit 3 PUDPS Power Up and Down Pull Select
        U16 pudps : 1;
        //! bit 4 PUDPE Power Up and Down Pull Enable
        U16 pudpe : 1;
        //! bit 5 PUDOEN Power Up and Down Output Enable
        U16 pudoen : 1;
        //! bit 6 PCM8BIT PCM Word Length
        U16 pcm8bit : 1;
        //! bit 7 TRI Tri-state PCMT LSB
        U16 tri : 1;
        //! bit 8 PCMTSEN PCM Transit Enable
        U16 pcmtsen : 1;
        //! reserved
        U16 reserved : 7;
    };
} NAU8814_REGISTER_ADC_OUT_DRIVE;


//! Reg 0x3B, PCM1 TIMESLOT CONTROL REGISTER
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 8-0 TSLOT[8:0]
        U16 tslot : 9;
        //! reserved
        U16 reserved : 7;
    };
} NAU8814_REGISTER_TIME_SLOT;

//! Reg 0x3A,Power Management 4
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! IBADJ[1:0]
        U16 ibadj : 2;
        //! TRIMREG[3:2]
        U16 trimreg : 2;
        //! MICBIASM
        U16 micbiasm : 1;
        //! LPDAC
        U16 lpdac : 1;
        //! LPSPKD
        U16 lpspkd : 1;
        //! LPADC
        U16 lpadc : 1;
        //! LPIPBST
        U16 lpipbst : 1;
        //! reserved
        U16 reserved : 7;
    };
} NAU8814_REGISTER_POWER_MANAGEMENT4;

//! Reg 0x38, MONO Mixer Control Register
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0 DACMOUT, DAC to MONO Mixer
        U16 dacmout : 1;
        //! 1 BYPMOUT, Bypass path (output of Boost Stage) to MONO Mixer
        U16 bypmout : 1;
        //! 2 AUXMOUT, Auxiliary to MONO Mixer
        U16 auxmout : 1;
        //! 5-3  reserved
        U16 reserved1 : 3;
        //! 6 MOUTMXMT, MOUT Mute
        U16 moutmt : 1;
        //! reserved
        U16 reserved2 : 9;
    };
} NAU8814_REGISTER_MONO_MIXER_CONTROL;

//! Reg 0x36, Speaker Gain Control Register
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  Speaker Gain
        U16 spkgain : 6;
        //! Speaker Output
        U16 spkmt : 1;
        //! Speaker Gain Control Zero Cross
        U16 spkzc : 1;
        //! reserved
        U16 reserved : 8;
    };
} NAU8814_REGISTER_SPK_OUT_VOLUME;

//! Reg 0x31, Output Register
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  Analog Output Resistance
        U16 aoutimp : 1;
        //! Thermal Shutdown
        U16 tsen : 1;
        //! Speaker Output Boost Stage
        U16 spkbst : 1;
        //! MONO Output Boost Stage
        U16 moutbst : 1;
        //! reserved
        U16 reserved : 12;
    };
} NAU8814_REGISTER_OUTPUT_CONTROL;

//! Reg 0x2F, ADC Boost Control Registers
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 2-0  Auxiliary to Input Boost Stage
        U16 auxbstgain : 3;
        //! reserved1
        U16 reserved1 : 1;
        //! MIC+ pin to the input Boost Stage
        U16 pmicbstgain : 3;
        //! reserved
        U16 reserved2 : 1;
        //! Input Boost
        U16 pgabst : 1;
        //! res3
        U16 res3 : 7;
    };
} NAU8814_REGISTER_ADC_BOOST;


//! Reg 0x2D, PGA Gain Control Register
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 5-0  Programmable Gain Amplifier Gain
        U16 pgagain : 6;
        //! bit6 Mute Control for PGA
        U16 pgamt : 1;
        //! bit7 PGA Zero Cross Enable
        U16 pgazc : 1;
        //! res
        U16 reserved : 8;
    };
} NAU8814_REGISTER_PGA_GAIN;

//! Reg 0x2C, Input Signal Control Register
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  Input PGA amplifier positive terminal to MIC+
                         //! or VREF
        U16 pmicpga : 1;
        //! MICN to input PGA negative terminal
        U16 nmicpga : 1;
        //! AUX amplifier output to input PGA signal source
        U16 auxpga : 1;
        //! Auxiliary Input mode
        U16 auxm : 1;
        //! xxxx
        U16 reserved1 : 3;
        //! Microphone Bias Voltage Control
        U16 micbiasv : 2;
        //! reserved        U16 reserved2 : 7;
    };
} NAU8814_REGISTER_INPUT_CONTROL;


//! Reg 0x28, Attenuation Control Register
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0 reserved
        U16 reserved1 : 1;
        //! speaker  Attenuation
        U16 spkatt : 1;
        //! Mono out   Attenuation
        U16 moutatt : 1;
        //! reserved
        U16 reserved2 : 13;
    };
} NAU8814_REGISTER_ATTENUATION_CONTROL;

//! Reg 0x27, Phase Lock Loop Control (PLL)
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0 reserved
        U16 pllk_8_0 : 9;
        //! reserved
        U16 reserved : 7;
    };
} NAU8814_REGISTER_LSB;

//! Reg 0x26, Phase Lock Loop Control (PLL)
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0 reserved
        U16 pllk_17_9 : 9;
        //! reserved
        U16 reserved : 7;
    };
} NAU8814_REGISTER_PLL_MID;

//! Reg 0x25, Phase Lock Loop Control (PLL)
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0 reserved
        U16 pllk_23_18 : 6;
        //! reserved
        U16 reserved : 10;
    };
} NAU8814_REGISTER_PLL_K_MSB;

//! Reg 0x24, PLL Control Registers
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  PLL Integer
        U16 plln : 4;
        //! PLL Clock
        U16 pllmclk : 1;
        //! reserved
        U16 reserved : 11;
    };
} NAU8814_REGISTER_PLL_N_CONTROL;

//! Reg 0x23, NOISE GAIN CONTROL REGISTER
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 2-0 ALCNTH[2:0] Noise Gate Threshold
        U16 alcnth : 3;
        //! 3 ALCNEN Noise Gate Enable
        U16 alcnen : 1;
        //! reserved
        U16 reserved : 12;
    };
} NAU8814_REGISTER_NOISE_GATE;


//! Reg 0x22, Automatic Level Control ALC3 REGISTER
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  Automatic Level Control ATTACK TIME
        U16 alcatk : 4;
        //! Automatic Level Control DECAY TIME
        U16 alcdcy : 4;
        //! Automatic Level Control Mode
        U16 alcm : 1;
        //! reserved
        U16 reserved : 7;
    };
} NAU8814_REGISTER_ALC_CONTROL3;

//! Reg 0x21,  ALC2 REGISTER
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  ALC TARGET – sets signal level at ADC input
        U16 alcsl : 4;
        //! ALC HOLD TIME before gain is increased
        U16 alcht : 4;
        //! ALC Zero Crossing Detect
        U16 alczc : 1;
        //! reserved
        U16 reserved : 7;
    };
} NAU8814_REGISTER_ALC_CONTROL2;

//! Reg 0x20, AUTOMATIC LEVEL CONTROL REGISTER
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 2-0  Minimum Gain
        U16 alcmngain : 3;
        //! 5-3  Maximum Gain
        U16 alcmxgain : 3;
        //! 7-6 xxxxx
        U16 reserved1 : 2;
        //! ALC Enable
        U16 alcen : 1;
        //! reserved
        U16 reserved2 : 7;
    };
} NAU8814_REGISTER_ALC_CONTROL1;

//! Reg xxxxx,  NOTCH FILTER
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0 reserved
        U16 nfca1 : 7;
        //! reserved
        U16 reserved1 : 1;
        //! reserved
        U16 nfcu : 1;
        //! reserved
        U16 reserved2 : 7;
    };
} NAU8814_REGISTER_NOTCH_FILTER1_LOW;

//! Reg 0x32, Speaker Mixer Control Register
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  DACSPK DAC to Speaker Mixer
        U16 dacspk : 1;
        //! 1 BYPSPK Bypass path (output of Boost stage) to Speaker Mixer
        U16 bypspk : 1;
        //! 2-4 reserved
        U16 reserved1 : 3;
        //! 5  AUXSPK Auxiliary to Speaker Mixer
        U16 auxspk : 1;
        //! 6-15 reserved
        U16 reserved2 : 10;
    };
} NAU8814_REGISTER_SPEAKER_MIXER_CONTROL;

//! Reg 0x1E, NOTCH FILTER
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! NFCA1[6:0]
        U16 nfca1 : 7;
        //! reserved1
        U16 reserved1 : 1;
        //! NFCU
        U16 nfcu : 1;
        //! reserved2
        U16 reserved2 : 7;
    };
} NAU8814_REGISTER_NOTCH_FILTER1_HIGH;


//! Reg 0x1c, Notch Filter Low
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! NFCA0[6:0]
        U16 nfca0 : 7;
        //! reserved
        U16 reserved1 : 1;
        //! NFCU
        U16 nfcu : 1;
        //! reserved
        U16 reserved2 : 7;
    };
} NAU8814_REGISTER_NOTCH_FILTER0_LOW;

//! Reg:1B,Notch Filter High
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! NFCA0[13:7]
        U16 nfca0 : 7;
        //! NFCEN
        U16 nfcen : 1;
        //! NFCU
        U16 nfcu : 1;
        //! reserved
        U16 reserved : 7;
    };
} NAU8814_REGISTER_NOTCH_FILTER0_HIGH;


//! Reg 0x19, DIGITAL TO ANALOG CONVERTER (DAC) LIMITER
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 3-0  DAC Limiter volume Boost
        U16 daclimbst : 4;
        //! 6-4  DAC Limiter Programmable signal threshold level
        U16 daclimthl : 3;
        //! reserved
        U16 reserved : 9;
    };
} NAU8814_REGISTER_DAC_LIMITER2;

//! Reg 0x18, DIGITAL TO ANALOG CONVERTER (DAC) LIMITER
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 3-0  DAC Limiter Attack time
        U16 daclimatk : 4;
        //! 7-4 DAC Limiter Decay time
        U16 daclimdcy : 4;
        //! DAC Digital Limiter
        U16 daclimen : 1;
        //! reserved
        U16 reserved : 7;
    };
} NAU8814_REGISTER_DAC_LIMITER1;

//! Reg 0x16, EQ5-High Cutoff
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! EQ5GC[4:0]
        U16 eq5gc : 5;
        //! EQ5CF[1:0]
        U16 eq5cf : 2;
        //! reserved
        U16 reserved : 9;
    };
} NAU8814_REGISTER_EQ5_HIGH_CUT_OFF;


//! Reg 0x15,EQ4-Peak3
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! EQ4GC[4:0]
        U16 eq4gc : 5;
        //! EQ4CF[1:0]
        U16 eq4cf : 2;
        //! reserved
        U16 reserved1 : 1;
        //! EQ4BW
        U16 eq4bw : 1;
        //! reserved
        U16 reserved2 : 7;
    };
} NAU8814_REGISTER_EQ4_PEAK3;

//! Reg 0x14, EQ3-Peak 2
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! EQ3GC[4:0]
        U16 eq3gc : 5;
        //! EQ3CF[1:0]
        U16 eq3cf : 2;
        //! reserved
        U16 reserved1 : 1;
        //! EQ3BW
        U16 eq3bw : 1;
        //! reserved
        U16 reserved2 : 7;
    };
} NAU8814_REGISTER_EQ3_PEAK2;

//! Reg 0x13, EQ2-Peak 1
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! EQ2GC[4:0]
        U16 eq2gc : 5;
        //! EQ2CF[1:0]
        U16 eq2cf : 2;
        //! reserved
        U16 reserved1 : 1;
        //! EQ2BW
        U16 eq2bw : 1;
        //! reserved
        U16 reserved2 : 7;
    };
} NAU8814_REGISTER_EQ2_PEAK1;


//! Reg 0x12, EQ1-Low Cutoff
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! EQ1GC[4:0]
        U16 eq1gc : 5;
        //! EQ1CF[1:0]
        U16 eq1cf : 2;
        //! reserved
        U16 reserved1 : 1;
        //! EQM
        U16 eqm : 1;
        //! reserved
        U16 reserved2 : 7;
    };
} NAU8814_REGISTER_EQ1_LOW_CUTOFF;

//! Reg 0x0E, ADC Control Register
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  ADC Polarity
        U16 adcpl : 1;
        //! 2-1 xxxx
        U16 reserved1 : 2;
        //! 3  Over Sample Rate
        U16 adcos : 1;
        //! 6-4  High Pass Filter
        U16 hpf : 3;
        //! Audio or Application Mode
        U16 hpfam : 1;
        //! High Pass Filter Enable
        U16 hpfen : 1;
        //! reserved
        U16 reserved2 : 7;
    };
} NAU8814_REGISTER_ADC_CONTROL;


//! Reg 0x0F, ADC Gain Control Register
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  ADC Gain
        U16 adcgain : 8;
        //! reserved
        U16 reserved : 8;
    };
} NAU8814_REGISTER_ADC_VOLUME;


//! 0x0B, DAC Gain Control Register
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  DAC Gain
        U16 dacgain : 8;
        //! reserved
        U16 reserved : 8;
    };
} NAU8814_REGISTER_DAC_VOLUME;


//! Reg 0x0A, DAC CTRL
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  Polarity Invert
        U16 dacpl : 1;
        //! reserved1
        U16 reserved1 : 1;
        //! AUTOMT,Auto Mute enable
        U16 automt : 1;
        //! DACOS,Over Sample Rate
        U16 dacos : 1;
        //! DEEMP[1:0],5-4 De-emphasis
        U16 deemp : 2;
        //! DACMT,Soft Mute Enable
        U16 dacmt : 1;
        //! reserved2
        U16 reserved2 : 9;
    };
} NAU8814_REGISTER_DACCONTROL;

//! Reg 0x08, GPIO Control Register
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit2- 0  General Purpose I/O Selection
        U16 gpiosel : 3;
        //! 3  GPIO Polarity
        U16 gpiopl : 1;
        //! 5-3 PLL Output Clock Divider
        U16 gpiopll : 2;
        //! reserved
        U16 reserved : 10;
    };
} NAU8814_REGISTER_GPIO_CONTROL;

//! Reg 0x07, Audio Sample Rate Control Register
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  Slow Clock Enable
        U16 sclken : 1;
        //! 3-1  Sample Rate Selection
        U16 smplr : 3;
        //! reserved
        U16 reserved : 12;
    };
} NAU8814_REGISTER_CLOCK_CONTROL2;

//! Reg 0x06, Clock Control Register
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  FRAME and BCLK
        U16 clkioen : 1;
        //! reserved
        U16 reserved1 : 1;
        //! 4-2   Bit Clock Select
        U16 bclksel : 3;
        //! 7-5 Master Clock Selection
        U16 mclksel : 3;
        //! 8 Source of Internal Clock
        U16 clkm : 1;
        //! reserved
        U16 reserved2 : 7;
    };
} NAU8814_REGISTER_CLOCK_CONTROL1;

//! Reg 0x05, Audio Interface Companding Control
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  loopback
        U16 addap : 1;
        //! 1-2 ADC Companding Select
        U16 adccm : 2;
        //! 3-4  DAC Companding Selection
        U16 daccm : 2;
        //! reserved
        U16 reserved : 11;
    };
} NAU8814_REGISTER_COMPANDING;


//! Reg 0x04, Audio Interface Control
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0, reserved1
        U16 reserved1 : 1;
        //! ADCPHS,ADC Data ‘right’ or ‘left’ phases of FRAME clock
        U16 adcphs : 1;
        //! DACPHS,DAC Data ‘right’ or ‘left’ phases of FRAME clock
        U16 dacphs : 1;
        //! AIFMT[1:0]
        U16 aifmt : 2;
        //! WLEN[1:0]
        U16 wlen : 2;
        //! FSP,Frame Clock Polarity
        U16 fsp : 1;
        //! BCLKP, BCLK Polarity
        U16 bclkp : 1;
        //! reserved2
        U16 reserved2 : 7;
    };
} NAU8814_REGISTER_AUDIO_INTERFACE;

//! Reg 0x02, Power Management 2
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  ADC Enable
        U16 adcen : 1;
        //! reserved
        U16 reserved1 : 1;
        //! 2  MIC(+/-) PGA Enable
        U16 pgaen : 1;
        //! reserved
        U16 reserved2 : 1;
        //! 4  Input Boost Enable
        U16 bsten : 1;
        //! reserved
        U16 res3 : 11;
    };
} NAU8814_REGISTER_POWER_MANAGEMENT2;

//! Reg 0x03, Power Management 3
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0  DAC Enable
        U16 dacen : 1;
        //! reserved
        U16 reserved1 : 1;
        //! Speaker Mixer Enable
        U16 spkmxen : 1;
        //! MONO Mixer Enable
        U16 moutmxen : 1;
        //! reserved
        U16 reserved2 : 1;
        //! SPKOUT+ Enable
        U16 pspken : 1;
        //! SPKOUT- Enable
        U16 nspken : 1;
        //! MOUT Enable
        U16 mouten : 1;
        //! reserved
        U16 res3 : 8;
    };
} NAU8814_REGISTER_POWER_MANAGEMENT3;

//! Reg xxxxx, Power Management 1
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! bit 0-1  VREF REFERENCE IMPEDANCE SELECTION
        U16 refimp : 2;
        //! Unused input/output tie off buffer enable
        U16 iobufen : 1;
        //! Analogue amplifier bias control
        U16 abiasen : 1;
        //! Microphone Bias Enable
        U16 micbiasen : 1;
        //! PLL enable
        U16 pllen : 1;
        //! AUX input buffer enable
        U16 auxen : 1;
        //! reserved
        U16 reserved1 : 1;
        //! Buffer for DC level shifting Enable
        U16 dcbufen : 1;
        //! reserved
        U16 reserved2 : 7;
    };
} NAU8814_REGISTER_POWER_MANAGEMENT1;

//! Reg 0x00, Software Reset
typedef union {
    //! register raw value
    U16 word;
    struct
    {
        //! RESET (SOFTWARE)
        U16 reset : 9;
        //! reserved
        U16 reserved : 7;
    };

} NAU8814_REGISTER_SOFTWARE_RESET;

//! NAU8814 Universal register type
typedef union {
    //! register raw value
    U16 word;
    //! REGISTER_SOFTWARE_RESET
    NAU8814_REGISTER_SOFTWARE_RESET SoftwareReset;
    //! NAU8814 REGISTER POWER_MANAGEMENT1
    NAU8814_REGISTER_POWER_MANAGEMENT1 PowerManagement1;
    //! NAU8814 REGISTER POWER_MANAGEMENT2
    NAU8814_REGISTER_POWER_MANAGEMENT2 PowerManagement2;
    //! NAU8814 REGISTER POWER_MANAGEMENT3
    NAU8814_REGISTER_POWER_MANAGEMENT3 PowerManagement3;
    //! NAU8814 REGISTER AUDIO_INTERFACE
    NAU8814_REGISTER_AUDIO_INTERFACE AudioInterface;
    //! NAU8814 REGISTER COMPANDING
    NAU8814_REGISTER_COMPANDING      Companding;
    //! NAU8814 REGISTER CLOCK_CONTROL1
    NAU8814_REGISTER_CLOCK_CONTROL1  ClockControl1;
    //! NAU8814 REGISTER CLOCK_CONTROL2
    NAU8814_REGISTER_CLOCK_CONTROL2  ClockControl2;
    //! NAU8814 REGISTER GPIO_CONTROL
    NAU8814_REGISTER_GPIO_CONTROL    GpioControl;
    //! NAU8814 REGISTER DACCONTROL
    NAU8814_REGISTER_DACCONTROL      DacControl;
    //! NAU8814 REGISTER DAC_VOLUME
    NAU8814_REGISTER_DAC_VOLUME      DacVolume;
    //! NAU8814 REGISTER ADC_CONTROL
    NAU8814_REGISTER_ADC_CONTROL AdcControl;
    //! NAU8814 REGISTER ADC_VOLUME
    NAU8814_REGISTER_ADC_VOLUME  AdcVolume;
    //! NAU8814 REGISTER EQ1_LOW_CUTOFF
    NAU8814_REGISTER_EQ1_LOW_CUTOFF   Eq1LowCutoff;
    //! NAU8814 REGISTER EQ2_PEAK1
    NAU8814_REGISTER_EQ2_PEAK1        Eq2Peak1;
    //! NAU8814 REGISTER EQ3_PEAK2
    NAU8814_REGISTER_EQ3_PEAK2        Eq3Peak2;
    //! NAU8814 REGISTER EQ4_PEAK3
    NAU8814_REGISTER_EQ4_PEAK3        Eq4Peak3;
    //! NAU8814 REGISTER EQ5_HIGH_CUT_OFF
    NAU8814_REGISTER_EQ5_HIGH_CUT_OFF Eq5HighCutoff;
    //! DIGITAL TO ANALOG (DAC) LIMITER
    NAU8814_REGISTER_DAC_LIMITER1 DacLimiter1;
    //! NAU8814 REGISTER DAC_LIMITER2
    NAU8814_REGISTER_DAC_LIMITER2 DacLimiter2;
    //! NAU8814 REGISTER NOTCH_FILTER0_HIGH
    NAU8814_REGISTER_NOTCH_FILTER0_HIGH NotchFilter0High;
    //! NAU8814 REGISTER NOTCH_FILTER0_LOW
    NAU8814_REGISTER_NOTCH_FILTER0_LOW  NotchFilter0Low;
    //! NAU8814 REGISTER NOTCH_FILTER1_HIGH
    NAU8814_REGISTER_NOTCH_FILTER1_HIGH NotchFilter1High;
    //! NAU8814 REGISTER NOTCH_FILTER1_LOW
    NAU8814_REGISTER_NOTCH_FILTER1_LOW  NotchFilter1Low;
    //! NAU8814 REGISTER ALC_CONTROL1
    NAU8814_REGISTER_ALC_CONTROL1 AlcControl1;
    //! NAU8814 REGISTER ALC_CONTROL2
    NAU8814_REGISTER_ALC_CONTROL2 AlcControl2;
    //! NAU8814 REGISTER ALC_CONTROL3
    NAU8814_REGISTER_ALC_CONTROL3 AlcControl3;
    //! NAU8814 REGISTER NOISE_GATE
    NAU8814_REGISTER_NOISE_GATE   NoiseGate;
    //! NAU8814 REGISTER PLL_N_CONTROL
    NAU8814_REGISTER_PLL_N_CONTROL PllNControl;
    //! NAU8814 REGISTER PLL_K_MSB
    NAU8814_REGISTER_PLL_K_MSB     Pllkl;
    //! NAU8814 REGISTER PLL_MID
    NAU8814_REGISTER_PLL_MID       Pllk2;
    //! NAU8814 REGISTER LSB
    NAU8814_REGISTER_LSB           Pllk3;
    //! INPUT, OUTPUT & MIXER CONTROL
    NAU8814_REGISTER_ATTENUATION_CONTROL AttenuationControl;
    //! NAU8814 REGISTER INPUT_CONTROL
    NAU8814_REGISTER_INPUT_CONTROL       InputControl;
    //! NAU8814 REGISTER PGA_GAIN
    NAU8814_REGISTER_PGA_GAIN            PgaGain;
    //! NAU8814 REGISTER ADC_BOOST
    NAU8814_REGISTER_ADC_BOOST           AdcBoost;
    //! NAU8814 REGISTER OUTPUT_CONTROL
    NAU8814_REGISTER_OUTPUT_CONTROL      OutputControl;
    //! NAU8814 REGISTER SPEAKER_MIXER_CONTROL
    NAU8814_REGISTER_SPEAKER_MIXER_CONTROL SpeakerMixerControl;
    //! NAU8814 REGISTER SPK_OUT_VOLUME
    NAU8814_REGISTER_SPK_OUT_VOLUME     SpkOutVolume;
    //! NAU8814 REGISTER MONO_MIXER_CONTROL
    NAU8814_REGISTER_MONO_MIXER_CONTROL MonoMixerControl;
    //! NAU8814 REGISTER POWER_MANAGEMENT4
    NAU8814_REGISTER_POWER_MANAGEMENT4 PowerManagement4;
    //! NAU8814 REGISTER PCM TIME SLOT & ADC OUT IMPEDANCE OPTION CONTROL
    NAU8814_REGISTER_TIME_SLOT     TimeSlot;
    //! NAU8814 REGISTER ADC_OUT_DRIVE
    NAU8814_REGISTER_ADC_OUT_DRIVE AdcOutDrive;
    //! NAU8814 REGISTER HIGH_VOLTAGE_CONTROL
    NAU8814_REGISTER_HIGH_VOLTAGE_CONTROL   HighVoltageControl;
    //! NAU8814 REGISTER ALC_ENHANCEMENTS1
    NAU8814_REGISTER_ALC_ENHANCEMENTS1      AlcEnhancements1;
    //! NAU8814 REGISTER ALC_ENHANCEMENTS2
    NAU8814_REGISTER_ALC_ENHANCEMENTS2      AlcEnhancements2;
    //! NAU8814 REGISTER ADDITIONAL_IF_CONTROL
    NAU8814_REGISTER_ADDITIONAL_IF_CONTROL  AdditionalIfControl;
    //! NAU8814 REGISTER POWER_TIE_OFF_CONTROL
    NAU8814_REGISTER_POWER_TIE_OFF_CONTROL  PowerTieOffControl;
    //! NAU8814 REGISTER AGC_P2P_DETECTOR
    NAU8814_REGISTER_AGC_P2P_DETECTOR       AgcP2pDetector;
    //! NAU8814 REGISTER AGC_PEAK_DETECTOR
    NAU8814_REGISTER_AGC_PEAK_DETECTOR      AgcPeakDetector;
    //! NAU8814 REGISTER CONTROL_AND_STATUS
    NAU8814_REGISTER_CONTROL_AND_STATUS     ControlAndStatus;
    //! NAU8814 REGISTER OUTPUT_TIE_OFF_CONTROL
    NAU8814_REGISTER_OUTPUT_TIE_OFF_CONTROL OutputTieOffControl;
} NAU8814_REGISTER_UNIVERSAL;

//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

// None.



//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************

// None.



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************


#endif //! #ifndef NAU8814_REGISTER_TYPES_H

//******************************* end of file ******************************************************
