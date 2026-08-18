#ifndef NAU8814_REG_TYPES_H
#define NAU8814_REG_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "nau8814_const.h"

/* Reg 0x4F
 * 13.21. Output Tie-off Direct Manual Control REGISTER
 * */
typedef union {
    uint16_t word;
    struct {
        uint16_t res1 : 3;  /*bit 0  xxxx*/
        uint16_t smout : 1;  /*  xxxx*/
        uint16_t spspk : 1;  /*  xxxx*/
        uint16_t snspk : 1;  /*  xxxx*/
        uint16_t sbufl : 1;  /*  xxxx*/
        uint16_t sbufh : 1;  /*  xxxx*/
        uint16_t manouten : 1;  /*  xxxx*/
        uint16_t res2 : 7;  /* xxxx*/
    };
}Nau8814RegOutputTieOffControl_t;


/* Reg 0x4E
 * 13.20. AUTOMUTE CONTROL AND STATUS REGISTER
 * */
typedef union {
    uint16_t word;
    struct {
        uint16_t ftdec : 1;  /*bit 0  Peak limiter indicator*/
        uint16_t res1 : 1;  /*  xxxx*/
        uint16_t dmute : 1;  /*  Digital Mute function of the DAC*/
        uint16_t amute : 1;  /*  Analog Mute function applied to DAC*/
        uint16_t nsgate : 1;  /*  Logic controlling the Noise Gate*/
        uint16_t hvdet : 1;  /*  High voltage detection circuit monitoring VDDSPK voltage*/
        uint16_t amtctrl : 1;  /*  Select observation point used by DAC output Automute feature*/
        uint16_t res2 : 9;  /* xxxx*/
    };
}Nau8814RegControlAndStatus_t;


/* Reg 0x4D (Read ONLY Register)
 * 13.19. AGC PEAK OUT REGISTER
 * */
typedef union {
    uint16_t word;
    struct {
        uint16_t pdet : 9;  /*bit 0  instantaneous value contained in the peak detector amplitude*/
        uint16_t res : 7;  /* xxxx*/
    };
}Nau8814RegAgcPeakDetector_t;

/* Reg 0x4C  (Read ONLY Register)
 * 13.18. AGC PEAK-TO-PEAK OUT REGISTER
 * */
typedef union {
    uint16_t word;
    struct {
        uint16_t p2pdet : 9;  /*bit 0  instantaneous value contained in the peak-to-peak amplitude*/
        uint16_t res : 7;  /* xxxx*/
    };
}Nau8814RegAgcP2pDetector_t;


/* Reg 0x4B
 * 13.17. Output Tie-Off REGISTER
 * */
typedef union {
    uint16_t word;
    struct {
        uint16_t manvrefl : 1;  /*bit 0  Direct manual control for switch for VREF 6k-ohm resistor to ground*/
        uint16_t manvrefm : 1;  /*bit 0  Direct manual control for switch for VREF 160k-ohm resistor to ground*/
        uint16_t manvrefh : 1;  /*bit 0  Direct manual control of switch for VREF 600k-ohm resistor to ground*/
        uint16_t res1 : 4;  /*bit 0  xxxx*/
        uint16_t lpspka : 1;  /*bit 0  Amplifier Stage*/
        uint16_t res2 : 8;  /*bit 0  xxxx*/
    };
}Nau8814RegPowerTieOffControl_t;

/* Reg 0x49
 * 13.16. MISC CONTROL REGISTER
 * */
typedef union {
    uint16_t word;
    struct {
        uint16_t dacos256 : 1;  /*bit 0  Set DAC to use 256x oversampling rate*/
        uint16_t plllockp : 1;  /*bit 1  Enable control to use PLL output when PLL is not in phase locked condition*/
        uint16_t dacinmt : 1;  /*bit 2  Enable control to mute DAC limiter output when softmute is enabled*/
        uint16_t nfdly : 1;  /*bit 3  Enable control to delay use of notch filter output when filter is enabled*/
        uint16_t fserrena : 1;  /*bit 4  Enable control for short frame cycle detection logic*/
        uint16_t fserflsh : 1;  /*bit 5  Enable DSP state flush on short frame sync event*/
        uint16_t fserrval : 2;  /*bit 7-6  Short frame sync detection period value trigger if frame time less than*/
        uint16_t spien : 1;  /*bit 8  Set SPI control bus mode regardless of state of Mode pin*/
        uint16_t res : 7;  /*bit  15-9  xxxx*/
    };
}Nau8814RegAdditionalIfControl_t;

/* Reg xxxxx
 * 13.15.2. ALC Enhanced 2 Register
 * */
typedef union {
    uint16_t word;
    struct {
        uint16_t res1 : 8;  /*bit 0  xxxx*/
        uint16_t pklimen : 1;  /*bit 0  Enable control for ALC fast peak limiter function*/
        uint16_t res2 : 7;  /*bit 0  xxxx*/
    };
}Nau8814RegAlcEnhancements2_t;

/* Reg 0x46
 * 13.15.1. ALC1 Enhanced Register
 * */
typedef union {
    uint16_t word;
    struct {
        uint16_t alcgain : 6;  /*bit 0  xxxx*/
        uint16_t alcngsel : 1;  /*bit 0  xxxx*/
        uint16_t alcpksel : 1;  /*bit 0  xxxx*/
        uint16_t alctblsel : 1;  /*bit 0  xxxx*/
        uint16_t res : 7;  /*bit 0  xxxx*/
    };
}Nau8814RegAlcEnhancements1_t;
/* Reg xxxxx*/


/* REg 0x45
 * 13.14. OUTPUT Driver Control Register
 * */
typedef union {
    uint16_t word;
    struct {
        uint16_t hvop : 1;  /*bit 0  Override to automatic 3V/5V bias selection */
        uint16_t res1 : 1;  /*bit 1  xxxx*/
        uint16_t hvopu : 1;  /*bit 2  High Voltage override */
        uint16_t res2 : 1;  /*bit 3  xxxx*/
        uint16_t moutmt : 1;  /*bit 4  Headphone output mute*/
        uint16_t res3 : 11;  /*bit -5  xxxx*/
    };
}Nau8814RegHighVoltageControl_t;

/* Reg 0x3C
 * 13.11.2. PCM2 TIMESLOT CONTROL REGISTER*/
typedef union {
    uint16_t word;
    struct {
        uint16_t tslot : 1;  /*bit 0  xxxx*/
        uint16_t pcmb : 1;  /*bit 1  PCM Mode2*/
        uint16_t loutr : 1;  /*bit 2  Left and Right Channel have same data*/
        uint16_t pudps : 1;  /*bit 3  Power Up and Down Pull Select*/
        uint16_t pudpe : 1;  /*bit 4  Power Up and Down Pull Enable*/
        uint16_t pudoen : 1;  /*bit 5  Power Up and Down Output Enable*/
        uint16_t pcm8bit : 1;  /*bit 6  PCM Word Length*/
        uint16_t tri : 1;  /*bit 7  Tri-state PCMT LSB*/
        uint16_t pcmtsen : 1;  /*bit 8  PCM Transit Enable*/
        uint16_t res : 7; /*  xxxxx*/
    };
}Nau8814RegAdcOutDrive_t;


/* Reg 0x3B
 * 13.11.1. PCM1 TIMESLOT CONTROL REGISTER
 * */
typedef union {
    uint16_t word;
    struct {
        uint16_t tslot : 9;  /*bit 8-0  xxxx*/
        uint16_t res : 7; /*  xxxxx*/
    };
}Nau8814RegTimeSlot_t;

/* Reg xxxxx*/
typedef union {
    uint16_t word;
    struct {
        uint16_t ibadj : 2;  /*bit 0  xxxx*/
        uint16_t trimreg : 2;  /* xxxx*/
        uint16_t micbiasm : 1;  /* xxxx*/
        uint16_t lpdac : 1; /*  xxxxx*/
        uint16_t lpspkd : 1; /*  xxxxx*/
        uint16_t lpadc : 1; /*  xxxxx*/
        uint16_t lpipbst : 1; /*  xxxxx*/
        uint16_t res : 7; /*  xxxxx*/
    };
}Nau8814RegPowerManagement4_t;

/* Reg 0x38
 * 13.10.8. MONO Mixer Control Register*/
typedef union {
    uint16_t word;
    struct{
        uint16_t dacmout : 1;  /*bit 0  DAC to MONO Mixer*/
        uint16_t bypmout : 1;  /*1 Bypass path (output of Boost Stage) to MONO Mixer*/
        uint16_t auxmout : 1;  /*2 Auxiliary to MONO Mixer*/
        uint16_t res1 : 3; /* 5-3   xxxxx*/
        uint16_t moutmt : 1; /*6  MOUT Mute*/
        uint16_t res2 : 9; /*  xxxxx*/
    };
}Nau8814RegMonoMixerControl_t;

/* Reg 0x36
 * 13.10.7. Speaker Gain Control Register
 * */
typedef union {
    uint16_t word;
    struct{
        uint16_t spkgain : 6;  /*bit 0  Speaker Gain*/
        uint16_t spkmt : 1;  /* Speaker Output*/
        uint16_t spkzc : 1;  /* Speaker Gain Control Zero Cross*/
        uint16_t res : 8; /*  xxxxx*/
    };
}Nau8814RegSpkOutVolume_t;

/* Reg 0x31
 * 13.10.5. Output Register
 * */
typedef union{
    uint16_t word;
    struct{
        uint16_t aoutimp : 1;  /*bit 0  Analog Output Resistance*/
        uint16_t tsen : 1;  /* Thermal Shutdown*/
        uint16_t spkbst : 1;  /* Speaker Output Boost Stage*/
        uint16_t moutbst : 1; /*  MONO Output Boost Stage*/
        uint16_t res : 12; /*  xxxxx*/
    };
}Nau8814RegOutputControl_t;

/* Reg 0x2F
 * 13.10.4. ADC Boost Control Registers
 * */
typedef union{
    uint16_t word;
    struct{
        uint16_t auxbstgain : 3;  /*bit 2-0  Auxiliary to Input Boost Stage*/
        uint16_t res1 : 1;  /* xxxx*/
        uint16_t pmicbstgain : 3;  /* MIC+ pin to the input Boost Stage*/
        uint16_t res2 : 1; /*  xxxxx*/
        uint16_t pgabst : 1; /*  Input Boost*/
        uint16_t res3 : 7; /*  xxxxx*/
    };
}Nau8814RegAdcBoost_t;


/* Reg 0x2D
 * 13.10.3. PGA Gain Control Register
 */
typedef union{
    uint16_t word;
    struct {
        uint16_t pgagain : 6; /*bit 5-0  Programmable Gain Amplifier Gain*/
        uint16_t pgamt : 1; /* bit6 Mute Control for PGA*/
        uint16_t pgazc : 1; /* bit7 PGA Zero Cross Enable*/
        uint16_t res : 8; /* xxxxx*/
    };
}Nau8814RegPgaGain_t;

/* Reg 0x2C
 * 13.10.2. Input Signal Control Register
 *
 */
typedef union{
    uint16_t word;
    struct{
        uint16_t pmicpga : 1;  /*bit 0  Input PGA amplifier positive terminal to MIC+ or VREF*/
        uint16_t nmicpga : 1;  /* MICN to input PGA negative terminal*/
        uint16_t auxpga : 1;  /* AUX amplifier output to input PGA signal source*/
        uint16_t auxm : 1;  /* Auxiliary Input mode*/
        uint16_t res1 : 3;  /* xxxx*/
        uint16_t micbiasv : 2;  /* Microphone Bias Voltage Control*/
        uint16_t res2 : 7; /*  xxxxx*/
    };
}Nau8814RegInputControl_t;


/* Reg 0x28
 *
 * 13.10.1. Attenuation Control Register
 * */
typedef union{
    uint16_t word;
    struct{
        uint16_t res1 : 1;  /*bit 0  xxxx*/
        uint16_t spkatt : 1;  /*   speaker  Attenuation*/
        uint16_t moutatt : 1;  /* Mono out   Attenuation*/
        uint16_t res2 : 13; /*  xxxxx*/
    };
}Nau8814RegAttenuationControl_t;

/* Reg 0x27
 * 13.9.2. Phase Lock Loop Control (PLL)*/
typedef union{
    uint16_t word;
    struct{
        uint16_t pllk_8_0 : 9;  /*bit 0  xxxx*/
        uint16_t res : 7; /*  xxxxx*/
    };
}Nau8814RegPllk3_t;

/* Reg 0x26
 * 13.9.2. Phase Lock Loop Control (PLL)
 * */
typedef union{
    uint16_t word;
    struct{
        uint16_t pllk_17_9 : 9;  /*bit 0  xxxx*/
        uint16_t res : 7; /*  xxxxx*/
    };
}Nau8814RegPllk2_t;

/* Reg 0x25
 * 13.9.2. Phase Lock Loop Control (PLL)
 * */
typedef union{
    uint16_t word;
    struct{
        uint16_t pllk_23_18 : 6;  /*bit 0  xxxx*/
        uint16_t res : 10; /*  xxxxx*/
    };
}Nau8814RegPllkl_t;

/* Reg 0x24
 * 13.9.1. PLL Control Registers
 * */
typedef union{
    uint16_t word;
    struct{
        uint16_t plln : 4;  /*bit 0  PLL Integer*/
        uint16_t pllmclk : 1; /*  PLL Clock*/
        uint16_t res : 11; /*  xxxxx*/
    };
}Nau8814RegPllNControl_t;

/* Reg xxxxx
 * 13.8. NOISE GAIN CONTROL REGISTER
 * */
typedef union{
    uint16_t word;
    struct{
        uint16_t alcnth : 3;  /*bit 2-0  Noise Gate Threshold*/
        uint16_t alcnen : 1;  /*3  Noise Gate Enable*/
        uint16_t res : 12;    /*  xxxxx*/
    };
}Nau8814RegNoiseGate_t;


/* Reg 0x22
 * Automatic Level Control
 * 13.7.3. ALC3 REGISTER
 * */
typedef union{
    uint16_t word;
    struct{
        uint16_t alcatk : 4;  /*bit 0  Automatic Level Control ATTACK TIME*/
        uint16_t alcdcy : 4; /*  Automatic Level Control DECAY TIME*/
        uint16_t alcm : 1; /*  Automatic Level Control Mode*/
        uint16_t res : 7; /*  xxxxx*/
    };
}Nau8814RegAlcControl3_t;

/* Reg 0x21
 *
 *ALC2 REGISTER
 * */
typedef union{
    uint16_t word;
    struct{
        uint16_t alcsl : 4;  /*bit 0  ALC TARGET – sets signal level at ADC input*/
        uint16_t alcht : 4; /*  ALC HOLD TIME before gain is increased*/
        uint16_t alczc : 1; /*  ALC Zero Crossing Detect*/
        uint16_t res : 7; /*  xxxxx*/
    };
}Nau8814RegAlcControl2_t;

/* Reg 0x20
 *
 * 13.7. AUTOMATIC LEVEL CONTROL REGISTER
 * */
typedef union{
    uint16_t word;
    struct{
        uint16_t alcmngain : 3;  /*bit 2-0  Minimum Gain*/
        uint16_t alcmxgain : 3; /*5-3  Maximum Gain*/
        uint16_t res1 : 2; /* 7-6 xxxxx*/
        uint16_t alcen : 1; /*  ALC Enable*/
        uint16_t res2 : 7; /*  xxxxx*/
    };
}Nau8814RegAlcControl1_t;

/* Reg xxxxx
 * NOTCH FILTER
 * */
typedef union{
    uint16_t word;
    struct{
        uint16_t nfca1 : 7;  /*bit 0  xxxx*/
        uint16_t res1 : 1; /*  xxxxx*/
        uint16_t nfcu : 1; /*  xxxxx*/
        uint16_t res2 : 7; /*  xxxxx*/
    };
}Nau8814RegNotchFilter1Low_t;

/* Reg 0x32
 * 13.10.6. Speaker Mixer Control Register
 * */
typedef union{
    uint16_t word;
    struct {
        uint16_t dacspk : 1;  /*bit 0  DACSPK DAC to Speaker Mixer*/
        uint16_t bypspk : 1; /* 1 BYPSPK Bypass path (output of Boost stage) to Speaker Mixer*/
        uint16_t res1 : 3; /* 2-4  xxxxx*/
        uint16_t auxspk : 1; /*5  AUXSPK Auxiliary to Speaker Mixer*/
        uint16_t res2 : 10; /*6-15  xxxxx*/
    };
}Nau8814RegSpeakerMixerControl_t;


/* Reg
*NOTCH FILTER
*/
typedef union{
    uint16_t word;
    struct{
        uint16_t nfca1 : 7;  /*bit 0  xxxx*/
        uint16_t res1 : 1; /*  xxxxx*/
        uint16_t nfcu : 1; /*  xxxxx*/
        uint16_t res2 : 7; /*  xxxxx*/
    };
}Nau8814RegNotchFilter1High_t;


/*Reg 0x1c*/
typedef union{
    uint16_t word;
    struct{
        uint16_t nfca0 : 7;  /*bit 0  xxxx*/
        uint16_t res1 : 1; /*  xxxxx*/
        uint16_t nfcu : 1; /*  xxxxx*/
        uint16_t res2 : 7; /*  xxxxx*/
    };
}Nau8814RegNotchFilter0Low_t;

/*  1B*/
typedef union{
    uint16_t word;
    struct{
        uint16_t nfca0 : 7;  /*bit 0  xxxx*/
        uint16_t nfcen : 1; /*  xxxxx*/
        uint16_t nfcu : 1; /*  xxxxx*/
        uint16_t res : 7; /*  xxxxx*/
    };
}Nau8814RegNotchFilter0High_t;


/* Reg 0x19
 * DIGITAL TO ANALOG CONVERTER (DAC) LIMITER
 * */
typedef union{
    uint16_t word;
    struct{
        uint16_t daclimbst : 4;  /*bit 3-0  DAC Limiter volume Boost*/
        uint16_t daclimthl : 3; /*6-4  DAC Limiter Programmable signal threshold level*/
        uint16_t res : 9; /*  xxxxx*/
    };
}Nau8814RegDacLimiter2_t;

/* Reg 0x18
 * DIGITAL TO ANALOG CONVERTER (DAC) LIMITER
 * */
typedef union{
    uint16_t word;
    struct{
        uint16_t daclimatk : 4;  /*bit 3-0  DAC Limiter Attack time*/
        uint16_t daclimdcy : 4; /* 7-4 DAC Limiter Decay time*/
        uint16_t daclimen : 1; /*  DAC Digital Limiter*/
        uint16_t res : 7; /*  xxxxx*/
    };
}Nau8814RegDacLimiter1_t;

/* Reg 0x16*/
typedef union{
    uint16_t word;
    struct{
        uint16_t eq5gc : 5;  /*bit 0  xxxx*/
        uint16_t eq5cf : 2; /*  xxxxx*/
        uint16_t res : 9; /*  xxxxx*/
    };
}Nau8814RegEq5HighCutoff_t;


/* Reg 0x15*/
typedef union{
    uint16_t word;
    struct{
        uint16_t eq4gc : 5;  /*bit 0  xxxx*/
        uint16_t eq4cf : 2; /*  xxxxx*/
        uint16_t res1 : 1; /*  xxxxx*/
        uint16_t eq4bw : 1; /*  xxxxx*/
        uint16_t res2 : 7; /*  xxxxx*/
    };
}Nau8814RegEq4Peak3_t;

/* Reg 0x14*/
typedef union{
    uint16_t word;
    struct{
        uint16_t eq3gc : 5;  /*bit 0  xxxx*/
        uint16_t eq3cf : 2; /*  xxxxx*/
        uint16_t res1 : 1; /*  xxxxx*/
        uint16_t eq3bw : 1; /*  xxxxx*/
        uint16_t res2 : 7; /*  xxxxx*/
    };
}Nau8814RegEq3Peak2_t;

/* Reg 0x13*/
typedef union{
    uint16_t word;
    struct{
        uint16_t eq2gc : 5;  /*bit 0  xxxx*/
        uint16_t eq2cf : 2; /*  xxxxx*/
        uint16_t res1 : 1; /*  xxxxx*/
        uint16_t eq2bw : 1; /*  xxxxx*/
        uint16_t res2 : 7; /*  xxxxx*/
    };
}Nau8814RegEq2Peak1_t;


/* Reg 0x12*/
typedef union{
    uint16_t word;
    struct{
        uint16_t eq1gc : 5;  /*bit 0  xxxx*/
        uint16_t eq1cf : 2; /*  xxxxx*/
        uint16_t res1 : 1; /*  xxxxx*/
        uint16_t eqm : 1; /*  xxxxx*/
        uint16_t res2 : 7; /*  xxxxx*/
    };
}Nau8814RegEq1LowCutoff_t;

/* Reg 0x0E
 * ADC Control Register
 * */
typedef union{
    uint16_t word;
    struct{
        uint16_t adcpl : 1;  /*bit 0  ADC Polarity*/
        uint16_t res1 : 2;  /*2-1 xxxx*/
        uint16_t adcos : 1;  /*3  Over Sample Rate*/
        uint16_t hpf : 3;  /*6-4  High Pass Filter */
        uint16_t hpfam : 1;  /*Audio or Application Mode*/
        uint16_t hpfen : 1;  /*  High Pass Filter Enable*/
        uint16_t res2 : 7; /*  xxxxx*/
    };
}Nau8814RegAdcControl_t;


/* Reg 0x0F
 * 13.3.9. ADC Gain Control Register
 * */
typedef union{
    uint16_t word;
    struct{
        uint16_t adcgain : 8;  /*bit 0  ADC Gain*/
        uint16_t res : 8; /*  xxxxx*/
    };
}Nau8814RegAdcVolume_t;


/*0x0B
 *  Reg DAC Gain Control Register*/
typedef union{
    uint16_t word;
    struct{
        uint16_t dacgain : 8;  /*bit 0  DAC Gain*/
        uint16_t res : 8; /*  xxxxx*/
    };
}Nau8814RegDacVolume_t;


/* Reg xxxxx*/
typedef union{
    uint16_t word;
    struct{
        uint16_t dacpl : 1;  /*bit 0  Polarity Invert*/
        uint16_t res1 : 1; /*  xxxxx*/
        uint16_t automt : 1; /*Auto Mute enable*/
        uint16_t dacos : 1; /*Over Sample Rate*/
        uint16_t deemp : 2; /*5-4 De-emphasis*/
        uint16_t dacmt : 1; /*Soft Mute Enable*/
        uint16_t res2 : 9; /*xxxxx*/
    };
}Nau8814RegDacControl_t;

/* Reg 0x08
 *  13.3.5. GPIO Control Register*/
typedef union{
    uint16_t word;
    struct{
        uint16_t gpiosel : 3;  /*bit2- 0  General Purpose I/O Selection*/
        uint16_t gpiopl : 1; /*3  GPIO Polarity*/
        uint16_t gpiopll : 2; /*5-3 PLL Output Clock Divider*/
        uint16_t res : 10; /*xxxxx*/
    };
}Nau8814RegGpioControl_t;

/* Reg 0x07
 * 13.3.4. Audio Sample Rate Control Register*/
typedef union{
    uint16_t word;
    struct{
        uint16_t sclken : 1;  /*bit 0  Slow Clock Enable*/
        uint16_t smplr : 3; /*3-1  Sample Rate Selection*/
        uint16_t res : 12; /*xxxxx*/
    };
}Nau8814RegClockControl2_t;

/* Reg 0x06
 * 13.3.3. Clock Control Register*/
typedef union{
    uint16_t word;
    struct{
        uint16_t clkioen : 1;  /*bit 0  FRAME and BCLK*/
        uint16_t res1 : 1; /*  xxxxx*/
        uint16_t bclksel : 3; /*4-2   Bit Clock Select*/
        uint16_t mclksel : 3; /*7-5 Master Clock Selection*/
        uint16_t clkm : 1; /*8 Source of Internal Clock*/
        uint16_t res2 : 7; /*xxxxx*/
    };
}Nau8814RegClockControl1_t;

/* Reg 0x05
 * 13.3.2. Audio Interface Companding Control*/
typedef union{
    uint16_t word;
    struct{
        uint16_t addap : 1;  /*bit 0  loopback*/
        uint16_t adccm : 2; /* 1-2 ADC Companding Select*/
        uint16_t daccm : 2; /*3-4  DAC Companding Selection*/
        uint16_t res : 11; /* xxxxx*/
    };
}Nau8814RegCompanding_t;


/* Reg xxxxx*/
typedef union{
    uint16_t word;
    struct{
        uint16_t res1 : 1;  /*bit 0  xxxx*/
        uint16_t adcphs : 1; /*     xxxxx*/
        uint16_t dacphs : 1; /*xxxxx*/
        uint16_t aifmt : 2; /*xxxxx*/
        uint16_t wlen : 2; /*xxxx*/
        uint16_t fsp : 1; /*xxxxx*/
        uint16_t bclkp : 1; /*xxxxx*/
        uint16_t res2 : 7; /*xxxxx*/
    };
}Nau8814RegAudioInterface_t;

/* Reg xxxxx
 *  13.2.2. Power Management 2*/
typedef union{
    uint16_t word;
    struct{
        uint16_t adcen : 1;  /*bit 0  ADC Enable*/
        uint16_t res1 : 1;   /*     xxxxx*/
        uint16_t pgaen : 1; /*2  MIC(+/-) PGA Enable*/
        uint16_t res2 : 1; /*xxxxx*/
        uint16_t bsten : 1; /*4  Input Boost Enable*/
        uint16_t res3 : 11; /*xxxxx*/

    };
}Nau8814RegPowerManagement2_t;

/* Reg 0x03
 * 13.2.3. Power Management 3*/
typedef union{
    uint16_t word;
    struct{
        uint16_t dacen : 1;  /*bit 0  DAC Enable*/
        uint16_t res1 : 1;   /*     xxxxx*/
        uint16_t spkmxen : 1; /*Speaker Mixer Enable*/
        uint16_t moutmxen : 1; /*MONO Mixer Enable*/
        uint16_t res2 : 1; /*xxxxx*/
        uint16_t pspken : 1; /*SPKOUT+ Enable*/
        uint16_t nspken : 1; /*SPKOUT- Enable*/
        uint16_t mouten : 1; /*MOUT Enable*/
        uint16_t res3 : 8; /*xxxxx*/
    };
}Nau8814RegPowerManagement3_t;

/* Reg xxxxx
 * 13.2.1. Power Management 1
 * */
typedef union{
    uint16_t word;
    struct{
        uint16_t refimp : 2;  /*bit 0-1  VREF REFERENCE IMPEDANCE SELECTION*/
        uint16_t iobufen : 1; /*     Unused input/output tie off buffer enable*/
        uint16_t abiasen : 1; /*Analogue amplifier bias control*/
        uint16_t micbiasen : 1; /*Microphone Bias Enable*/
        uint16_t pllen : 1; /*PLL enable*/
        uint16_t auxen : 1; /*AUX input buffer enable*/
        uint16_t res1 : 1; /*xxxxx*/
        uint16_t dcbufen : 1; /*Buffer for DC level shifting Enable*/
        uint16_t res2 : 7; /*xxxxx*/
    };
}Nau8814RegPowerManagement1_t;

/* Reg xxxxx*/
typedef union{
    uint16_t word;
    uint16_t reset;
}Nau8814RegSoftwareReset_t;

/* Reg xxxxx*/
typedef union{
    uint16_t word;

    Nau8814RegSoftwareReset_t SoftwareReset;
    //POWER MANAGEMENT
    Nau8814RegPowerManagement1_t PowerManagement1;
    Nau8814RegPowerManagement2_t PowerManagement2;
    Nau8814RegPowerManagement3_t PowerManagement3;
    //AUDIO CONTROL
    Nau8814RegAudioInterface_t AudioInterface;
    Nau8814RegCompanding_t Companding;
    Nau8814RegClockControl1_t ClockControl1;
    Nau8814RegClockControl2_t ClockControl2;
    Nau8814RegGpioControl_t GpioControl;
    Nau8814RegDacControl_t DacControl;
    Nau8814RegDacVolume_t DacVolume;

    Nau8814RegAdcControl_t AdcControl;
    Nau8814RegAdcVolume_t AdcVolume;
    //EQUALISER
    Nau8814RegEq1LowCutoff_t Eq1LowCutoff;
    Nau8814RegEq2Peak1_t Eq2Peak1;
    Nau8814RegEq3Peak2_t Eq3Peak2;
    Nau8814RegEq4Peak3_t Eq4Peak3;
    Nau8814RegEq5HighCutoff_t Eq5HighCutoff;
//DIGITAL TO ANALOG (DAC) LIMITER
    Nau8814RegDacLimiter1_t DacLimiter1;
    Nau8814RegDacLimiter2_t DacLimiter2;
    //NOTCH FILTER
    Nau8814RegNotchFilter0High_t NotchFilter0High;
    Nau8814RegNotchFilter0Low_t NotchFilter0Low;
    Nau8814RegNotchFilter1High_t NotchFilter1High;
    Nau8814RegNotchFilter1Low_t NotchFilter1Low;
//ALC CONTROL
    Nau8814RegAlcControl1_t AlcControl1;
    Nau8814RegAlcControl2_t AlcControl2;
    Nau8814RegAlcControl3_t AlcControl3;
    Nau8814RegNoiseGate_t NoiseGate;
    //PLL CONTROL
    Nau8814RegPllNControl_t PllNControl;
    Nau8814RegPllkl_t Pllkl;
    Nau8814RegPllk2_t Pllk2;
    Nau8814RegPllk3_t Pllk3;
//INPUT, OUTPUT & MIXER CONTROL
    Nau8814RegAttenuationControl_t AttenuationControl;
    Nau8814RegInputControl_t InputControl;
    Nau8814RegPgaGain_t PgaGain;
    Nau8814RegAdcBoost_t AdcBoost;
    Nau8814RegOutputControl_t OutputControl;

    Nau8814RegSpeakerMixerControl_t SpeakerMixerControl;

    Nau8814RegSpkOutVolume_t SpkOutVolume;
    Nau8814RegMonoMixerControl_t MonoMixerControl;
    //LOW POWER CONTROL

    Nau8814RegPowerManagement4_t PowerManagement4;
    //PCM TIME SLOT & ADCOUT IMPEDANCE OPTION CONTROL
    Nau8814RegTimeSlot_t TimeSlot;
    Nau8814RegAdcOutDrive_t AdcOutDrive;
    //REGISTER ID
    Nau8814RegHighVoltageControl_t HighVoltageControl;
    Nau8814RegAlcEnhancements1_t AlcEnhancements1;
    Nau8814RegAlcEnhancements2_t AlcEnhancements2;
    Nau8814RegAdditionalIfControl_t AdditionalIfControl;
    Nau8814RegPowerTieOffControl_t PowerTieOffControl;
    Nau8814RegAgcP2pDetector_t AgcP2pDetector;
    Nau8814RegAgcPeakDetector_t AgcPeakDetector;
    Nau8814RegControlAndStatus_t ControlAndStatus;
    Nau8814RegOutputTieOffControl_t OutputTieOffControl;
}Nau8814RegUniversal_t;





#endif /* NAU8814_REG_TYPES_H */
