#ifndef LIGHT_NAVIGATOR_DIAG_H
#define LIGHT_NAVIGATOR_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "light_navigator_types.h"

bool light_navigator_diag(void);
bool light_navigator_diag_one(uint8_t num);
bool LightNavigatorDiag(const LightNavigatorHandle_t* const Node);
const char* LightNavigatorDiag2Str(const LightNavigatorHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* LIGHT_NAVIGATOR_DIAG_H */
