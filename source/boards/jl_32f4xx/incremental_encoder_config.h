#ifndef INCREMENTAL_ENCODER_CONFIG_H
#define INCREMENTAL_ENCODER_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "incremental_encoder_types.h"
#include "incremental_encoder_dep.h"

extern const IncrementalEncoderConfig_t IncrementalEncoderConfig[];
extern IncrementalEncoderHandle_t IncrementalEncoderInstance[];

uint32_t incremental_encoder_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* INCREMENTAL_ENCODER_CONFIG_H */
