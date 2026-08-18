#ifndef MAX9860_REG_TYPES_H
#define MAX9860_REG_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "max9860_const.h"

// Table 2. Status  0x00
typedef union {
    uint8_t byte;
    struct {
        uint8_t res : 5;
        uint8_t ulk : 1; /*Digital PLL Unlock Flag*/
        uint8_t sld : 1; /*Slew Level Detect Flag.*/
        uint8_t cld : 1; /*Clip Detect Flag.*/
    };
} Max9860Reg00InterruptStatus_t;

// Table 2. Gain  0x01
typedef union {
    uint8_t byte;
    struct {
        uint8_t agc : 5; /*AGC Gain. When the AGC is enabled these bits indicate the AGC controlled level to the MIC
                            preamp.*/
        uint8_t ng : 3;  /*Noise Gate Attenuation. When the noise gate is enabled these bits indicate the current noise
                            gate attenuation.*/
    };
} Max9860Reg01Gain_t;

// Table 2. Interrupt Enable 0x02
typedef union {
    uint8_t byte;
    struct {
        uint8_t res : 5;  /**/
        uint8_t iulk : 1; /*Interrupt Enable Digital PLL Unlock*/
        uint8_t isld : 1; /*Interrupt Enable Slew Level Detect*/
        uint8_t icld : 1; /*Interrupt Enable Clip Detect */
    };
} Max9860Reg02IntEnable_t;

// Table 3. System Clock 0x03
typedef union {
    uint8_t byte;
    struct {
        uint8_t f16khz : 1; /*16kHz Mode*/
        uint8_t freq : 2;   /*Integer Clock Mode*/
        uint8_t res1 : 1;   /**/
        uint8_t psclk : 2;  /*MCLK Prescaler*/
        uint8_t res2 : 2;   /**/
    };
} Max9860Reg03SystemClock_t;

// Table 3.Stereo Audio Clock Control 0x04
typedef union {
    uint8_t byte[2];
    uint16_t word;
    struct {
        uint16_t nhi : 15; /*LRCLK Divider*/
        uint16_t pll : 1;  /*PLL Enable */
    };
} Max9860Reg04StereoAudioClockControl_t;

// Table 3.Stereo Audio Clock Control Hight 0x04
typedef union {
    uint8_t byte;

    struct {
        uint8_t nhi : 7; /**/
        uint8_t pll : 1; /*PLL Enable */
    };
} Max9860Reg04StereoAudioClockControlHight_t;

// Table 3.Stereo Audio Clock Control Low 0x05
typedef union {
    uint8_t byte;
    uint8_t nlo; /**/
} Max9860Reg05StereoAudioClockControlLow_t;

// Table 5. Digital Audio Interface Registers 0x06
typedef union {
    uint8_t byte;
    struct {
        uint8_t res : 2;  /*reserved*/
        uint8_t tdm : 1;  /*TDM Mode Select*/
        uint8_t hiz : 1;  /*SDOUT High-Impedance Mode*/
        uint8_t ddly : 1; /*DAC Delay Mode*/
        uint8_t dbci : 1; /*DAC BCLK Invert (must be set to ABCI)*/
        uint8_t wci : 1;  /*LRCLK Invert*/
        uint8_t mas : 1;  /*Master Mode*/
    };
} Max9860Reg06If1_t;

// Table 5. Digital Audio Interface Registers 0x07
typedef union {
    uint8_t byte;
    struct {
        uint8_t bsel : 3; /*BCLK Select*/
        uint8_t st : 1;   /*Stereo Enable*/
        uint8_t adly : 1; /*ADC Delay Mode*/
        uint8_t abci : 1; /*ADC BCLK Invert (must be set to DBCI)*/
        uint8_t res : 2;  /**/
    };
} Max9860Reg07If2_t;

// Table 6. Voice Filter Digital Filter Registers
typedef union {
    uint8_t byte;
    struct {
        uint8_t dvflt : 4; /*DAC Voice Filter Frequency Select. See Table 7.*/
        uint8_t avflt : 4; /*ADC Voice Filter Frequency Select. See Table 7.*/
    };
} Max9860Reg08DigitalFilter_t;

// Table 8. Digital Level Control Registers
typedef union {
    uint8_t byte;
    uint8_t dva; /*DAC Level Adjust*/

} Max9860Reg09DacLevAdj_t;

// Table 8. 0x0A ADC Output Levels
typedef union {
    uint8_t byte;
    struct {
        uint8_t adcll : 4; /*Left ADC Output Level*/
        uint8_t adcrl : 4; /*Right ADC Output Level*/
    };
} Max9860Reg0AAdcOutLevel_t;

// Table  0x0B DAC Gain and Sidetone
typedef union {
    uint8_t byte;
    struct {
        uint8_t dvst : 5; /*Sidetone  Sets the level of left ADC output mixed into the DAC.*/
        uint8_t dvg : 2;  /*DAC Gain  The gain set by DVG adds to the level set by DVA*/
        uint8_t res : 1;  /* */
    };
} Max9860Reg0BDacGainSidetone_t;

/*Microphone Gain */
typedef union {
    uint8_t byte;
    struct {
        uint8_t pgam : 5; /*Left and Right Microphone PGA */
        uint8_t pam : 2;  /*Left and Right Microphone Preamp Gain */
        uint8_t res : 1;  /* */
    };
} Max9860Reg0CMicrophoneGain_t;

/* Microphone AGC
 * Table 10. AGC and Noise Gate Registers
 */
typedef union {
    uint8_t byte;
    struct {
        uint8_t agchld : 2; /*AGC Hold Time */
        uint8_t agcatk : 2; /*AGC Attack Time */
        uint8_t agcrls : 3; /*AGC Release Time */
        uint8_t agcsrc : 1; /*AGC/Noise Gate Signal Source Select */
    };
} Max9860Reg0EMicrophoneAgc_t;

/*Noise Gate,Microphone AGC
 * Table 10. AGC and Noise Gate Registers
 * */
typedef union {
    uint8_t byte;
    struct {
        uint8_t agcth : 4; /* AGC Signal Threshold*/
        uint8_t anth : 4;  /* Noise Gate Threshold */
    };
} Max9860Reg0FNoiseGateMicAgc_t;

/*System Shutdown*/
typedef union {
    uint8_t byte;
    struct {
        uint8_t adcren : 1; /* ADC Right Enable */
        uint8_t adclen : 1; /* ADC Left  Enable */
        uint8_t res1 : 1;   /* */
        uint8_t dacen : 1;  /*DAC Enable */
        uint8_t res2 : 3;   /* */
        uint8_t shdn : 1;   /*Active-Low Software Shutdown */
    };
} Max9860Reg10SysShutdown_t;

typedef union {
    uint8_t byte;
    Max9860Reg00InterruptStatus_t Reg00Status;                                    /**/
    Max9860Reg01Gain_t Reg01Gain;                                                 /**/
    Max9860Reg02IntEnable_t Reg02IntEnable;                                       /**/
    Max9860Reg03SystemClock_t Reg03SystemClock;                                   /**/
    Max9860Reg04StereoAudioClockControlHight_t Reg04StereoAudioClockControlHight; /**/
    Max9860Reg05StereoAudioClockControlLow_t Reg05StereoAudioClockControlLow;     /**/
    Max9860Reg06If1_t Reg06If1;                                                   /**/
    Max9860Reg07If2_t Reg07If2;                                                   /**/
    Max9860Reg08DigitalFilter_t Reg08DigitalFilter;                               /**/
    Max9860Reg09DacLevAdj_t Reg09DacLevAdj;                                       /**/
    Max9860Reg0AAdcOutLevel_t Reg0AAdcOutLevel;                                   /**/
    Max9860Reg0BDacGainSidetone_t Reg0BDacGainSidetone;                           /**/
    Max9860Reg0CMicrophoneGain_t Reg0CMicrophoneGain;                             /**/
    Max9860Reg0EMicrophoneAgc_t Reg0EMicrophoneAgc;                               /**/
    Max9860Reg0FNoiseGateMicAgc_t Reg0FNoiseGateMicAgc;                           /**/
    Max9860Reg10SysShutdown_t Reg10SysShutdown;                                   /**/
} Max9860RegUniversal_t;

#endif /* MAX9860_REG_TYPES_H */
