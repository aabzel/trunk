#ifndef DDS_CONFIG_H
#define DDS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dds_type.h"

#ifndef HAS_DDS
#error  "+HAS_DDS"
#endif /*HAS_DDS*/
#define DDS_MAX_SAMPLE_ARRAY 16000
typedef enum {
     DDS_I2S_NUM = 1,
     DDS_GREEN_LED_NUM = 2,
     DDS_RED_LED_NUM = 3,
     DDS_DFT_TEST_NUM = 4,
     DDS_MODULATOR_NUM = 5,
     DDS_FFT_TEST_NUM = 6,
     DDS_CHIRP_NUM = 7,
     DDS_WAV_CH1 = 8,
     DDS_WAV_CH2 = 9,
}DacTypes_t;

extern const DdsConfig_t DdsConfig[];
extern DdsHandle_t DdsInstance[];

uint32_t dds_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /*DDS_CONFIG_H*/
