#ifndef LORA_WRITER_H
#define LORA_WRITER_H

#include <stdbool.h>

#include "writer_generic.h"

#ifndef HAS_LORA
#error "LoRa macro must be defined"
#endif

#define LORA_TX_ARRAY_SIZE 255U

extern generic_writer_t dbg_lora_o;
#define DBG_LORA_STREAM (&dbg_lora_o.s)

bool lora_writer_transmit(struct generic_writer_s* s);

#endif /* LORA_WRITER_H */
