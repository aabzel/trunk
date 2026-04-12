#ifndef BIT_FIFO_CONFIG_H
#define BIT_FIFO_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bit_fifo_types.h"
#include "bit_fifo_dep.h"

extern const BitFifoConfig_t BitFifoConfig[];
extern BitFifoHandle_t BitFifoInstance[];

uint32_t bit_fifo_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* BIT_FIFO_CONFIG_H */
