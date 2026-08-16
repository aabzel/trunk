#ifndef DDS_CONST_H
#define DDS_CONST_H

#include "dds_dep.h"

#define DDS_STATIC_CHANNEL_CNT 100
#define DDS_PERIOD_US 1000

typedef enum {
    DDS_MODE_STATIC ,
    DDS_MODE_PWM ,
    DDS_MODE_SIN ,
    DDS_MODE_SAW ,
    DDS_MODE_FENCE ,
    DDS_MODE_PULSE_TRAIN ,
    DDS_MODE_CHIRP ,
    DDS_MODE_BARKER_13 ,
    DDS_MODE_DTMF ,
    DDS_MODE_BPSK ,
    DDS_MODE_M_SEQ ,
    DDS_MODE_CNT
} DdsMode_t;

typedef enum {
    DDS_STATE_PLAY = 1,
    DDS_STATE_IDLE = 2,

    DDS_STATE_UNDEF = 0,
} DdsState_t;

#if 0
#endif
typedef enum {
    DDS_PLAYER_UNDEF = 0,
    DDS_PLAYER_DAC_CHANNEL1 ,
    DDS_PLAYER_DAC_CHANNEL2  ,
#ifdef HAS_I2S
    DDS_PLAYER_I2S0 ,
    DDS_PLAYER_I2S1 ,
    DDS_PLAYER_I2S2 ,
    DDS_PLAYER_I2S3 ,
    DDS_PLAYER_I2S4 ,
    DDS_PLAYER_I2S5 ,
    DDS_PLAYER_I2S6 ,
#endif
    DDS_PLAYER_WAV_FILE  ,
    DDS_PLAYER_CSV_FILE  ,

} DdsPlayer_t;

typedef enum {
    CHANNEL_UNDEF = 0,
    CHANNEL_ONLY_RIGHT = 1,
    CHANNEL_ONLY_LEFT = 2,
    CHANNEL_BOTH = 3,
    CHANNEL_MONO = 4,

}FramePattern_t;

#endif /* DDS_CONST_H*/
