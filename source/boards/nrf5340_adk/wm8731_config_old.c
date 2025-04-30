#include "wm8731_config.h"

#include "i2c_drv.h"
#include "wm8731_const.h"
#include "data_utils.h"

const Wm8731RegConfig_t Wm8731RegConfigLut[]={
    {.reg_addr=0x00, .value.LeftLineInCtrl.linvol=31, 
                     .value.LeftLineInCtrl.lin_mute=MUTE_ON},
    {.reg_addr=0x01, .value.RightLineInCtrl.rinvol=31, 
                     .value.RightLineInCtrl.rin_mute=MUTE_ON,},
    {.reg_addr=0x02, .value.LeftHeadOutCtrl.lhpvol=127,
                     .value.LeftHeadOutCtrl.lzcen=0,},
    {.reg_addr=0x03, .value.RightHeadOutCtrl.rhpvol=127,
                     .value.RightHeadOutCtrl.rzcen=0,},
    {.reg_addr=0x04, .value.AnalogAudioPathCtrl.mic_boost=MIC_IN_BOOST_OFF,
                     .value.AnalogAudioPathCtrl.mute_mic=MUTE_OFF,
                     .value.AnalogAudioPathCtrl.insel=ADC_IN_SEL_MIC,
                     .value.AnalogAudioPathCtrl.by_pass=BYPASS_SW_OFF,
                     .value.AnalogAudioPathCtrl.dac_sel=DAC_SEL_ON,
                     .value.AnalogAudioPathCtrl.side_tone=SIDE_TONE_OFF,
                     .value.AnalogAudioPathCtrl.sideatt=0,},
    {.reg_addr=WM8731_REG_APDIGI, .value.DigitalAudioPathCtrl.adchpd=ADC_HI_PASS_FILT_OFF,
                     .value.DigitalAudioPathCtrl.deemp=DE_EMPH_OFF,
                     .value.DigitalAudioPathCtrl.dacmu=DAC_SW_MUTE_OFF,
                     .value.DigitalAudioPathCtrl.hpor=DC_OFFSET_CLEAR, },
    {.reg_addr=0x06, .value.PowerDownCtrl.lineinpd=0,/**/
                     .value.PowerDownCtrl.micpd=0,   /**/
                     .value.PowerDownCtrl.adcpd=0,   /**/
                     .value.PowerDownCtrl.dacpd=0,   /**/
                     .value.PowerDownCtrl.outpd=0,   /**/
                     .value.PowerDownCtrl.oscpd=0,   /**/
                     .value.PowerDownCtrl.clkoutpd=0,/**/
                     .value.PowerDownCtrl.poweroff=0,/**/   },
    {.reg_addr=0x07, .value.DigitalAudioIfCtrl.format=FMT_I2S,
                     //.value.DigitalAudioIfCtrl.iwl=AUD_BIT_32,
                     .value.DigitalAudioIfCtrl.iwl=AUD_BIT_24,
                     .value.DigitalAudioIfCtrl.lrp=I2S_DAC_PHASE_RIGHT_CH_DAC_DACLRC_HI,
                     .value.DigitalAudioIfCtrl.lrswap=DAC_LR_CLK_RIGHT,
                     .value.DigitalAudioIfCtrl.ms=BUS_MODE_SLAVE,
                     .value.DigitalAudioIfCtrl.bclkinv=BIT_CLOCK_NORMAL, },
    {.reg_addr=0x08, .value.SamplingCtrl.usb_normal=0,
                     .value.SamplingCtrl.bosr=BASE_OVER_SAMPLE_RATE_256FS,
                     .value.SamplingCtrl.sr=SAMPLE_RATE_48000_HZ,
                     .value.SamplingCtrl.clkidiv2=0,
                     .value.SamplingCtrl.clkodiv2=0,    },
    {.reg_addr=0x09, .value.ActiveCtrl.active=1,},
    
    /*    {.reg_addr=0x0F, .ResetCtrl.reset=0xFF,},*/
};

Wm8731RegConfig_t Wm8731RegConfig[10];

uint32_t wm8731_get_config_cnt(void){
    uint8_t cnt=0;
    uint8_t cnt1 = ARRAY_SIZE(Wm8731RegConfig);
    uint8_t cnt2 = ARRAY_SIZE(Wm8731RegConfigLut);
    if(cnt1==cnt2){
        cnt=cnt1;
    }
    return cnt;
}


