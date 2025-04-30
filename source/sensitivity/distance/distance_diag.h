#ifndef DISTANCE_DIAG_H
#define DISTANCE_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "distance_types.h"

bool distance_diag(uint8_t num);
const char* DistanceState2Str(DistanceState_t state);
const char* DistanceInPut2Str(DistanceInput_t input);
const char* DistanceNode2Str(const DistanceHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* DISTANCE_DIAG_H */
