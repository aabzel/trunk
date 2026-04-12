#ifndef BIT_FIFO_DIAG_H
#define BIT_FIFO_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bit_fifo_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_BIT_FIFO
#error "+HAS_BIT_FIFO"
#endif

#ifndef HAS_BIT_FIFO_DIAG
#error "+HAS_BIT_FIFO_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool bit_fifo_diag(void);
bool bit_fifo_diag_one(uint8_t num);

const char* BitFifoMemToBitStr(const uint8_t* const data, const uint32_t size) ;
const char* BitFifoConfigToStr(const BitFifoConfig_t* const Config);
const char* BitFifoNodeToStr(const BitFifoHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* BIT_FIFO_DIAG_H  */
