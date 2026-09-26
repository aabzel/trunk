#ifndef WAV_DIAG_H
#define WAV_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "wav_types.h"
#include "std_includes.h"

bool WavHeaderToFileName(const WavHeader_t* const Node, char* const file_name, uint32_t size);
const char* WavHeaderToStr(const WavHeader_t* const Header);
const char* WavNodeToStr(const WavHandle_t* const Node);
const char* WavInfoToStr(const WavInfo_t* const Info);

#ifdef __cplusplus
}
#endif

#endif /* WAV_DIAG_H */
