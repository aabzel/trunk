#ifndef WAV_TYPES_H
#define WAV_TYPES_H

/*
 https://audiocoding.cc/articles/2008-05-22-wav-file-structure/
 * */
#include "std_includes.h"

#include <stdio.h>
#include <stddef.h>

#include "wav_const.h"
#include "data_types.h"
#include "time_mcal.h"
#include "file_mcal_types.h"

#ifdef HAS_CRC
#include "crc_types.h"
#endif

typedef struct{
    uint32_t channels ;
    uint32_t sample_size;
    uint32_t sample_cnt;
    uint32_t sampling_frequency_hz;
    bool valid;
    uint32_t data_size;
    float duration_s ;
    float sample_time_s ;
}WavInfo_t;

typedef struct {
    int16_t left;  /**/
    int16_t right;  /**/
}__attribute__((packed)) WavSample16_t;

/* 44 byte
   Little-Endian Do Not changr order*/
typedef union {
    uint8_t buff[44];
    struct {
        /* Do not change order! */
        uint32_t chunkId;                /* contain letters    RIFF*/
        uint32_t chunkSize;              /* Chunk size this header size*/
        uint32_t format;                 /* WAVE 0x57415645*/
        uint32_t subchunk1Id;            /* Chunk ID: fmt 0x666d7420*/
        uint32_t subchunk1Size;          /* Chunk Data Size:  16 + extra format bytes*/

        uint16_t audioFormat;            /* Compression code   PCM = 1	*/
        uint16_t numChannels;            /* Number of channels: mono= 1, stereo= 2 */
        uint32_t sampleRate;             /* Sample rate, Sampling Frequency in Hz*/
        uint32_t aver_bytes_per_sec;     /* Average Bytes Per Second, The number of bytes transferred per second of playback.*/
        uint16_t blockAlign;             /* Block align, Average bytes per second, The number of bytes for one sample, including all channels.*/
        uint16_t bitsPerSample;          /* Significant bits per sample, The number of bits in a sample. The so-called "depth" or precision of sound. 8 bit, 16 bit, etc.*/

        uint32_t subchunk2Id;/*Chunk ID: data*/
        uint32_t subchunk2Size;/*Chunk Data Size: Size of the audio data (little-endian )*/
    } __attribute__((packed));
} __attribute__((packed)) WavHeader_t;


#define WAV_COMMON_VARIABLES            \
    char* file_name_dflt;               \
    char* name;                         \
    uint32_t channels ;                 \
    uint32_t block_align;               \
    uint32_t sample_cnt ;               \
    uint8_t bits_per_sample;            \
    uint32_t sampling_frequency_hz;     \
    uint8_t file_num;                   \
    uint8_t num;                        \
    bool valid;

typedef struct{
    WAV_COMMON_VARIABLES
}WavConfig_t;

typedef struct{
    WAV_COMMON_VARIABLES
    bool init;
    int32_t real_file_size;
    uint32_t data_size;
    uint32_t real_data_size;
    int32_t data_diff_size;
    float sample_time_s ;
    float duration_s ;
    uint8_t*  data; //little-endian
    char fileName[150];
}WavHandle_t;




#endif /* WAV_TYPES_H */
