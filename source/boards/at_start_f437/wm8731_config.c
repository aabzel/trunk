#include "wm8731_config.h"


//#include "c_defines_generated.h"
#include "data_utils.h"


#if !defined(HAS_WM8731_I2S_MASTER) && !defined(HAS_WM8731_I2S_SLAVE)
#error "some WM8731 I2S role must be defined!"
#endif


#if defined(HAS_WM8731_I2S_MASTER) && defined(HAS_WM8731_I2S_SLAVE)
#error "WM8731 I2S role contradiction!"
#endif


#if defined(HAS_WM8731_USB_MODE) && defined(HAS_WM8731_NORMAL_MODE)
#error "WM8731 I2S clock contradiction!"
#endif

#if !defined(HAS_WM8731_USB_MODE) && !defined(HAS_WM8731_NORMAL_MODE)
#error "some WM8731 I2S clock must be defined!"
#endif


static const Wm8731RegConfig_t Wm8731RegisterConfiguration[] = {
    {.reg_addr = 0x00, .value.LeftLineInCtrl.linvol = 31, .value.LeftLineInCtrl.lin_mute = MUTE_ON},
    {
        .reg_addr = 0x01,
        .value.RightLineInCtrl.rinvol = 31,
        .value.RightLineInCtrl.rin_mute = MUTE_ON,
    },
    {.reg_addr = 0x02,
     .value =
         {
             .LeftHeadOutCtrl.lhpvol = 127,
             .LeftHeadOutCtrl.lzcen = 1,
         }},
    {.reg_addr = 0x03,
     .value =
         {
             .RightHeadOutCtrl.rhpvol = 127,
             .RightHeadOutCtrl.rzcen = 1,
         }},
    /*Analogue Audio Path Control*/
    {
        .reg_addr = 0x04,
        .value.AnalogAudioPathCtrl.mic_boost = MIC_IN_BOOST_OFF,
        .value.AnalogAudioPathCtrl.mute_mic = MUTE_OFF,
        .value.AnalogAudioPathCtrl.insel = ADC_IN_SEL_MIC,
        .value.AnalogAudioPathCtrl.by_pass = BYPASS_SW_OFF,
        .value.AnalogAudioPathCtrl.dac_sel = DAC_SEL_ON,
        .value.AnalogAudioPathCtrl.side_tone = SIDE_TONE_OFF,
        .value.AnalogAudioPathCtrl.sideatt = SIDE_TONE_ATTEN_MIN_6_DB,
    },
    {
        .reg_addr = WM8731_REG_APDIGI,
        .value.DigitalAudioPathCtrl.adchpd = ADC_HI_PASS_FILT_OFF, /*Must be off! ADC_HI_PASS_FILT_OFF*/
        .value.DigitalAudioPathCtrl.deemp = DE_EMPH_48000HZ,
        .value.DigitalAudioPathCtrl.dacmute = DAC_SW_MUTE_OFF,
        .value.DigitalAudioPathCtrl.hpor = DC_OFFSET_CLEAR,
    },
    {.reg_addr = 0x06,                  /*Power Down Control*/
     .value.PowerDownCtrl.lineinpd = 0, /**/
     .value.PowerDownCtrl.micpd = 0,    /**/
     .value.PowerDownCtrl.adcpd = 0,    /**/
     .value.PowerDownCtrl.dacpd = 0,    /**/
     .value.PowerDownCtrl.outpd = 0,    /**/
     .value.PowerDownCtrl.oscpd = 0,    /**/
     .value.PowerDownCtrl.clkoutpd = 0, /**/
     .value.PowerDownCtrl.poweroff = 0,
     /**/},
    {
        .reg_addr = 0x07, /*Digital Audio Interface Format*/
        .value.DigitalAudioIfCtrl.format = FMT_I2S,
        .value.DigitalAudioIfCtrl.iwl = AUD_BIT_16,                           // AUD_BIT_16 AUD_BIT_24 AUD_BIT_32
        .value.DigitalAudioIfCtrl.lrp = I2S_DAC_PHASE_RIGHT_CH_DAC_DACLRC_HI, /*???*/
        .value.DigitalAudioIfCtrl.lrswap = DAC_LR_CLK_LEFT,
#ifdef HAS_WM8731_I2S_MASTER
        .value.DigitalAudioIfCtrl.ms = BUS_MODE_MASTER,
#endif
#ifdef HAS_WM8731_I2S_SLAVE
        .value.DigitalAudioIfCtrl.ms = BUS_MODE_SLAVE,
#endif
        .value.DigitalAudioIfCtrl.bclkinv = BIT_CLOCK_NORMAL,
    },
    {
        .reg_addr = 0x08,
#ifdef HAS_WM8731_USB_MODE
        .value.SamplingCtrl.usb_normal = MODE_USB,
        .value.SamplingCtrl.bosr = USB_BASE_OVER_SAMPLE_RATE_250FS,
        .value.SamplingCtrl.sr = WM_USB_SAMPLE_RATE_48000_HZ,
        .value.SamplingCtrl.clkidiv2 = CORE_CLK_MCLK,
        .value.SamplingCtrl.clkodiv2 = CLK_OUT_CORE_CLK,
#endif /*HAS_WM8731_USB_MODE*/

#ifdef HAS_WM8731_NORMAL_MODE
        .value.SamplingCtrl.usb_normal = MODE_NORMAL,
        .value.SamplingCtrl.bosr = NORM_BASE_OVER_SAMPLE_RATE_256FS,
        .value.SamplingCtrl.sr = WM_NORM_SAMPLE_RATE_48000_HZ,
        .value.SamplingCtrl.clkidiv2 = CORE_CLK_MCLK,
        .value.SamplingCtrl.clkodiv2 = CLK_OUT_CORE_CLK,
#endif /*HAS_WM8731_NORMAL_MODE*/
    },

    {
        .reg_addr = 0x09,
        .value.ActiveCtrl.active = 1,
    },

    /*    {.reg_addr=0x0F, .ResetCtrl.reset=0xFF,},*/
};

const Wm8731Config_t Wm8731Config[] = {
    {
        .num = 1,
        .chip_addr = WM8731_7BIT_ADDRESS,
        .i2c_num = 2,
        .i2s_tx_num = 2,
        .i2s_rx_num = 5,
        .left = 1,
        .RegArray = Wm8731RegisterConfiguration,
        .right = 1,
        .reg_cnt = ARRAY_SIZE(Wm8731RegisterConfiguration),
        .valid = true,
    }
};

Wm8731Handle_t Wm8731Instance[] = {
    {
        .num = 1,
        .valid = true,
    }
};



uint32_t wm8731_get_cnt(void) {
    uint8_t cnt = 0;
    cnt = ARRAY_SIZE(Wm8731Config);
    return cnt;
}
