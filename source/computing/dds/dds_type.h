#ifndef DDS_TYPE_H
#define DDS_TYPE_H

// DDS - Direct Digital Synthesis


#include "std_includes.h"
#include "dds_const.h"
#include "dsp_types.h"
#include "interfaces_types.h"

#define DDS_MCAL_COMMON_VARIABLE   \
    uint32_t total_sample_cnt;     \
    uint32_t sample_cnt;           \
    SampleType_t* sample_array;    \
    uint8_t num;                   \
    bool valid;                    \
    float phase_ms;                \
    float duty_cycle;              \
    float frequency;               \
    float frequency2;              \
    float signal_diration_s;       \
    InterfaceType_t player;        \
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
    SampleType_t tx_sample;
    float tx_sample_d;
    DdsState_t state;
    uint64_t play_off_time_stamp_ms;
    uint64_t duration_ms;
    bool init_done;
    bool proc_on;
} DdsHandle_t;

#endif /*DDS_TYPE_H*/
