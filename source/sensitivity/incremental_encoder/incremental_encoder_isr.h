#ifndef INCREMENTAL_ENCODER_ISR_H
#define INCREMENTAL_ENCODER_ISR_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"
#include "incremental_encoder_config.h"
#include "incremental_encoder_types.h"

bool incremental_encoder_proc_event(const Pad_t Pad, const PinIntEdge_t edge_effective) ;

#ifdef __cplusplus
}
#endif

#endif /* INCREMENTAL_ENCODER_ISR_H */
