#ifndef FDA801_TYPES_H
#define FDA801_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif
#include "fda801_const.h"

//Table 13. IB0-ADDR:
typedef union {
    uint8_t reg_val;
    struct{
        uint8_t pwm_phase :1;/*PWM phase*/
        uint8_t pwm_amplifier_clock :1;/*PWM amplifier clock*/
        uint8_t switching_frequency :2;/*Switching frequency (with I2S frequency range 35-50kHz), expressed in kHz*/
        uint8_t fs :2;/*Digital input frame sync frequency (Fs):*/
        uint8_t digital_input_settings :2;/*Digital input settings:*/
    };
}Fda801RegInterface_t;

//Table 14. IB1-ADDR: I0000001
typedef union {
    uint8_t reg_val;
    struct{
    	uint8_t output_offset_detector:1;       /**/
        uint8_t input_offset_detector:1;       /**/
		uint8_t high_pass_in_the_dac:1;         /**/
		uint8_t low_radiation_function:1;       /**/
		uint8_t low_battery_mute_and_uvlo:1;    /**/
		uint8_t noise_gate:1;                   /**/
		uint8_t ch3_and_ch4_operation:1;        /**/
		uint8_t ch1_and_ch2_operation:1;        /**/
    };
}Fda801RegIb1Addr_t;

//Table 15. IB2-ADDR: I0000010
typedef union {
    uint8_t reg_val;
    struct{
    	uint8_t clipping_information:1;
		uint8_t output_offset_information:1;
		uint8_t input_offset_information:1;
		uint8_t fault_information:1;
		uint8_t temperature_warning_information: 3;
		uint8_t res:1;
    };
}Fda801RegIb2Addr_t;

//Table 16. IB3-ADDR: I0000011
typedef union {
    uint8_t reg_val;
    struct{
         uint8_t res: 1;
         uint8_t dac_level_ctrl: 2;
	 	 uint8_t cmc_fully_differential :1 ;
	 	 uint8_t power_diag_sel: 1 ;
         uint8_t low_side_power_control :1 ;
         uint8_t mute_timing_setup: 2;
    };
}Fda801RegIb3Addr_t;

//Table 17. IB4-ADDR: â€œI0000100â€�
typedef union {
    uint8_t reg_val;
    struct{
    	uint8_t res :4;
    	uint8_t diag_hold_time_sel :2;
    	uint8_t diag_ramp_time_sel :2;
    };
}Fda801RegIb4Addr_t;



typedef union {
    uint8_t reg_val;
    struct{
        uint8_t state:1;     /*0 BitPlay/Mute*/
        uint8_t load_open:1;  /*1 Bit*/
        uint8_t short_gnd:1;  /*2 Bit*/
        uint8_t short_vcc:1;  /*3 Bit*/
        uint8_t load_short:1; /*4 Bit*/
        uint8_t overcurrent:1;/*5 Bit*/
        uint8_t diag_valid:1; /*6 Bit*/
        uint8_t operation:1;  /*7 Bit*/
    };
}Fda801RegChannelDCOutputs_t;


#define FDA801_REG_CHANNEL_CTRL_T(CHAN)                 \
    struct{                                             \
        uint8_t CHAN##_status:1;       /*0 Play/Mute*/  \
        uint8_t CHAN##_ac_diag:1;      /*1 */           \
        uint8_t CHAN##_dc_diag:1;      /*2 */           \
        uint8_t CHAN##_diag:1;         /*3 Speaker or Line Driver Diagnostic*/ \
        uint8_t CHAN##_pwm:1;          /*4 */           \
        uint8_t CHAN##_gain_sel:2;     /*5-6 Gain Selection*/ \
        uint8_t CHAN##_ac_ext_test:1;  /*7 */           \
    };


//Table 18 Channel 1 controls
//Table 19 Channel 2 controls
//Table 20 Channel 3 controls
//Table 21 Channel 4 controls
typedef union {
    uint8_t reg_val;
    FDA801_REG_CHANNEL_CTRL_T(chx)
}Fda801RegChannelCtrl_t;

//Table 18. IB5-ADDR: I0000101  Channel 1 controls
typedef union xFda801RegIb5AddrChannel1Ctrl_t{
    uint8_t reg_val;
    FDA801_REG_CHANNEL_CTRL_T(ch1)
}Fda801RegChannel1Ctrl_t;

//Table 19. IB6-ADDR: I000011 Channel 2 controls
typedef union xFda801RegIb6Addr_t{
    uint8_t reg_val;
    FDA801_REG_CHANNEL_CTRL_T(ch2)
}Fda801RegChannel2Ctrl_t;

//Table 20. IB7-ADDR: I0000111  Channel 3 controls
typedef union xFda801RegIb7Addr_t{
    uint8_t reg_val;
    FDA801_REG_CHANNEL_CTRL_T(ch3)
}Fda801RegChannel3Ctrl_t;

//Table 21. IB8-ADDR: I0001000 Channel 4 controls
typedef union xFda801RegIb8Addr_t{
    uint8_t reg_val;
    FDA801_REG_CHANNEL_CTRL_T(ch4)
}Fda801RegChannel4Ctrl_t;

//Table 22. IB9-ADDR: I0001001
typedef union {
    uint8_t reg_val;
    struct{
    	uint8_t diag_phase_delay_ctrl:6;
		uint8_t additive_contribution: 1;
		uint8_t pll_clock: 1;
    };
}Fda801PhaseDelayCtrl_t;

#define FDA801PHASE_DELAY_CTRL(CHX) uint8_t CHX##_diag_phase_delay_ctrl:6;

//Table 22. IB9-ADDR: I0001001
typedef union xFda801RegIb9Addr_t{
    uint8_t reg_val;
    struct{
        FDA801PHASE_DELAY_CTRL(ch1)
        uint8_t res:2;
    };
}Fda801RegDiagPhaseDelayCtrlCh1_t;

//Table 23. IB10-ADDR: I0001010
typedef union xFda801RegIb10Addr_t{
    uint8_t reg_val;
    struct{
        FDA801PHASE_DELAY_CTRL(ch2)
        uint8_t res:2;
    };
}Fda801RegDiagPhaseDelayCtrlCh2_t;

//Table 24. IB11-ADDR: I0001011
typedef union {
    uint8_t reg_val;
    struct{
        FDA801PHASE_DELAY_CTRL(ch3)
        uint8_t additive_contribution:1;
        uint8_t pll_clock_proc_spread:1;
    };
}Fda801RegDiagPhaseDelayCtrlCh3_t;

//Table 25. IB12-ADDR: I0001100
typedef union xFda801RegIb12Addr_t{
    uint8_t reg_val;
    struct{
        FDA801PHASE_DELAY_CTRL(ch4)
		uint8_t i_prot: 2;
    };
}Fda801RegDiagPhaseDelayCtrlCh4_t;

//Table 26. IB13-ADDR: I0001101
typedef union {
    uint8_t reg_val;
    struct{
        uint8_t res:2;
        uint8_t watchdog_on_i2sws_signal: 1;
		uint8_t cmdpwm_peak:1;
		uint8_t ac_diag_signal_level:1;
		uint8_t res2: 1;
        uint8_t digital_mute:1;
		uint8_t res3: 1;
    };
}Fda801RegIb13Addr_t;

//Table 27. IB14-ADDR: I0001110
typedef union {
    uint8_t reg_val;
    struct{
        uint8_t first_setup:1;
		uint8_t lc_filetr_setup:3;
		uint8_t res: 4;
    };
}Fda801RegIb14Addr_t;

//Table 28. DB0-ADDR: I0100000
typedef union {
    uint8_t reg_val;
    struct{
    	uint8_t pll_lock:1;
		uint8_t res:2;
		uint8_t uvlo_sens:1;
		uint8_t dump_pulses_sens:1;
		uint8_t clipping_sens:1;
		uint8_t output_offset_sens:1;
		uint8_t input_offset_sens:1;
    };
}Fda801RegDb0Addr_t;

//Table 29. DB1-ADDR: â€œI0100001â€�
typedef union {
    uint8_t reg_val;
    struct{
    	uint8_t res:4;
    	uint8_t thermal_warning_4_not_active:1;
		uint8_t thermal_warning_3_not_active:1;
		uint8_t thermal_warning_2_not_active:1;
		uint8_t thermal_warning_1_not_active:1;
    };
}Fda801RegDb1Addr_t;


typedef union {
    uint8_t reg_val;
    struct{
        uint8_t state:1;                /*d0 mute play*/
		uint8_t load_open:1;             /*d1 Normal Open*/
		uint8_t short_gnd:1;             /*d2 */
		uint8_t short_vcc:1;             /*d3 */
		uint8_t load_short:1;            /*d4 */
		uint8_t over_current:1;          /*d5 */
		uint8_t dc_diag_dat_valid:1;     /*d6 */
		uint8_t dc_op:1;                 /*d7 operation*/
    };
}Fda801RegChDcOut_t;

//Table 30. DB2-ADDR: I0100010â€� CHANNEL 1 DC outputs
typedef union {
    uint8_t reg_val;
    Fda801RegChDcOut_t ChDcOut;
}Fda801RegCh1DcOut_t;

//Table 31. DB3-ADDR: I0100011â€� CHANNEL 2 DC outputs
typedef union xFda801RegCh2DcOut_t{
    uint8_t reg_val;
    Fda801RegChDcOut_t ChDcOut;
}Fda801RegCh2DcOut_t;

//Table 32. DB4-ADDR: I0100100â€� CHANNEL 3 DC outputs
typedef union xFda801RegCh3DcOut_t{
    uint8_t reg_val;
    Fda801RegChDcOut_t ChDcOut;
}Fda801RegCh3DcOut_t;

//Table 33. DB5-ADDR: I0100101â€� CHANNEL 4 DC outputs
typedef union xFda801RegCh4DcOut_t{
    uint8_t reg_val;
    Fda801RegChDcOut_t ChDcOut;
}Fda801RegCh4DcOut_t;


#define CHANNEL_DIAG_RES(CH_X)     \
	uint8_t CH_X##_error_warning:1; \
	uint8_t CH_X##_tweeter:1;      \
	uint8_t CH_X##_ac_diag_data:1; \
	uint8_t CH_X##_operation:1;

//Table 34. DB6-ADDR: �I0100110� CH1 and CH2 A C diagnostic results
typedef union xFda801RegCh1Ch2AcDiag_t{
    uint8_t reg_val;
    struct{
    	CHANNEL_DIAG_RES(ch2)
    	CHANNEL_DIAG_RES(ch1)
    };
}Fda801RegCh1Ch2AcDiag_t;

//Table 35. DB7-ADDR: �I0100111� CH3 and CH4 A C diagnostic results
typedef union xFda801RegCh3Ch4AcDiag_t{
    uint8_t reg_val;
    struct{
    	CHANNEL_DIAG_RES(ch4)
    	CHANNEL_DIAG_RES(ch3)
    };
}Fda801RegCh3Ch4AcDiag_t;


typedef union xFda801RegChAcDiag_t{
    uint8_t reg_val;
    struct{
        CHANNEL_DIAG_RES(ch4)
        CHANNEL_DIAG_RES(ch3)
    };
    struct{
        CHANNEL_DIAG_RES(ch2)
        CHANNEL_DIAG_RES(ch1)
    };
}Fda801RegChAcDiag_t;

typedef struct xFda801Reg_t{
    uint8_t reg_addr;
    char *name;
}Fda801Reg_t;


typedef struct xFda801RegData_t{
    uint8_t addr;
    uint8_t value;
}Fda801RegData_t;

typedef  union uEnable_t{
    uint8_t byte;
    struct{
        uint8_t en1:1;
        uint8_t en2:1;
        uint8_t en3:1;
        uint8_t res:5;
    };
}Enable_t;

typedef struct {
    uint8_t addr;
    Enable_t code;
}Fda801I2cAddr_t;

#ifdef HAS_GPIO
typedef struct {
    Pad_t en1;
    Pad_t en2;
    Pad_t en3;
    Pad_t mute;
    Pad_t diag;
}Fda801Gpios_t;
#endif

typedef union uFda801Reg_t{
  uint8_t reg_val;
  Fda801RegInterface_t Ib0Addr;
  Fda801RegIb1Addr_t Ib1Addr;
  Fda801RegIb2Addr_t Ib2Addr;
  Fda801RegIb3Addr_t Ib3Addr;
  Fda801RegIb4Addr_t Ib4Addr;
  Fda801RegChannel1Ctrl_t Ib5AddrChannel1Ctrl;
  Fda801RegChannel2Ctrl_t Ib6AddrChannel2Ctrl;
  Fda801RegChannel3Ctrl_t Ib7AddrChannel3Ctrl;
  Fda801RegChannel4Ctrl_t Ib8AddrChannel4Ctrl;
  Fda801RegDiagPhaseDelayCtrlCh1_t DiagPhaseDelayCtrlCh1;
  Fda801RegDiagPhaseDelayCtrlCh2_t DiagPhaseDelayCtrlCh2;
  Fda801RegDiagPhaseDelayCtrlCh3_t DiagPhaseDelayCtrlCh3;
  Fda801RegDiagPhaseDelayCtrlCh4_t DiagPhaseDelayCtrlCh4;
  Fda801RegIb13Addr_t Ib13Addr;
  Fda801RegIb14Addr_t Ib14Addr;
  Fda801RegDb0Addr_t Db0Addr;
  Fda801RegDb1Addr_t Db1Addr;
  Fda801RegCh1DcOut_t Ch1DcOut;
  Fda801RegCh2DcOut_t Ch2DcOut;
  Fda801RegCh3DcOut_t Ch3DcOut;
  Fda801RegCh4DcOut_t Ch4DcOut;
  Fda801RegCh3Ch4AcDiag_t Ch3Ch4AcDiag;
  Fda801RegCh1Ch2AcDiag_t Ch1Ch2AcDiag;
}Fda801RegVal_t;


typedef struct xFda801RegSetting_t{
    uint8_t addr;
    Fda801RegVal_t val;
}Fda801RegSetting_t;

typedef struct xFda801Config_t{
    uint8_t num;
    uint8_t def_i2c_addr;
#ifdef HAS_GPIO
    Fda801Gpios_t gpio;
#endif
    Fda801RegSetting_t RegCfgDump[FDA801_REG_CNT];
}Fda801Config_t;

/*
 Table 30
 Table 31
 Table 32
 Table 33
 */

typedef union xFda801ChannelDcOutput_t{
    uint8_t byte;
    struct{
        uint8_t state:1;                /*d0*/
        uint8_t load_open:1;            /*d1*/
        uint8_t short_gnd:1;            /*d2*/
        uint8_t short_vcc:1;            /*d3*/
        uint8_t load_short:1;           /*d4*/
        uint8_t over_current:1;         /*d5*/
        uint8_t dc_diag_dat_valid:1;    /*d6*/
        uint8_t operation:1;            /*d7*/
    };
}Fda801ChannelDcOutput_t;

typedef struct{
    Fda801AcDiagOps_t operation;
    Fda801AcDiagValid_t valid;
    Fda801AcDiagTweeter_t tweeter;
    Fda801AcDiagWarning_t warning;
}Fda801ChannelAcDiag_t;

typedef struct xFda801ChannelParam_t{
      Fda801ChannelState_t state;
      Fda801ChannelGain_t  gain_sel;
      Fda801ChannelDiag_t diag;
      bool ac_diag;
      bool dc_diag;
      bool pwm_on;
      bool ac_ext_test_flag;
}Fda801ChannelParam_t;

typedef struct xFda801Channel_t{
    Fda801ChannelNum_t ch_num;
    Fda801ChannelParam_t Set;
    Fda801ChannelParam_t Reg;
    Fda801ChannelDcOutput_t DcOutput;
    Fda801ChannelAcDiag_t AcDiag;
    Fda801DcDiag_t DcDiag;
}Fda801Channel_t;

typedef struct {
	  uint8_t num;
	  uint32_t spin_cnt;
	  Fda801Channel_t Channel[FDA801_CHANNEL_COUNT];
	  uint32_t reg_val_disaccord;
	  bool init;
}Fda801Handle_t;

typedef struct {
      uint8_t ac_diag;
      uint8_t dc_output;
      uint8_t ctrl;
}ChannalRegAddr_t;

typedef struct {
      Fda801ChannelNum_t channal;
      ChannalRegAddr_t RegAddr;
}Channal2Regs_t;


#endif /* FDA801_TYPES_H */
