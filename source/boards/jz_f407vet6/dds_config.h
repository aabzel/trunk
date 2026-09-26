#ifndef DDS_CONFIG_H
#define DDS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dds_type.h"

typedef enum {
     DDS_NUM_CHIRP ,
     DDS_NUM_SIN,
     DDS_NUM_DAC_TEST ,
     DDS_NUM_WAV_CH1 ,
     DDS_NUM_WAV_CH2 ,
     DDS_NUM_CNT,
}DdsLegalNums_t;


extern const DdsConfig_t DdsConfig[];
extern DdsHandle_t DdsInstance[];

uint32_t dds_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /*DDS_CONFIG_H*/
