#ifndef INCREMENTAL_ENCODER_MCAL_H
#define INCREMENTAL_ENCODER_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "incremental_encoder_config.h"
#include "incremental_encoder_types.h"
#include "incremental_encoder_isr.h"

#ifdef HAS_INCREMENTAL_ENCODER_DIAG
#include "incremental_encoder_diag.h"
#endif

/* API */
IncrementalEncoderHandle_t* IncrementalEncoderGetNode(uint8_t num);
IncrementalEncoderHandle_t* IncrementalEncoderPadToNode(Pad_t Pad);
const IncrementalEncoderConfig_t* IncrementalEncoderGetConfig(uint8_t num);
bool IncrementalEncoderIsValidConfig(const IncrementalEncoderConfig_t* const Config);

#ifdef HAS_INCREMENTAL_ENCODER_CUSTOM
const IncrementalEncoderInfo_t* IncrementalEncoderGetInfo(uint8_t num);
#endif


bool incremental_encoder_mcal_init(void);
bool incremental_encoder_init_custom(void);
bool incremental_encoder_init_common(const IncrementalEncoderConfig_t* const Config, IncrementalEncoderHandle_t* const Node);
bool incremental_encoder_init_node(IncrementalEncoderHandle_t* const Node);
bool incremental_encoder_init_one(uint8_t num);

bool incremental_encoder_proc_one(uint8_t num);
bool incremental_encoder_proc(void);

/*setters*/
bool incremental_encoder_set_0(uint8_t num);

/*getters*/
IncrementalEncoderState_t incremental_encoder_read_state( IncrementalEncoderHandle_t *Node );
int32_t incremental_encoder_get_counter(const uint8_t num);
float  incremental_encoder_get_revolutions(const uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* INCREMENTAL_ENCODER_MCAL_H */
