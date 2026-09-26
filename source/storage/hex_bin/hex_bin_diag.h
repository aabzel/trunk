#ifndef HEX_BIN_DIAG_H
#define HEX_BIN_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "hex_bin_types.h"

const char* NodeToProgressStr(const HexBinHandle_t* const Node);
const char* DataToStr(const uint8_t* const data, uint8_t size);
const char* HexFrameToStr(const HexFrame_t* const Frame);
const char* HexNodeToStr(const HexBinHandle_t* const Node);
const char* HexRecTypeToStr(HexRecType_t rec_type);
bool HexNodeDiag(const HexBinHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* HEX_BIN_DIAG_H */
