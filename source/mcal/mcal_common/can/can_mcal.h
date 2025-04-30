#ifndef CAN_GENERAL_DRV_H
#define CAN_GENERAL_DRV_H

#include "can_types.h"
#include "can_config.h"
#ifdef HAS_CAN_DIAG
#include "can_diag.h"
#endif
#include "can_custom_drv.h"

CanHandle_t* CanGetNode(uint8_t num);
const CanConfig_t* CanGetConfig(uint8_t num);

bool can_is_message_valid(CanMessage_t* const Message);
bool can_proc_one(uint8_t num);

bool can_api_transmit_buff(uint8_t num, uint16_t id, const uint8_t* const data, uint8_t size);
bool can_api_transmit_data(uint8_t num, const CanMessage_t* const Message);
bool can_proc(void);
bool can_check(void);
bool can_heartbeat_proc(void);
bool can_heartbeat_proc_one(uint8_t num) ;
bool can_init_one(uint8_t num);
bool can_init(void);
bool can_api_baudrate_set(uint8_t num, uint32_t baudrate);
bool can_api_baudrate_get(uint8_t num, uint32_t * const bit_rate);

#endif /* CAN_GENERAL_DRV_H  */
