#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

#include "std_includes.h"

bool can_if_send(uint8_t num, const uint8_t* const data, uint16_t len) ;
bool can_if_proc(void);
bool can_if_proc_payload(uint8_t* const rx_payload, uint32_t rx_size);
bool can_if_init(void);

#endif /* CAN_INTERFACE_H */
