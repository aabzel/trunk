#ifndef QUAD_MIX_4FS_DIAG_H
#define QUAD_MIX_4FS_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include <std_includes.h>
#include "quad_mix_4fs_types.h"


const char* QuadMix4fsAfterMuxNodeToStr(const  QuadMix4fsHandle_t* const Node);
const char* QuadMix4fsNodeToStr(const  QuadMix4fsHandle_t* const Node);
const char* QuadMix4fsShortNodeToStr(const  QuadMix4fsHandle_t* const Node);
const char* QuadMix4fsConfigToStr(const  QuadMix4fsConfig_t* const Config);

bool QuadMix4fsDiagConfig(const QuadMix4fsConfig_t* const Config);
bool quad_mix_4fs_diag(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* QUAD_MIX_4FS_DIAG_H */
