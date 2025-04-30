#ifndef I2S_VOLUME_H
#define I2S_VOLUME_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "i2s_types.h"

SampleType_t i2s_calc_pcm_max_ll( I2sHandle_t* const Node );
bool i2s_increase_pcms_ll(I2sHandle_t* const Node);
bool i2s_decrease_pcms_ll( I2sHandle_t* const Node);
bool i2s_volume_init_ll(I2sHandle_t* const Node);
bool i2s_volume_proc_ll(I2sHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* I2S_VOLUME_H */


