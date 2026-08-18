#ifndef SI4703_CONST_H
#define SI4703_CONST_H

#include "time_mcal.h"
#include "si4703_dep.h"

#define SI4703_VERSION "4"
#define SI4703_PERIOD_US MSEC_2_USEC(100)

#define SI4703_REG_WRITE_CNT 8
#define SI4703_REG_CNT 16
#define SI4703_I2C_ADDR 0x10 //0x20
#define SI4703_DEV_CODE_BEFORE_PUP     8
#define SI4703_DEV_CODE_AFTER_PUP     9


#define SI4703_DEVICEID_PART_NUMBER_SI4703 0x01
#define SI4703_DEVICEID_MANUFACTURER_ID 0x242

typedef enum{
    SI4703_REG_DEVICE_ID = 0,
    SI4703_REG_CHIPID = 1,
    SI4703_REG_POWERCFG = 2,
    SI4703_REG_CHANNEL = 3,
    SI4703_REG_SYSCONFIG1 = 4,
    SI4703_REG_SYSCONFIG2 = 5,
    SI4703_REG_SYSCONFIG3 = 6,
    SI4703_REG_TEST1 = 7,
    SI4703_REG_TEST2 = 8,
    SI4703_REG_BOOTCONFIG = 9,
    SI4703_REG_STATUS_RSSI = 10,
    SI4703_REG_READ_CHAN = 11,
    SI4703_REG_RDSA = 12,
    SI4703_REG_RDSB = 13,
    SI4703_REG_RDSC = 14,
    SI4703_REG_RDSD = 15,


    SI4703_REG_UNDEF = 17
} Si4703RegAddr_t;


typedef enum {
    Si4703_SPI_WRITE = 0,
    Si4703_SPI_READ = 1,
    Si4703_SPI_UNDEF = 2,
} Si4703SpiAccess_t;

typedef enum {
    POWER_DOWN = 0,
    POWER_UP = 1,
    POWER_UNDEF = 2,
} Si4703Pwr_t;

typedef enum {
    BAND_SEL_87_5_108_MHz = 0, //(USA, Europe) (Default).
    BAND_SEL_76_108_MHz = 1,   //(Japan wide band).
    BAND_SEL_76_90_MHz = 2,    // (Japan).
    BAND_SEL_RES = 3,
} Si4703BandSel_t;

typedef enum {
    SEEK_END_WRAP = 0, // Wrap
    SEEK_END_HALT = 1, // Halt
    SEEK_END_UNDEF = 2,
} Si4703SeekEnd_t;

typedef enum {
    TUNE_DISABLE = 0,
    TUNE_ENABLE = 1,
    TUNE_UNDEF = 2,
} Si4703Tune_t;

typedef enum {
    SEEK_DIR_DOWN = 0, //direction of the search
    SEEK_DIR_UP = 1,   // direction of the search
    SEEK_DIR_UNDEF = 2,
} Si4703SeekDir_t;

typedef enum {
    CHAN_SPACE_200_KHZ = 0,   //200 kHz (USA, Australia) (default).
    CHAN_SPACE_100_KHZ = 1,   //100 kHz (Europe, Japan).
    CHAN_SPACE_50_KHZ = 2,    //50 kHz
    CHAN_SPACE_UNDEF = 3,     //
} Si4703Channel_Spacing_t;

typedef enum {
    RDS_MODE_STANDART = 0,
    RDS_MODE_VERBOSE = 1,
    RDS_MODE_UNDEF,
} Si4703RdsMode_t;

typedef enum {
    RDS_DISABLE = 0,
    RDS_ENABLE = 1,
    RDS_UNDEF,
} Si4703Rds_t;

typedef enum {
    RDS_INT_DISABLE = 0,
    RDS_INT_ENABLE = 1,
    RDS_INT_UNDEF,
} Si4703RdsInt_t;

#endif /* SI4703_CONST_H */
