#include "fda801_config.h"

#include "data_utils.h"
#include "gpio_const.h"
#include "common_const.h"
#include "fda801_const.h"
 
const Fda801Config_t Fda801Config[]={
 {.num=FDA801_MAIN,
  .def_i2c_addr=FDA801_ADDRESS1,
  .gpio.en1.port=PORT_A, .gpio.en1.pin=3,
  .gpio.en2.port=PORT_D, .gpio.en2.pin=7,
  .gpio.en3.port=PORT_C, .gpio.en3.pin=0,
  .gpio.mute.port=PORT_C,.gpio.mute.pin=1,
  .gpio.diag.port=PORT_C,.gpio.diag.pin=3,

  .RegCfgDump[0]= {
        .addr=REG_INTERFACE,
        .val.Ib0Addr.digital_input_settings=DIG_IN_SETTINGS_I2S,
        .val.Ib0Addr.pwm_phase=PWM_OUT_OF_PHASE,
        .val.Ib0Addr.pwm_amplifier_clock=PWM_AMP_CLOCK_NOT_DITHERED,
        .val.Ib0Addr.switching_frequency=SWITCH_FREQ_ON_44_1_KHZ_308_7_KHZ,
        .val.Ib0Addr.fs=DIGITAL_INPUT_FRAME_SYN_FREQ_44_1_KHZ,
  },

   .RegCfgDump[1]= {.addr=REG_CR1,       .val.reg_val=0,},
   .RegCfgDump[2]= {.addr=REG_DIAG,      .val.reg_val=0,},
   .RegCfgDump[3]= {.addr=REG_CR2,
                    .val.Ib3Addr.dac_level_ctrl=DAC_LEV_CTRL_LOW,
                    .val.Ib3Addr.mute_timing_setup=MUTE_TIMEING_SETUP_185_MS,

 },
   .RegCfgDump[4]= {.addr=REG_DIAGSEL,   .val.reg_val=0,},

   .RegCfgDump[5]= {.addr=REG_CHN1CNTR,
                    .val.Ib5AddrChannel1Ctrl.ch1_ac_ext_test=SW_OFF,
                    .val.Ib5AddrChannel1Ctrl.ch1_gain_sel=GAIN_SEL_GV1,
                    .val.Ib5AddrChannel1Ctrl.ch1_pwm=SW_OFF,
                    .val.Ib5AddrChannel1Ctrl.ch1_diag=CH_DIAG_LINE_DRIVER,
                    .val.Ib5AddrChannel1Ctrl.ch1_dc_diag=ST_DISABLE,
                    .val.Ib5AddrChannel1Ctrl.ch1_ac_diag=ST_DISABLE,
                    .val.Ib5AddrChannel1Ctrl.ch1_status=CH_STATE_PLAY,
                   },
   .RegCfgDump[6]= {.addr=REG_CHN2CNTR,
                     .val.Ib6AddrChannel2Ctrl.ch2_ac_ext_test=SW_OFF,
                     .val.Ib6AddrChannel2Ctrl.ch2_gain_sel=GAIN_SEL_GV1,
                     .val.Ib6AddrChannel2Ctrl.ch2_pwm=SW_OFF,
                     .val.Ib6AddrChannel2Ctrl.ch2_diag=CH_DIAG_LINE_DRIVER,
                     .val.Ib6AddrChannel2Ctrl.ch2_dc_diag=ST_DISABLE,
                     .val.Ib6AddrChannel2Ctrl.ch2_ac_diag=ST_DISABLE,
                     .val.Ib6AddrChannel2Ctrl.ch2_status=CH_STATE_MUTE,
 },
 .RegCfgDump[7]= {.addr=REG_CHN3CNTR,
                     .val.Ib7AddrChannel3Ctrl.ch3_ac_ext_test=SW_OFF,
                     .val.Ib7AddrChannel3Ctrl.ch3_gain_sel=GAIN_SEL_GV1,
                     .val.Ib7AddrChannel3Ctrl.ch3_pwm=SW_OFF,
                     .val.Ib7AddrChannel3Ctrl.ch3_diag=CH_DIAG_LINE_DRIVER,
                     .val.Ib7AddrChannel3Ctrl.ch3_dc_diag=ST_DISABLE,
                     .val.Ib7AddrChannel3Ctrl.ch3_ac_diag=ST_DISABLE,
                     .val.Ib7AddrChannel3Ctrl.ch3_status=CH_STATE_MUTE,
  },
  .RegCfgDump[8]= {.addr=REG_CHN4CNTR,
                     .val.Ib8AddrChannel4Ctrl.ch4_ac_ext_test=SW_OFF,
                     .val.Ib8AddrChannel4Ctrl.ch4_gain_sel=GAIN_SEL_GV1,
                     .val.Ib8AddrChannel4Ctrl.ch4_pwm=SW_OFF,
                     .val.Ib8AddrChannel4Ctrl.ch4_diag=CH_DIAG_LINE_DRIVER,
                     .val.Ib8AddrChannel4Ctrl.ch4_dc_diag=ST_DISABLE,
                     .val.Ib8AddrChannel4Ctrl.ch4_ac_diag=ST_DISABLE,
                     .val.Ib8AddrChannel4Ctrl.ch4_status=CH_STATE_MUTE,
},

    .RegCfgDump[9]= {.addr=REG_DIAGPHASEDELAYCNTRCH1,  .val.DiagPhaseDelayCtrlCh1.ch1_diag_phase_delay_ctrl=0,},
    .RegCfgDump[10]= {.addr=REG_DIAGPHASEDELAYCNTRCH2, .val.DiagPhaseDelayCtrlCh2.ch2_diag_phase_delay_ctrl=0,},
    .RegCfgDump[12]= {.addr=REG_DIAGPHASEDELAYCNTRCH3, .val.DiagPhaseDelayCtrlCh3.ch3_diag_phase_delay_ctrl=0,},
    .RegCfgDump[11]= {.addr=REG_DIAGPHASEDELAYCNTRCH4,
                      .val.DiagPhaseDelayCtrlCh4.ch4_diag_phase_delay_ctrl=0,
                      .val.DiagPhaseDelayCtrlCh4.i_prot=I_PROT_4_5_A,},
    .RegCfgDump[13]= {.addr=REG_DIGITAL,
        .val.Ib13Addr.watchdog_on_i2sws_signal=WDT_I2S_WS_DISABLE,
        .val.Ib13Addr.cmdpwm_peak=ST_DISABLE,
        .val.Ib13Addr.ac_diag_signal_level=AC_DIAG_STANDART,
        .val.Ib13Addr.digital_mute=DIGITAL_MUTE_DISABLE,
 },
   .RegCfgDump[14]= {.addr=REG_LCFILTERSETUP,
        .val.Ib14Addr.first_setup = FIRST_SETUP_PROG,
        .val.Ib14Addr.lc_filetr_setup=LC_FILT_10UH_3_3_UF_OUT, /*See schematic*/
 },

   .RegCfgDump[15]= {.addr=REG_SENSOR,                .val.reg_val=0,},
   .RegCfgDump[16]= {.addr=REG_THERMALWARNING,        .val.reg_val=0,},
   .RegCfgDump[17]= {.addr=REG_CHN1DCOUT,             .val.reg_val=0,},
   .RegCfgDump[18]= {.addr=REG_CHN2DCOUT,             .val.reg_val=0,},
   .RegCfgDump[19]= {.addr=REG_CHN3DCOUT,             .val.reg_val=0,},
   .RegCfgDump[20]= {.addr=REG_CHN4DCOUT,             .val.reg_val=0,},
   .RegCfgDump[21]= {.addr=REG_CH1CH2ACDIAGRES,       .val.reg_val=0,},
   .RegCfgDump[22]= {.addr=REG_CH3CH4ACDIAGRES,       .val.reg_val=0,},
 },

};

Fda801Handle_t Fda801Instance[]={
 {.num=FDA801_MAIN,}
};

uint32_t fda801_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(Fda801Instance);
    cnt2 = ARRAY_SIZE(Fda801Config);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
