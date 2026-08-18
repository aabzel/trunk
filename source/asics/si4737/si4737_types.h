#ifndef SI4737_TYPES_H
#define SI4737_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "gpio_types.h"
#include "si4737_const.h"
#include "data_types.h"


typedef union {
    uint16_t word;
    struct {
        uint16_t rds_en :1; /* RDS Processing Enable   */
        uint16_t res :7;    /*   */
        uint16_t blethd :2; /* Block Error Threshold BLOCKD   */
        uint16_t blethc :2; /* Block Error Threshold BLOCKC  */
        uint16_t blethb :2; /* Block Error Threshold BLOCKB */
        uint16_t bletha:2;  /* Block Error Threshold BLOCKA */
    };
}FmRdsConfig_t;

typedef union {
    uint8_t reg_val;
    struct {
        uint8_t stc_int :1; /*   */
        uint8_t asq_int :1; /*   */
        uint8_t same_int:1; /* RDSINT */
        uint8_t rsq_int  :1; /*  */
        uint8_t res :2; /*  */
        uint8_t err:1; /*  */
        uint8_t cts :1; /* */
    };
}Si4737RegStatus_t;

typedef union {
    uint8_t byte;
    struct {
        uint8_t stc_int :1;  /* Seek/Tune Complete Interrupt.  */
        uint8_t asq_int :1;  /* Signal Quality Interrupt.   */
        uint8_t rds_int:1;   /* Received Signal Quality Interrupt.  */
        uint8_t rsq_int  :1; /* Received Signal Quality Interrupt.  */
        uint8_t res :2;     /*  */
        uint8_t err:1; /* Error*/
        uint8_t cts :1; /* Clear to Send*/
    };
}Si4737Status_t;

typedef union {
    uint8_t byte;
    struct {
        uint8_t intack:1;  /* Seek/Tune Interrupt Clear.  */
        uint8_t cancel:1;  /* Cancel seek.  */
        uint8_t res:6;     /* Always write to 0.  */
    };
}FmTuneFreq_t;


typedef union {
    uint8_t byte;
    struct {
        uint8_t valid:1;  /*Valid Channel.   */
        uint8_t afcrl:1;  /*AFC Rail Indicator.    */
        uint8_t res:5;     /*   */
        uint8_t bltf:1;  /*Band Limit.    */
    };
}FmTuneStatusResp1_t;

typedef union {
    uint8_t buff[8];
    struct {
        Si4737Status_t status;/**/
        FmTuneStatusResp1_t Resp1;/**/
        uint16_t read_freq;/*Read Frequency*/
        uint8_t rssi;/*Received Signal Strength Indicator.*/
        uint8_t snr;/* dB*/
        uint8_t mult ;/*Multipath.*/
        uint8_t read_ant_cap;/*Read Antenna Tuning Capacitor (Si4704/05/06/2x only).*/
    };
}FmTuneStatusResp_t;

typedef union {
    uint8_t byte;
    struct {
        uint8_t func:4;    /* Function.  */
        uint8_t xoscen:1;  /* Crystal Oscillator Enable.  */
        uint8_t patch:1;   /* Patch Enable */
        uint8_t gpo2oen:1; /* GPO2 Output Enable */
        uint8_t cts_ien:1;  /* CTS Interrupt Enable */
    };
}Si4737PwgUpArg1_t;


typedef union {
    uint8_t byte;
    struct {
        uint8_t intack:1;    /* Interrupt Acknowledge */
        uint8_t res:7;  /*  */
    };
}FmRsqStatusArg1_t;

typedef union {
    uint8_t buff[5];
    struct __attribute__((__packed__)) {
        uint8_t arg1;
        uint16_t property; /*Property*/
        uint16_t value;    /*Property Value*/
    };
}SetPropArg_t;

typedef union {
    uint8_t byte;
    struct {
        uint8_t rssiilint:1;    /*RSSI Detect Low   */
        uint8_t rssihint:1;    /* RSSI Detect High  */
        uint8_t snrlint:1;    /* SNR Detect Low  */
        uint8_t snrhint:1;    /*SNR Detect High.   */
        uint8_t multlint:1;    /*Multipath Detect Low   */
        uint8_t multhint:1;    /*Multipath Detect High   */
        uint8_t res:1;    /*   */
        uint8_t blendint:1;    /* Blend Detect Interrupt.  */
    };
}FmRsqStatusResp1_t;

typedef union {
    uint8_t byte;
    struct {
        uint8_t valid:1;    /* Valid Channel  */
        uint8_t afcrl:1;    /* AFC Rail Indicator  */
        uint8_t res1:1;    /*   */
        uint8_t smute:1;    /*Soft Mute Indicator  */
        uint8_t res2:4;    /*    */
    };
}FmRsqStatusResp2_t;

typedef union {
    uint8_t byte;
    struct {
        uint8_t stblend:7;  /* Stereo Blend Indicator*/
        uint8_t pilot:1;    /* Pilot Indicator */
    };
}FmRsqStatusResp3_t;


typedef union{
 uint8_t buff[8];
 struct {
     Si4737Status_t status;
     FmRsqStatusResp1_t Resp1;
     FmRsqStatusResp2_t Resp2;
     FmRsqStatusResp3_t Resp3;
     uint8_t rssi;
     uint8_t snr;
     uint8_t mult;
     uint8_t freqoff_khz;
 };
}FmRsqStatusResp_t;

typedef struct {
    Si4737PwgUpArg1_t PwgUpArg1;
    OpMode_t OpMode;
    uint8_t rds_int_fifo_cnt;
    double fm_freq_mhz;
    bool valid;
    bool rds_en;
}Si4737Config_t;


typedef union{
    uint16_t word;
    struct {
        uint16_t rds_recv       :1;    /*RDS Received*/
        uint16_t rds_sync_lost  :1;  /*RDS Sync Lost*/
        uint16_t rds_sync_found :1;  /*RDS Sync Found.*/
        uint16_t res1           :1;  /**/
        uint16_t rds_new_block_a :1;  /*RDS New Block A Found*/
        uint16_t rds_new_block_b :1;  /*RDS New Block B Found*/
        uint16_t res2 :10;  /**/
    };
}FmRdsIntSource_t;

typedef union{
    uint16_t word;
    struct {
        uint16_t r_mute :1;    /*Mutes   R Audio Outputs*/
        uint16_t l_mute :1;  /*RMutes   L Audio Outputs*/
        uint16_t res   :14;  /**/
    };
}RxHardMute_t;

typedef union{
    uint16_t word;
    struct {
    	  uint16_t osize :2;    /* Digital Output Audio Sample Precision. */
    	  uint16_t omono :1;    /* Digital Output Mono Mode */
    	  uint16_t omode :4;    /* Digital Output Mode */
    	  uint16_t ofall :1;    /* Digital Output DCLK Edge */
    	  uint16_t res :8;      /* */
    };
}DigitalOutputFormat_t;

typedef union{
    uint16_t word;
    struct {
        uint16_t rssi_lien :1;    /*Interrupt Source Enable: RSSI Low.*/
        uint16_t rssi_hien :1;  /*Interrupt Source Enable: RSSI High*/
        uint16_t snr_lien  :1;  /*Interrupt Source Enable: SNR Low*/
        uint16_t snr_hien  :1;  /*Interrupt Source Enable: SNR High*/
        uint16_t mult_lien :1;  /*Interrupt Source Enable: Multipath Low*/
        uint16_t mult_hien :1;  /*Interrupt Source Enable: Multipath High*/
        uint16_t res1 :1;  /**/
        uint16_t blend_ien :1;  /*Interrupt Source Enable: Blend*/
        uint16_t res2 :8;  /**/
    };
}FmRsqIntSource_t;


typedef union{
    uint16_t word;
    struct {
        uint16_t stcien :1;    /*Seek/Tune Complete Interrupt Enable.*/
        uint16_t asqien :1;  /*Audio Signal Quality Interrupt Enable*/
        uint16_t rdsien :1;  /*RDS Interrupt Enable (Si4711/13/21 Only)*/
        uint16_t res1   :3;  /**/
        uint16_t errien :1;  /*ERR Interrupt Enable*/
        uint16_t ctsien :1;  /*CTS Interrupt Enable*/
        uint16_t stcrep :1;  /*STC Interrupt Repeat*/
        uint16_t asqrep :1;  /*ASQ Interrupt Repeat*/
        uint16_t rdsrep :1;  /*RDS Interrupt Repeat. (Si4711/13/21 Only)*/
        uint16_t res :5;  /**/

    };
}GpoIen_t;


typedef union{
    uint8_t buff[2];
    struct{
        Si4737PwgUpArg1_t Arg1;
        uint8_t op_mode;
    };
}PowerUpArg_t;

typedef union{
    uint8_t byte;
    Si4737Status_t status;
}PowerUpResp_t;

typedef struct {
    double fm_freq_mhz;
    uint8_t rssi;/*Received Signal Strength Indicator.*/
    uint8_t snr;/* dB*/
    bool connected;
    bool init;
    uint8_t mult;
    uint16_t  rx_volume;
    uint32_t rds_int_cnt;
    uint32_t asq_cnt;
    uint32_t stc_int_cnt;
    uint32_t err_cnt;
    uint32_t rsq_int_cnt;
    uint32_t rds_recv_cnt;
    uint32_t valid_cnt;
    uint32_t pilot_cnt;
    uint32_t cts_cnt;
    uint8_t rds_fifo_cnt;
    uint8_t out_size_bit; /*Digital Output Audio Sample Precision*/
    DigitalOutputMonoMode_t out_mono; /*Digital Output Mono Mode*/
    DigitalOutputMode_t out_mode;/*Digital Output Mode*/
    DigitalOutputDclkEdge_t out_fall; /*Digital Output DCLK Edge*/
    bool stc_int;
    bool rds_int;
    bool rsq_int;
    double freq_offset; /*Hz*/
}Si4737Handler_t;


typedef struct {
    Si4737Command_t cmd;
    uint8_t arg_cnt;
    uint8_t resp_size;
}Si4737CommandInfo_t;

typedef struct {
    uint16_t id;
    uint16_t val;
}Si4737Property_t;

typedef struct {
    uint16_t id;
    const char* name;
}Si4737PropertyDiag_t;



typedef struct __attribute__((__packed__))  {
   Si4737RegStatus_t status;
   uint8_t pn;
   uint8_t fwmajor;
   uint8_t  fwminor;
   uint16_t patch;
   uint8_t cmpmajor;
   uint8_t cmpminor;
   uint8_t chiprev;
   uint8_t res[5];
   uint8_t cid;
}Si4737RevResp_t ;

typedef union {
    uint8_t byte;
    struct {
        uint8_t fast:1;    /*FAST Tuning*/
        uint8_t freeze:1;  /*Freeze Metrics During Alternate Frequency Jump*/
        uint8_t res:6;     /*  */

    };
}FmTuneFreqArg1_t;


typedef union {
    uint8_t byte;
    struct {
        uint8_t res1:2;  /**/
        uint8_t wrap:1;  /**/
        uint8_t seekup:1;  /**/
        uint8_t res2:4;  /**/
    };
}FmSeekStartArg1_t;


typedef union  __attribute__((__packed__)) {
    uint8_t buff[4];
    struct  __attribute__((__packed__)) {
        FmTuneFreqArg1_t FmTuneFreqArg1;
        uint16_t freq_10mhz;
        uint8_t antcap;
    };
}FmTuneFreqArg_t;

typedef union {
    uint8_t byte;
    struct {
        uint8_t int_ack:1;  /*Interrupt Acknowledge*/
        uint8_t mt_fifo:1;  /*Empty FIFO*/
        uint8_t status_only:1;  /*Status Only.*/
        uint8_t res:5;  /**/
    };
}FmRdsStatusArg1_t;

typedef union{
    uint8_t byte;
    struct {
        uint8_t rds_recv:1;  /*RDS Received*/
        uint8_t rds_sync_lost:1;  /*RDS Sync Lost*/
        uint8_t rds_sync_found:1;  /*RDS Sync Found*/
        uint8_t res1:1;  /**/
        uint8_t rds_new_block_a:1;  /*RDS New Block A*/
        uint8_t rds_new_block_b:1;  /*RDS New Block B*/
        uint8_t res2:2;  /**/
    };
}FmRdsStatusResp1_t;


typedef union {
    uint8_t byte;
    struct {
        uint8_t rds_sync:1;  /*RDS Sync*/
        uint8_t res1:1;
        uint8_t grp_lost:1;  /*Group Lost*/
        uint8_t res2:5;
    };
}FmRdsStatusResp2_t;

typedef union {
    uint8_t byte;
    struct {
        uint8_t ble_d:2;        /*RDS Block D Corrected Errors*/
        uint8_t ble_c:2;        /*RDS Block C Corrected Errors*/
        uint8_t ble_b:2;        /*RDS Block B Corrected Errors.*/
        uint8_t ble_a:2;        /*RDS Block A Corrected Errors.*/
    };
}FmRdsStatusResp12_t;

typedef union {
    uint16_t words[4];
    struct {
        U16_bit_t block_a;
        U16_bit_t block_b;
        U16_bit_t block_c;
        U16_bit_t block_d;
    };
}RdsData_t;

typedef union __attribute__((__packed__)) {
    uint8_t buff[13];
    struct __attribute__((__packed__)){
        Si4737Status_t status;
        FmRdsStatusResp1_t Resp1;
        FmRdsStatusResp2_t Resp2;
        uint8_t rds_fifo_used;
        RdsData_t RdsData;
        FmRdsStatusResp12_t Resp12;
    };
}FmRdsStatusResp_t;

typedef union {
    uint8_t byte;
    Si4737Status_t status;
}Si4737FmTuneFreqResp_t;

typedef union {
    uint8_t byte;
    Si4737Status_t status;
}FmSeekStartResp_t;

typedef union {
    uint8_t buff[16];
    Si4737RevResp_t RevResp;
}Si4737FullRevResp_t;


#endif /* SI4737_TYPES_H */
