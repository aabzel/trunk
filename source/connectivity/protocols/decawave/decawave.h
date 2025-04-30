#ifndef DECAWAVE_PROTOCOL_H
#define DECAWAVE_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "decawave_proto_config.h"
#include "decawave_types.h"
#ifdef HAS_UWB
#include "uwb_if_types.h"
#endif

#ifndef HAS_DECAWAVE
#error "+HAS_DECAWAVE"
#endif

const DecaWaveConfig_t* DecaWaveGetConfig(uint8_t num);
DecaWaveHandle_t* DecaWaveGetNode(uint8_t num);

bool decawave_dist_get_ll( DecaWaveHandle_t* const Node, double* const dist);
bool decawave_proc_payload(DecaWaveHandle_t* const Node);
bool decawave_proc_data(DecaWaveHandle_t* const Node);
bool decawave_proc(uint8_t num, const uint8_t* const arr, uint16_t length);
bool decawave_send(uint8_t num, DwcaMess_t mess_type, uint16_t destination_id, UwbVatiable_t var_id, uint8_t* buff,
                   uint32_t size);
bool decawave_send_ll(DecaWaveHandle_t* const Node, DwcaMess_t mess_type, uint16_t destination_id, UwbVatiable_t var_id,
                      uint8_t* buff, uint32_t size);
#ifdef HAS_UWB
bool decawave_send_poll(uint8_t num, const UwbIdInfo_t* const IdInfo);
#endif
bool decawave_send_final(uint8_t num, UwbVatiable_t var_id, uint8_t* buff, uint32_t size);
bool decawave_send_response_payload(uint8_t num, uint16_t destination, UwbVatiable_t var_id, uint8_t* buff,
                                    uint32_t size);
bool decawave_send_response_poll(uint8_t num);
bool decawave_init(void);
bool decawave_dist_get(uint8_t num, double* const dist);

#ifdef __cplusplus
}
#endif

#endif /* DECAWAVE_PROTOCOL_H */
