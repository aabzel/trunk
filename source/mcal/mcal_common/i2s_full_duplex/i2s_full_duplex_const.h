#ifndef I2S_CONST_H
#define I2S_CONST_H

#ifndef HAS_I2S
#error "+HAS_I2S"
#endif /*HAS_I2S*/

#define I2S_BUFFER_SIZE 600
#define I2S_ARRAY_CNT 2
#define I2S_VOLUME_SET_ACCURACY 10

typedef enum {
    FULL_DUPLEX_OFF = 0,
    FULL_DUPLEX_ON = 1,
    FULL_DUPLEX_UNDEF = 2,
} FullDuplex_t;

typedef enum {
    LOOPBACK_SHARED_MEM = 0,
    LOOPBACK_SWITCH_MEM = 1,
    LOOPBACK_UNDEF = 2,
} LoopBackMode_t;

typedef enum {
    I2S_CLOCK_POL_LOW = 0,
    I2S_CLOCK_POL_HIGH = 1,
    I2S_CLOCK_POL_UNDEF = 2,
} Cpol_t;

typedef enum {
    I2SMODE_SLAVE = 1,
    I2SMODE_SLAVE_TX = 2,
    I2SMODE_SLAVE_RX = 3,
    I2SMODE_MASTER = 4,
    I2SMODE_MASTER_TX = 5,
    I2SMODE_MASTER_RX = 6,

    I2SMODE_UNDEF = 0,
} I2sRole_t;

typedef enum {
    I2S_DATA_FORMAT_8B = 8,
    I2S_DATA_FORMAT_16B = 16,
    I2S_DATA_FORMAT_16B_EXTENDED = 17,
    I2S_DATA_FORMAT_24B = 24,
    I2S_DATA_FORMAT_32B = 32,

    I2S_DATA_FORMAT_UNDEF = 0,
} I2sDataFormat_t;

typedef enum {
    I2S_AUDIO_FREQ_UNDEF = 0,
    I2S_AUDIO_FREQ_768K = 768000,
    I2S_AUDIO_FREQ_384K = 384000,
    I2S_AUDIO_FREQ_192K = 192000,
    I2S_AUDIO_FREQ_176K = 176400,
    I2S_AUDIO_FREQ_96K = 960000,
    I2S_AUDIO_FREQ_88K = 88200,
    I2S_AUDIO_FREQ_48K = 48000,
    I2S_AUDIO_FREQ_44K = 44100,
    I2S_AUDIO_FREQ_41K = 41000,
    I2S_AUDIO_FREQ_32K = 32000,
    I2S_AUDIO_FREQ_22K = 22000,
    I2S_AUDIO_FREQ_16K = 16000,
    I2S_AUDIO_FREQ_11K = 11000,
    I2S_AUDIO_FREQ_8K = 8000,
    I2S_AUDIO_FREQ_DEFAULT = 31000,
} AudioFreq_t;

typedef enum {
    I2S_MCLKOUT_ON = 1,
    I2S_MCLKOUT_OFF = 0,
    I2S_MCLKOUT_UNDEF = 2,
} MclkOut_t;

typedef enum {
    I2S_STD_PHILIPS = 0,
    I2S_STD_MSB = 1,
    I2S_STD_LSB = 2,
    I2S_STD_PCM_SHORT = 3,
    I2S_STD_PCM_LONG = 4,
    I2S_STD_UNDEF = 5,
} Standard_t;

typedef enum {
    I2S_CLK_PLL = 0,
    I2S_CLK_EXT = 1,
} I2sClockSource_t;

typedef enum {
    I2S_STATE_OFF = 1,
    I2S_STATE_AMP = 2,
    I2S_STATE_RUN = 3,
    I2S_STATE_DEC = 4,

    I2S_STATE_UNDEF = 0,
} I2sState_t;

#ifndef I2S_BLOCK_SIZE
#define I2S_BLOCK_SIZE 128
#endif

#endif /* I2S_CONST_H */
