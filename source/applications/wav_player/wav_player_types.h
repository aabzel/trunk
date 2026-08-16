#ifndef WAV_PLAYER_TYPES_H
#define WAV_PLAYER_TYPES_H

#include "std_includes.h"
#include "wav_player_const.h"
#include "ff.h"
#include "wav_types.h"
#include "dsp_types.h"
#include "i2s_types.h"

#define WAV_PLAYER_COMMON_VARIABLES                    \
    uint32_t sample_array_size;                        \
    SampleType_t* SampleArray;                         \
    char* name;                                        \
    uint8_t num;                                       \
    uint8_t led_num;                                   \
    uint8_t fat_fs_num;                                \
    uint8_t audio_codec_num;                           \
    uint8_t wm8731_num;                                \
    uint8_t i2s_num;                                   \
    bool valid;

typedef struct {
    WAV_PLAYER_COMMON_VARIABLES
}WavPlayerConfig_t;

#define WAV_PLAYER_PLAY_VARIABLES                                    \
    char file_name[100];                                             \
    WavHeader_t WavHeader ;                                          \
    uint32_t slow_read_error;                                        \
    uint32_t read_error_cnt;                                         \
    uint32_t read_len_error_cnt;                                     \
    uint32_t cur_read_size; /*current file read size in bytes*/      \
    FIL FileToPlay;           /* [OUT] Pointer to the file object structure */                           \
    uint32_t file_size; /*total wav file size in bytes*/

typedef struct {
    WAV_PLAYER_COMMON_VARIABLES
    WAV_PLAYER_PLAY_VARIABLES
    bool play;
    bool init;
    I2sHandle_t* I2s;
    volatile WavPlayerState_t state;
    volatile WavPlayerAction_t action;
    volatile WavPlayerStatus_t status;
    uint32_t error_cnt;
    uint32_t play_need_duration_ms;
    uint32_t start_play_ms;
    uint32_t spin;
}WavPlayerHandle_t;


#endif /* WAV_PLAYER_TYPES_H */
