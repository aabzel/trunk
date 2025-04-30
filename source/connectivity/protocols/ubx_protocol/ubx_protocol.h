#ifndef UBX_PROTOCOL_H
#define UBX_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ubx_constants.h"
#include "ubx_types.h"

extern UbloxProtocol_t UbloxProtocol;
extern StatClass_t tableRxClass[UBX_CLA_CNT];

bool ubx_reset_rx(void);
bool ublox_protocol_init(void);
bool ubx_proc_byte(uint8_t rx_byte);
bool ubx_print_frame(uint8_t* frame);
bool ubx_update_stat(uint8_t val_class);
bool ubx_print_frame(uint8_t* frame);
uint16_t ubx_calc_crc16(uint8_t* array, uint16_t len);
uint8_t ubx_key_len_2bytes(uint8_t code);
uint8_t ubx_keyid_2len(uint32_t key_id);
bool ubx_wait_ack(uint32_t wait_pause_ms);
#ifdef __cplusplus
}
#endif

#endif /* UBX_PROTOCOL_H */
