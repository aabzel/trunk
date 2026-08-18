
#ifndef DECADRIVER_API_H
#define DECADRIVER_API_H

#include <stdbool.h>
#include <stdint.h>

#include "decadriver_config.h"
#include "decadriver_types.h"

bool decadriver_set_rx(void);
bool decadriver_wait_tx_done_ms(uint32_t wait_pause_ms);
bool decadriver_read_data(void);
bool dwm1000_reset(void);
bool decadriver_init(void);
bool decadriver_is_connected(DecaDriverInstance_t* const item);
bool decadriver_proc(void);
bool decadriver_tx(const uint8_t* const buff, uint32_t size);

#endif /* DECADRIVER_API_H*/
