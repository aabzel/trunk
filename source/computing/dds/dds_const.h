#ifndef DDS_CONST_H
#define DDS_CONST_H

#include "dds_dep.h"

#define DDS_STATIC_CHANNEL_CNT 100
#define DDS_PERIOD_US 1000

typedef enum {
    DDS_MODE_STATIC = 0U,
    DDS_MODE_PWM = 1U,
    DDS_MODE_SIN = 2U,
    DDS_MODE_SAW = 3U,
    DDS_MODE_FENCE = 4U,
    DDS_MODE_PULSE_TRAIN = 5U,
    DDS_MODE_CHIRP = 6U,
    DDS_MODE_DTMF = 7U,
    DDS_MODE_BPSK = 8U,

    DDS_UNDEF = 8U
} DdsMode_t;

typedef enum {
    DDS_STATE_PLAY = 1,
    DDS_STATE_IDLE = 2,

    DDS_STATE_UNDEF = 0,
} DdsState_t;

typedef enum {
    DDS_PLAYER_I2S0 = 0U,
    DDS_PLAYER_I2S1 = 1U,
    DDS_PLAYER_I2S2 = 2U,
    DDS_PLAYER_I2S3 = 3U,
    DDS_PLAYER_I2S4 = 4U,
    DDS_PLAYER_I2S5 = 5U,
    DDS_PLAYER_I2S6 = 6U,
    DDS_PLAYER_WAV_FILE = 7U,
    DDS_PLAYER_CSV_FILE = 8U,
    DDS_PLAYER_UNDEF = 8U
} DdsPlayer_t;

typedef enum {
    CHANNEL_ONLY_RIGHT=1,
    CHANNEL_ONLY_LEFT=2,
    CHANNEL_BOTH=3,
    CHANNEL_MONO=4,

    CHANNEL_UNDEF=0,
}FramePattern_t;

#endif /* DDS_CONST_H*/
