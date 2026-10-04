#ifndef DDS_CONFIG_H
#define DDS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dds_type.h"

typedef enum {
     DDS_DAC_TEST = 1,
}DacTypes_t;

extern const DdsConfig_t DdsConfig[];
extern DdsHandle_t DdsInstance[];

uint32_t dds_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /*DDS_CONFIG_H*/
