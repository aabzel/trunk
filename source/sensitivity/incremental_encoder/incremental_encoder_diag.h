#ifndef INCREMENTAL_ENCODER_DIAG_H
#define INCREMENTAL_ENCODER_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "incremental_encoder_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_INCREMENTAL_ENCODER
#error "+HAS_INCREMENTAL_ENCODER"
#endif

#ifndef HAS_INCREMENTAL_ENCODER_DIAG
#error "+HAS_INCREMENTAL_ENCODER_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool incremental_encoder_diag(void);
const char* IncrementalEncoderStateToStr(const IncrementalEncoderState_t state);
bool incremental_encoder_diag_one(uint8_t num);
const char* IncrementalEncoderInputToStr(const IncrementalEncoderInput_t input );
const char* IncrementalEncoderConfigToStr(const IncrementalEncoderConfig_t* const Config);
const char* IncrementalEncoderNodeToStr(const IncrementalEncoderHandle_t* const Node);
const char* IncrementalEncoderMainToStr(const IncrementalEncoderHandle_t* const Node);
const char* IncrementalEncoderEventToStr(const IncrementalEncoderEvent_t* const Event,
                                         IncrementalEncoderHandle_t *Node);

#ifdef __cplusplus
}
#endif

#endif /* INCREMENTAL_ENCODER_DIAG_H  */
