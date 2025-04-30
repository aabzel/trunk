#ifndef DDS_TYPE_H
#define DDS_TYPE_H

// DDS - Direct Digital Synthesis


#include "std_includes.h"
#include "dds_const.h"

#ifdef HAS_AUDIO
#include "audio_types.h"
#endif
    // uint32_t sample_size;

#define DDS_MCAL_COMMON_VARIABLE   \
    SampleType_t* sample_array;    \
    uint32_t array_size;           \
    uint8_t num;                   \
    bool valid;                    \
    double phase_ms;               \
    double duty_cycle;             \
    double frequency;              \
    double frequency2;             \
    double signal_diration_s;      \
    DdsPlayer_t player;            \
    SampleType_t amplitude;        \
    uint32_t sample_per_second;    \
    DdsMode_t dds_mode;            \
    uint8_t sample_bitness;        \
    FramePattern_t frame_pattern;  \
    char* name;                    \
    SampleType_t offset;

typedef struct {
    DDS_MCAL_COMMON_VARIABLE
} DdsConfig_t;

typedef struct {
    DDS_MCAL_COMMON_VARIABLE
    SampleType_t cur_sample;
    SampleType_t prev_sample;
    SampleType_t tx_sample; // one
    double tx_sample_d ;
    DdsState_t state;
    uint64_t play_off_time_stamp_ms;
    uint32_t sample_cnt;
    uint64_t duration_ms;
    bool init;
    bool proc_on;
} DdsHandle_t;

#endif /*DDS_TYPE_H*/
