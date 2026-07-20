#ifndef LOOPBACK_AUDIO_TYPES_H
#define LOOPBACK_AUDIO_TYPES_H

#include "std_includes.h"
#include "loopback_audio_const.h"
#include "dsp_types.h"
#include "ff.h"
#include "wav_types.h"
#include "i2s_types.h"

#if 0
    bool interrupt_on;
    uint8_t wm8731_num;
    uint8_t i2s_num;
#endif

#define LOOPBACK_AUDIO_COMMON_VARIABLES                \
    uint32_t sample_array_size;                        \
    SampleType_t* RxSampleArray;                       \
    SampleType_t* TxSampleArray;                       \
    uint8_t led_num;                                   \
    char* name;                                        \
    uint8_t num;                                       \
    uint8_t rec_num;                                   \
    uint8_t player_num;                                \
    bool valid;

typedef struct {
    LOOPBACK_AUDIO_COMMON_VARIABLES
}LoopbackAudioConfig_t;


typedef struct {
    LOOPBACK_AUDIO_COMMON_VARIABLES
    bool tx_rx_180;
    bool rec_need;
    bool init;
    LoopbackAudioState_t state;
    LoopbackAudioAction_t action;
    uint32_t error_cnt;
    char rec_file_name[80];
    char play_file_name[80];
    uint32_t spin;
}LoopbackAudioHandle_t;


#endif /* LOOPBACK_AUDIO_TYPES_H */
