#ifndef SOUND_RECORDER_TYPES_H
#define SOUND_RECORDER_TYPES_H

#include "std_includes.h"
#include "dsp_types.h"
#include "ff.h"
#include "sound_recorder_const.h"
#include "i2s_types.h"
#include "dds_const.h"

    //uint8_t channel_cnt;

#define SOUND_RECORDER_COMMON_VARIABLES                \
    char* name;                                        \
    uint32_t rx_sample_array_size;                     \
    volatile SampleType_t* RxSampleArray;              \
    volatile SampleType_t* FixRxSampleArray;           \
    FramePattern_t frame_pattern;                      \
    uint8_t sample_bitness;                            \
    uint32_t sample_freq_hz;                           \
    uint8_t led_num;                                   \
    uint8_t wm8731_num;                                \
    uint8_t i2s_num;                                   \
    uint8_t num;                                       \
    bool valid;

typedef struct {
    SOUND_RECORDER_COMMON_VARIABLES
}SoundRecorderConfig_t;

typedef struct {
    SOUND_RECORDER_COMMON_VARIABLES
    bool init;
    bool is_rec;
    uint32_t sample_cnt;
    uint32_t rec_cnt;
    uint32_t spin;
    volatile SoundRecorderState_t state;
    volatile SoundRecorderAction_t action;
    volatile I2sHandle_t* I2s;
    char file_name[100];
    uint32_t total_file_size;
    uint32_t cur_save_size;
    uint32_t start_rec_ms;
    uint32_t stop_rec_ms;
    uint32_t duration_ms;
    uint32_t wr_ok_cnt;
    uint32_t long_write_error_cnt;
    uint32_t error_size_cnt;
    uint32_t error_cnt;
    uint32_t i2s_error_cnt;
#ifdef HAS_FAT_FS
    FRESULT fat_fs_err_code;
    FIL FileToRec;           /* [OUT] Pointer to the file object structure */
#endif
    uint32_t data_size; /*WAV file payload size*/
}SoundRecorderHandle_t ;


#endif /* SOUND_RECORDER_TYPES_H */
