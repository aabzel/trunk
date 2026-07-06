#ifndef I2S_CONST_H
#define I2S_CONST_H

#include "i2s_dep.h"

#define I2S_MEM_SIZE 2048
#define I2S_MEM_HALF_SIZE (I2S_MEM_SIZE/2)

#define I2S_POLL_PERIOD_US 10000

#define I2S_ARRAY_CNT 2
#define I2S_VOLUME_SET_ACCURACY 10

#ifndef I2S_BLOCK_SIZE
#define I2S_BLOCK_SIZE 128
#endif



#include "audio_const.h"

typedef enum {
    FULL_DUPLEX_UNDEF = 0,
    FULL_DUPLEX_OFF ,
    FULL_DUPLEX_ON ,
} I2sFullDuplex_t;


typedef enum {
    LOOPBACK_UNDEF = 0,
    LOOPBACK_SHARED_MEM ,
    LOOPBACK_SWITCH_MEM,
} I2sLoopBackMode_t;

typedef enum {
    I2S_CLOCK_POL_UNDEF = 0,
    I2S_CLOCK_POL_LOW ,
    I2S_CLOCK_POL_HIGH ,
} I2sCpol_t;

#if 0
typedef enum {
    I2S_DIR_BUS_MODE_UNDEF = 0,
    I2S_DIR_BUS_MODE_SLAVE = 1,    /*He clocks I2S,*/
    I2S_DIR_BUS_MODE_MASTER = 4,   /*I clock I2S,*/
    I2S_DIR_BUS_MODE_SLAVE_TX = 2, /*He clocks I2S, I out Tx*/
    I2S_DIR_BUS_MODE_SLAVE_RX = 3, /*He clocks I2S, I in RX*/
    I2S_DIR_BUS_MODE_MASTER_TX = 5,/*I clock I2S, I Out TX*/
    I2S_DIR_BUS_MODE_MASTER_RX = 6,/*I clock I2S, I In Rx*/
} I2sDirAndBusRole_t;
#endif

typedef enum {
    I2S_DATA_FORMAT_UNDEF = 0,
    I2S_DATA_FORMAT_8B = 8,
    I2S_DATA_FORMAT_16B = 16,
    I2S_DATA_FORMAT_16B_EXTENDED = 17,
    I2S_DATA_FORMAT_24B = 24,
    I2S_DATA_FORMAT_32B = 32,

} I2sDataFormat_t;

typedef enum {
    I2S_MCLKOUT_UNDEF = 0,
    I2S_MCLKOUT_OFF ,
    I2S_MCLKOUT_ON ,
} I2sMclkOut_t;

typedef enum {
    I2S_STD_UNDEF = 0,
    I2S_STD_PHILIPS ,
    I2S_STD_MSB ,
    I2S_STD_LSB ,
    I2S_STD_PCM_SHORT ,
    I2S_STD_PCM_LONG ,
} I2sStandard_t;

typedef enum {
    I2S_CLK_UNDEF = 0,
    I2S_CLK_PLL ,
    I2S_CLK_EXT ,
} I2sClockSource_t;

typedef enum {
    I2S_STATE_UNDEF = 0,
    I2S_STATE_OFF   ,
    I2S_STATE_AMP   ,
    I2S_STATE_RUN   ,
    I2S_STATE_DEC   ,
    I2S_STATE_REC   ,
    I2S_STATE_PLAY ,
    I2S_STATE_IDLE ,

} I2sState_t;

#endif /* I2S_CONST_H */
