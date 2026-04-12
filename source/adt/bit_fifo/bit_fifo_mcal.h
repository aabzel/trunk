#ifndef BIT_FIFO_MCAL_H
#define BIT_FIFO_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bit_fifo_config.h"
#include "bit_fifo_types.h"

#ifdef HAS_BIT_FIFO_DIAG
#include "bit_fifo_diag.h"
#endif

BitFifoHandle_t* BitFifoGetNode(uint8_t num);
const BitFifoConfig_t* BitFifoGetConfig(uint8_t num);

bool bit_fifo_mcal_init(void);

/*buffer_bytes Size of buffer in bytes (capacity = buffer_bytes * 8 bits). */
bool bit_fifo_init(BitFifoHandle_t *const Node, uint8_t * const buffer, const uint32_t buffer_bytes) ;


/*setters*/
/*   Push a single bit into the FIFO.       bit   Bit value (0 or 1). Only LSB is used. */
bool bit_fifo_push(BitFifoHandle_t *const Node, const uint8_t bit);


/*getters*/
bool bit_fifo_pull(BitFifoHandle_t *const Node, uint8_t *const bit);


/* Peek at the oldest bit in the FIFO without removing it.  */
bool bit_fifo_peek(const BitFifoHandle_t *const Node, uint8_t *const bit);

int32_t bit_fifo_get_count(const BitFifoHandle_t *const Node);



bool bit_fifo_push_array(BitFifoHandle_t* const Node, uint8_t* const inArr,const  uint32_t arrLen);

bool bit_fifo_pull_array(const BitFifoHandle_t* const Node, uint8_t* const outArr,
                         const uint32_t arr_size, uint32_t* const outLen);

bool bit_fifo_peek_array(BitFifoHandle_t* const Node, uint8_t* const outArr, uint32_t* const outLen);



#ifdef __cplusplus
}
#endif

#endif /* BIT_FIFO_MCAL_H */
