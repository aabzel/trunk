#ifndef MAX9860_DAC_CONST_H
#define MAX9860_DAC_CONST_H

#define DVST_MAX 0x1F

/*(page 27)  DAC Gain
 * The gain set by DVG adds to the level set by DVA.
 * Table 8. Digital Level Control Registers
 **/
typedef enum {
    DAC_GAIN_0 = 0,
    DAC_GAIN_6 = 1,
    DAC_GAIN_12 = 2,
    DAC_GAIN_18 = 3,

    DAC_GAIN_UNDEF = 4,
} DacGainCode_t;

/*DAC BCLK Invert (must be set to ABCI) DBCI*/
typedef enum {
    /* ADC BCLK Invert (must be set to DBCI)  */
    // SDOUT is valid on the rising edge of BCLK and transitions immediately after the rising edge.
    DBCI_SDOUT_VALID_ON_BCLK_RISING_EDGE = 0,

    // SDOUT is valid on the falling edge of BCLK and transitions immediately after the falling edge.
    DBCI_SDOUT_VALID_ON_BCLK_FALLING_EDGE = 1,

    DBCI_UNDEF = 2,
} DacBitClkInvert_t;

/*DDLY DAC Delay Mode*/
typedef enum {
    DDLY_1ST_BCLK = 0, // SDIN data is latched on the first BCLK edge following an LRCLK edge.
    DDLY_2ND_BCLK = 1, // SDIN data is assumed to be delayed one BCLK cycle so that it is latched on the 2nd BCLK edge
                       // following an LRCLK edge (I2S-compatible mode).
    DDLY_UNDEF = 2,
} DacDelay_t;

/*(page 27) The gain set by DVG adds to the level set by DVA.
 * Table 8. Digital Level Control Registers
 **/
typedef enum {
    MAX9860_DAC_GAIN_0 = 0,
    MAX9860_DAC_GAIN_6 = 6,
    MAX9860_DAC_GAIN_12 = 12,
    MAX9860_DAC_GAIN_18 = 18,

    MAX9860_DAC_GAIN_UNDEF = 100,
} Max9860DacLegalGain_t;

typedef enum {
    MAX_STEREO_OFF = 0, /*The interface transmits and receives only one channel of data. If right record path is
                        enabled, no data from this channel is transmitted. */

    MAX_STEREO_ON = 1, /*The interface operates in stereo. The left and right incoming data are summed to mono and then
   routed to the DAC. The summed data is divided by 2 to prevent overload. Both the left and right
   record signals are transmitted.*/

    MAX_STEREO_UNDEF = 4,
} MaxStereo_t;

/*Table 11. Power Management Register*/
typedef enum {
    DACEN_OFF = 0, /*DAC disabled*/
    DACEN_ON = 1,  /*DAC enabled*/

    DACEN_UNDEF = 2,
} DacEn_t;

#endif /* MAX9860_DAC_CONST_H */
