#ifndef DDS_CONFIG_H
#define DDS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dds_type.h"

#ifndef HAS_DDS
#error  "+HAS_DDS"
#endif

#define DDS_MAX_SAMPLE_ARRAY (5*96000)

typedef enum {
     DDS_NUM_INDEF = 0,
     DDS_NUM_CHIRP ,
     DDS_NUM_SIN,
     DDS_NUM_DFT_TEST ,
     DDS_NUM_MODULATOR ,
     DDS_NUM_FFT_TEST ,
     DDS_NUM_WAV_CH1 ,
     DDS_NUM_WAV_CH2 ,
#ifdef HAS_LED
     DDS_NUM_GREEN_LED ,
     DDS_NUM_RED_LED ,
#endif
     DDS_NUM_CNT ,
}DacTypes_t;


extern const DdsConfig_t DdsConfig[];
extern DdsHandle_t DdsInstance[];

uint32_t dds_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /*DDS_CONFIG_H*/
