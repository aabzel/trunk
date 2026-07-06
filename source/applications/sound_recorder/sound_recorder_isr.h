#ifndef SOUND_RECORDER_ISR_H
#define SOUND_RECORDER_ISR_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"
#include "sound_recorder_config.h"
#include "sound_recorder_types.h"
#include "i2s_types.h"


bool I2xRxHalfCallbackCustom(I2sHandle_t* const Node);
bool I2xRxDoneCallbackCustom(I2sHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* SOUND_RECORDER_ISR_H */
