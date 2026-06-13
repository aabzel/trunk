#ifndef ENCODER_LAMP_CONFIG_H
#define ENCODER_LAMP_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "encoder_lamp_types.h"
#include "encoder_lamp_dep.h"

extern const EncoderLampConfig_t EncoderLampConfig[];
extern EncoderLampHandle_t EncoderLampInstance[];

uint32_t encoder_lamp_get_cnt(void);


#ifdef __cplusplus
}
#endif

#endif /* ENCODER_LAMP_CONFIG_H */
