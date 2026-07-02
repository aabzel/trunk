#ifndef WAV_DIAG_H
#define WAV_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "wav_types.h"

bool WavHeaderToFileName(const WavHeader_t* const Header, char* const file_name, uint32_t size);

const char* WavHandleToStr(const WavHandle_t* const Handle);
const char* WavHeaderToStr(const WavHeader_t* const Header);
const char* WavNodeToStr(const WavHandle_t* const Node);


#ifdef __cplusplus
}
#endif

#endif /* WAV_DIAG_H */
