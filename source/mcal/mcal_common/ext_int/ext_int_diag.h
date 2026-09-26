#ifndef EXT_INT_DIAG_H
#define EXT_INT_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_EXT_INT
#error "+HAS_EXT_INT"
#endif

#include "ext_int_types.h"

bool ext_int_diag(void);
bool ExtIntDiagConfig(const ExtIntConfig_t* const Config);
const char* ExtIntEventToStr1(const ExtIntEvent_t* const pEvent) ;
const char* ExtIntEdgeToStr(const PinIntEdge_t code);
const char* ExtIntEventToStr(const ExtIntEvent_t *const Event, ExtIntHandle_t *pNode);
const char* ExtIntEventToStr1(const ExtIntEvent_t* const pEvent);
const char* ExtIntConfigToStr(const ExtIntConfig_t* const Config);
const char* ExtIntDropToStr(const PinIntDrop_t drop);
const char* ExtIntNodeToStr(const ExtIntHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* EXT_INT_DIAG_H */
