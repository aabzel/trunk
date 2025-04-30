#ifndef RLE_DIAG_H
#define RLE_DIAG_H

#include <stdbool.h>

#include "rle_types.h"

const char* RleDecodeInput2Str(RleDecoderInput_t input);
const char* RleDecodeState2Str(RleDecoderState_t state);
bool RleDecoderDiag(RleDecodeFsm_t* Node);
bool RleEncoderDiag(RleEncodeFsm_t* Node);

#endif
