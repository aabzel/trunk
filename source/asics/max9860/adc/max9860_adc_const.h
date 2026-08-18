#ifndef MAX9860_ADC_CONST_H
#define MAX9860_ADC_CONST_H

typedef enum {
    MIC_LEFT = 1,
    MIC_RIGHT = 2,

    MIC_UNDEF = 0,
} MicChannel_t;

/*SDOUT High-Impedance Mode*/
typedef enum {
    // SDOUT is set either high or low after all data bits have been transferred out of the part.
    HIZ_SDOUT_HI_OR_LOW = 0,

    HIZ_SDOUT_HI_IMPEDANCE = 1, // SDOUT goes to a high-impedance state after all data bits have been transferred out of
                                // the part, allowing SDOUT to be shared by other devices.

    HIZ_UNDEF = 2,
} HighImpedanceZ_t;

typedef enum {
    /* ADC Delay Mode  */
    SDOUT_DATA_VALID_ON_FIRST_BCLK_EDGE = 0, // SDOUT data is valid on the first BCLK edge following an LRCLK edge.

    SDOUT_DATA_VALID_ON_SECONDT_BCLK_EDGE = 1, /* SDOUT data is delayed one BCLK cycle so that it is valid on the 2nd
                                                  BCLK edge following an LRCLK edge (I2S-compatible mode).*/
    ADLY_UNDEF = 2,
} AdcDelayMode_t;

/*Table 11. Power Management Register*/
typedef enum {
    ADCEN_OFF = 0, /*Left/right ADC disabled*/
    ADCEN_ON = 1,  /*Left/right ADC enabled*/

    ADCEN_UNDEF = 0,
} AdcEnable_t;

/*Table 10. AGC and Noise Gate Registers*/
typedef enum {
    /* AGC/Noise Gate Signal Source Select  */
    LEFT_ADC_OUTPUT_FOR_AGC = 0, // The left ADC output is used by the AGC and noise gate.
    SUM_ADC_OUTPUTS_FOR_AGC = 1, // The sum of the left and right ADC outputs is used by the AGC and noise gate.

    AGCSRC_UNDEF = 0x2,
} AGCSrc_t;

/*Table 10. AGC and Noise Gate Registers*/
typedef enum {
    /* AGC Release Time. Time taken by the AGC circuit to increase the gain from minimum to maximum  */
    AGCRLS_78_MS = 0,  /*78ms*/
    AGCRLS_156_MS = 1, /*156ms*/
    AGCRLS_312_MS = 2, /*312ms*/
    AGCRLS_625_MS = 3, /*625ms*/
    AGCRLS_1_25_S = 4, /*1.25s*/
    AGCRLS_2_5_S = 5,  /*2.5s*/
    AGCRLS_5_S = 6,    /*5s*/
    AGCRLS_10_S = 7,   /*10s*/

    AGCRLS_UNDEF = 8,
} AGCReleaseTime_t;

/*Table 10. AGC and Noise Gate Registers*/
typedef enum {
    /* AGC Attack Time. The time constant of the AGC gain reduction curve.  */
    AGCATK_3_MS = 0,   /*3ms  */
    AGCATK_12_MS = 1,  /*12ms */
    AGCATK_50_MS = 2,  /*50ms */
    AGCATK_200_MS = 3, /*200ms*/

    AGCATK_UNDEF = 4,
} AGCAttackTime_t;

/*Table 10. AGC and Noise Gate Registers*/
typedef enum {
    /* AGC Hold Time. Time the AGC circuit waits before beginning to increase
    gain when a signal below the threshold is detected.  */
    AGCHLD_AGC_DISABLED = 0, /*AGC disabled */
    AGCHLD_50_MS = 1,        /*50ms         */
    AGCHLD_100_MS = 2,       /*100ms        */
    AGCHLD_400_MS = 3,       /*400ms        */

    AGCHLD_UNDEF = 4,
} AGCHoldTime_t;

/*(page 29) Table 9. Microphone Input Register 0x0C*/
typedef enum {
    /* Left and Right Microphone Preamp Gain.  */
    ADC_PAM_GAIN_DISABLED = 0,   /*Disabled*/
    ADC_PAM_GAIN_0_DB = 1,       /*0*/
    ADC_PAM_GAIN_PLUS_20_DB = 2, /*+20*/
    ADC_PAM_GAIN_PLUS_30_DB = 3, /*+30*/

    ADC_PAM_GAIN_UNDEF = 4, /**/
} AdcPreampGain_t;

typedef enum {
    ABCI_SDOUT_RISING_BCLK = 0,
    ABCI_SDOUT_FALLING_BCLK = 1,

    ABCI_UNDEF = 2,
} AdcBitClkInvert_t;

/* Table 2. Status/Interrupt Registers
 * Noise Gate Attenuation. When the noise gate is enabled these bits indicate the current noise gate attenuation.*/
typedef enum {
    NG_ATT_0_DB = 0,  /*0dB*/
    NG_ATT_1_DB = 1,  /*1dB*/
    NG_ATT_2_DB = 2,  /*2dB*/
    NG_ATT_3_DB = 3,  /*3dB*/
    NG_ATT_6_DB = 4,  /*6dB*/
    NG_ATT_8_DB = 5,  /*8dB*/
    NG_ATT_10_DB = 6, /*10dB*/
    NG_ATT_12_DB = 7, /*12dB*/

    NG_ATT_UNDEF = 8,
} NoiseGateAttenuation_t;

#endif /* MAX9860_ADC_CONST_H */
