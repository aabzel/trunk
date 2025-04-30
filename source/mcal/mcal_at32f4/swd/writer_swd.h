#ifndef SRC_SWD_WRITER_H
#define SRC_SWD_WRITER_H

#include <stdbool.h>

#include "writer_generic.h"

#define SWD_TX_ARRAY_SIZE 600U

#ifndef HAS_SWD
#error "+ HAS_SWD"
#endif

extern generic_writer_t swd_o;
#define DBG_SWD_STREAM (&swd_o.s)

bool swd_writer_init(void);
bool swd_writer_transmit(struct generic_writer_s* s);

#endif /* SRC_SWD_WRITER_H */
