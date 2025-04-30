#include "max9860_config.h"

#ifdef HAS_I2C
#include "i2c_drv.h"
#endif

#include "data_utils.h"
#include "max9860_types.h"

#if !defined(HAS_MAX9860_I2S_MASTER) && !defined(HAS_MAX9860_I2S_SLAVE)
#error "some MAX9860 I2S role must be defined!"
#endif


const Max9860Config_t Max9860Config = {
    .dac_en = true,
    .adc_left_en = false,
    .adc_right_en = false,
    .i2c_num = 1,
    .i2s_num = 0,
    .dac_attenuation = -5, /*-90...+3*/
    .dac_gain = MAX9860_DAC_GAIN_18, /*0 +6 +12 +18*/
    .mclk_hz = 12288000,
    .lrclk_hz = 48000,
    .i2s_role = MAX9860_I2S_ROLE_SLAVE,
    .interface = MAX_IF_I2S,
    .stereo = false,
};

Max9860Item_t Max9860Item = {0};

Max9860RegVal_t Max9860RegVal[MAX9860_REG_CNT] = {
    {
        .addr = MAX9860_REG_INTERRUPT_STATUS,
        .value.byte = 0x00,
    },
    {
        .addr = MAX9860_REG_MICROPHONE_NG_AGC_READBACK,
        .value.byte = 0x00,
    },
    {
        .addr = MAX9860_REG_INTERRUPT_ENABLE,
        .value.byte = 0x00,
    },
    {
        .addr = MAX9860_REG_SYSTEM_CLOCK,
        .value.byte = 0x00,
    },
    {
        .addr = MAX9860_REG_STEREO_AUDIO_CLOCK_CONTROL_HIGH,
        .value.byte = 0x00,
    },
    {
        .addr = MAX9860_REG_STEREO_AUDIO_CLOCK_CONTROL_LOW,
        .value.byte = 0x00,
    },
    {
        .addr = MAX9860_REG_INTERFACE1,
        .value.byte = 0x00,
    },
    {
        .addr = MAX9860_REG_INTERFACE2,
        .value.byte = 0x00,
    },
    {
        .addr = MAX9860_REG_VOICE_FILTER,
        .value.byte = 0x00,
    },
    {
        .addr = MAX9860_REG_DAC_ATTENUATION,
        .value.byte = 0x00,
    },
    {
        .addr = MAX9860_REG_ADC_OUTPUT_LEVELS,
        .value.byte = 0x00,
    },
    {
        .addr = MAX9860_REG_DAC_GAIN_AND_SIDETONE,
        .value.byte = 0x00,
    },
    {
        .addr = MAX9860_REG_MICROPHONE_GAIN,
        .value.byte = 0x00,
    },
    {
        .addr = MAX9860_REG_RESERVED,
        .value.byte = 0x00,
    },
    {
        .addr = MAX9860_REG_MICROPHONE_AGC,
        .value.byte = 0x00,
    },
    {
        .addr = MAX9860_REG_NOISE_GATEMICROPHONE_AGC,
        .value.byte = 0x00,
    },
    {
        .addr = MAX9860_REG_SYSTEM_SHUTDOWN,
        .value.byte = 0x00,
    },
    {
        .addr = MAX9860_REG_REVISION_CODE,
        .value.byte = 0x00,
    },
};

const Max9860RegVal_t Max9860RegValConfigLUT[] = {

    {
        .addr = MAX9860_REG_INTERRUPT_ENABLE,
        .value.Reg02IntEnable =
            {
                .iulk = 1, /*Interrupt Enable Digital PLL Unlock*/
                .isld = 1, /*Interrupt Enable Slew Level Detect*/
                .icld = 1, /*Interrupt Enable Clip Detect */
            },
    },

    {
        .addr = MAX9860_REG_SYSTEM_CLOCK,
        .value.Reg03SystemClock =
            {
                .f16khz = 0,                     /*16kHz Mode*/
                .freq = 1,                       /*Integer Clock Mode*/
                .psclk = PSCLK_MCLK_10MHZ_20MHZ, /*MCLK Prescaler*/
            },
    },

    {
        .addr = MAX9860_REG_STEREO_AUDIO_CLOCK_CONTROL_HIGH,
        .value.Reg04StereoAudioClockControlHight =
            {
                .nhi = 0x62, /**/
                .pll = 1, /*PLL Enable */
            },
    },

    {
        .addr = MAX9860_REG_STEREO_AUDIO_CLOCK_CONTROL_LOW,
        .value.Reg05StereoAudioClockControlLow =
            {
                .nlo = 0x4E, /*LRCLK Divider*/
            },
    },

    {
        .addr = MAX9860_REG_INTERFACE1,
        .value.Reg06If1 =
            {
                .tdm = 0,  /*TDM Mode Select*/
                .hiz = 0,  /*SDOUT High-Impedance Mode*/
                .ddly = 1, /*DAC Delay Mode*/
                .dbci = 0, /*DAC BCLK Invert (must be set to ABCI)*/
                .wci = 0,  /*LRCLK Invert*/
                .mas = 0,  /*Master Mode*/
            },
    },

    {
        .addr = MAX9860_REG_INTERFACE2,
        .value.Reg07If2 =
            {
                .bsel = 0, /*BCLK Select*/
                .st = 1,   /*Stereo Enable*/
                .adly = 1, /*ADC Delay Mode*/
                .abci = 0, /*ADC BCLK Invert (must be set to DBCI)*/
            },
    },

    {
        .addr = MAX9860_REG_VOICE_FILTER,
        .value.Reg08DigitalFilter =
            {
                .dvflt = 0, /*DAC Voice Filter Frequency Select. See Table 7.*/
                .avflt = 0, /*ADC Voice Filter Frequency Select. See Table 7.*/
            },
    },

    {
        .addr = MAX9860_REG_DAC_ATTENUATION,
        .value.Reg09DacLevAdj =
            {
                .dva = 0, /*DAC Level Adjust*/
            },
    },

    {
        .addr = MAX9860_REG_ADC_OUTPUT_LEVELS,
        .value.Reg0AAdcOutLevel =
            {
                /*Left and Right ADC Output Level*/
                .adcll = 0, /*Left ADC Output Level*/
                .adcrl = 0, /*Right ADC Output Level*/
            },
    },

    {
        .addr = MAX9860_REG_DAC_GAIN_AND_SIDETONE,
        .value.Reg0BDacGainSidetone =
            {
                .dvst = 0, /*Sidetone  Sets the level of left ADC output mixed into the DAC.*/
                .dvg = DAC_GAIN_18,  /*DAC Gain  The gain set by DVG adds to the level set by DVA*/
            },
    },

    {
        .addr = MAX9860_REG_MICROPHONE_GAIN,
        .value.Reg0CMicrophoneGain =
            {
                .pgam = 0x13, /*Left and Right Microphone PGA */
                .pam = 0,  /*Left and Right Microphone Preamp Gain */
            },
    },

    {
        .addr = MAX9860_REG_MICROPHONE_AGC,
        .value.Reg0EMicrophoneAgc =
            {
                .agchld = 0, /*AGC Hold Time */
                .agcatk = 0, /*AGC Attack Time */
                .agcrls = 0, /*AGC Release Time */
                .agcsrc = 0, /*AGC/Noise Gate Signal Source Select */
            },
    },

    {
        .addr = MAX9860_REG_NOISE_GATEMICROPHONE_AGC,
        .value.Reg0FNoiseGateMicAgc =
            {
                .agcth = 0, /* AGC Signal Threshold*/
                .anth = 0,  /* Noise Gate Threshold */
            },
    },

    {
        .addr = MAX9860_REG_SYSTEM_SHUTDOWN,
        .value.Reg10SysShutdown =
            {
                .adcren = 0, /* ADC Right Enable */
                .adclen = 0, /* ADC Left  Enable */
                .dacen = 1,  /*DAC Enable */
                .shdn = 1,   /*Active-Low Software Shutdown */
            },
    },
};


uint32_t max9860_get_config_cnt(void) {
    uint8_t cnt = 0;
    cnt = ARRAY_SIZE(Max9860RegValConfigLUT);
    return cnt;
}
