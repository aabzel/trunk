#ifndef SI4703_REGISTER_TYPES_H
#define SI4703_REGISTER_TYPES_H

#include "std_includes.h"
#include "si4703_const.h"
#include "storage_const.h"

//Register 0Ch. RDSA
typedef union {
    uint16_t word;
    uint16_t rdsa; /*RDS Block A Data*/
} Si4703RegRdsA_t;

//Register 0Dh. RDSB
typedef union {
    uint16_t word;
    uint16_t rdsb;/*RDS Block B Data*/
} Si4703RegRdsB_t;

//Register 0Eh RDSC
typedef union {
    uint16_t word;
    uint16_t rdsc;/*RDS Block C Data*/
} Si4703RegRdsC_t;

typedef struct {
    Si4703RegAddr_t reg_addr;
    uint8_t reg_index;
    char *name;
    bool valid;
    StorageAccess_t access;
} Si4703RegInfo_t;

//Register 0Fh RDSD
typedef union {
    uint16_t word;
    uint16_t rdsd; /*RDS Block B Data*/
} Si4703RegRdsD_t;

//Register 00h. Device ID
typedef union {
    uint16_t word;
    struct {
        uint16_t mfgid :12; /*Manufacturer ID*/
        uint16_t pn :4; /*Part Number*/
    };
} Si4703RegDeviceID_t;

//Register 01h. Chip ID
typedef union {
    uint16_t word;
    struct {
        uint16_t firmware :6; /*Firmware Version*/
        uint16_t dev :4; /*Device*/
        uint16_t rev :6; /*Chip Version*/
    };
} Si4703RegChipID_t;

/*
 Register 02h. Power Configuration
 */
typedef union {
    uint16_t word;
    struct {
        uint16_t enable :1; /*Powerup Enable*/
        uint16_t res1 :5; /**/
        uint16_t disable :1; /*Powerup Disable*/
        uint16_t res2 :1; /**/
        uint16_t seek :1; /*Seek*/
        uint16_t seekup :1; /*Seek Direction */
        uint16_t skmode :1; /*Seek Mode*/
        uint16_t rdsm :1; /*bit11 RDS Mode*/
        uint16_t res3 :1; /**/
        uint16_t mono :1; /*Mono Select*/
        uint16_t dmute :1; /*Mute Disable*/
        uint16_t dsmute :1; /*Softmute Disable */
    };
} Si4703RegPwrCfg_t;

//Register 03h. Channel
typedef union {
    uint16_t word;
    struct {
        uint16_t channel :10; /*Channel Select*/
        uint16_t res :5; /**/
        uint16_t tune :1; /*Tune*/
    };
} Si4703RegChannel_t;

//Register 04h. System Configuration 1
typedef union {
    uint16_t word;
    struct {
        uint16_t gpio1 :2; /*General Purpose I/O 1*/
        uint16_t gpio2 :2; /*General Purpose I/O 2*/
        uint16_t gpio3 :2; /*General Purpose I/O 3.   */
        uint16_t blndadj :2; /*Stereo/Mono Blend Level Adjustment*/
        uint16_t res :2; /**/
        uint16_t agcd :1; /*AGC Disable*/
        uint16_t de :1; /* De-emphasis*/
        uint16_t rds :1; /*RDS Enable*/
        uint16_t res2 :1; /**/
        uint16_t stcien :1; /*Seek/Tune Complete Interrupt Enable*/
        uint16_t rdsien :1; /*RDS Interrupt Enable*/
    };
} Si4703RegSysCfg1_t;

//Register 05h. System Configuration 2
typedef union {
    uint16_t word;
    struct {
        uint16_t volume :4; /*Volume.*/
        uint16_t space :2; /*Channel Spacing*/
        uint16_t band :2; /*Band Select*/
        uint16_t seekth :8; /*RSSI Seek Threshold*/
    };
} Si4703RegSysCfg2_t;

//Register 06h. System Configuration 3
typedef union {
    uint16_t word;
    struct {
        uint16_t skcnt :4; /*Seek FM Impulse Detection Threshold*/
        uint16_t sksnr :4; /*Seek SNR Threshold*/
        uint16_t volext :1; /*Extended Volume Range*/
        uint16_t res :3; /**/
        uint16_t smutea :2; /*Softmute Attenuation*/
        uint16_t smuter :2; /*Softmute Attack/Recover Rate*/
    };
} Si4703RegSysCfg3_t;

//Register 07h. Test 1
typedef union {
    uint16_t word;
    struct {
        uint16_t res :14; /**/
        uint16_t ahizen :1; /*Audio High-Z Enable*/
        uint16_t xoscen :1; /*Crystal Oscillator Enable*/
    };
} Si4703RegTest1_t;

//Register 0Ah. Status RSSI
typedef union {
    uint16_t word;
    struct {
        uint16_t rssi :8; /*RSSI (Received Signal Strength Indicator)*/
        uint16_t st :1; /*Stereo Indicator*/
        uint16_t blera :2; /*RDS Block A Errors*/
        uint16_t rdss :1; /*RDS Synchronized*/
        uint16_t afcrl :1; /*AFC Rail*/
        uint16_t sf_bl :1; /*Seek Fail/Band Limit*/
        uint16_t stc :1; /*Seek/Tune Complete*/
        uint16_t rdsr :1; /*RDS Ready*/
    };
} Si4703RegStatusRssi_t;

//Register 0Bh. Read Channel
typedef union {
    uint16_t word;
    struct {
        uint16_t readchan :10; /*Read Channel*/
        uint16_t blerd :2; /*RDS Block D Errors*/
        uint16_t blerc :2; /*RDS Block C Errors*/
        uint16_t blerb :2; /*RDS Block B Errors*/
    };
} Si4703RegReadChan_t;

typedef union {
    uint16_t word;
    Si4703RegDeviceID_t DeviceId; /*00*/
    Si4703RegChipID_t ChipID; /*01*/
    Si4703RegPwrCfg_t PwrCfg; /*02*/
    Si4703RegChannel_t Channel; /*03*/
    Si4703RegSysCfg1_t SysCfg1; /*04*/
    Si4703RegSysCfg2_t SysCfg2; /*05*/
    Si4703RegSysCfg3_t SysCfg3; /*06*/
    Si4703RegTest1_t Test1; /*07*/
    Si4703RegStatusRssi_t StatusRssi; /*0A*/
    Si4703RegReadChan_t ReadChan; /*0B*/
    Si4703RegRdsA_t RdsA; /*0C*/
    Si4703RegRdsB_t RdsB; /*0D*/
    Si4703RegRdsC_t RdsC; /*0E*/
    Si4703RegRdsD_t RdsD; /*0F*/
} Si4703Reg_t;

#endif /* SI4703_REGISTER_TYPES_H */
