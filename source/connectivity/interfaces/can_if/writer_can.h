#ifndef SRC_CAN_WRITER_H
#define SRC_CAN_WRITER_H

#include <stdbool.h>

#include "writer_generic.h"

#define CAN_TX_ARRAY_SIZE 8U

#ifndef HAS_CAN
#error "CAN hardware is not determined"
#endif

extern generic_writer_t can_o;
#define DBG_CAN_STREAM (&can_o.s)

bool can_writer_transmit(struct generic_writer_s* s);

#endif /* SRC_CAN_WRITER_H */
