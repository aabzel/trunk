
#ifndef DTMF_IF_H
#define DTMF_IF_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "dtmf_config.h"
#include "dtmf_types.h"

DtmfHandle_t* DtmfGetNode(uint8_t num);
const DtmfConfig_t* DtmfGetConfig(uint8_t num);
bool dtmf_init_one(uint8_t num);
bool dtmf_send_char(uint8_t num, char letter, uint32_t duration_ms);
bool dtmf_send(uint8_t num, const uint8_t* const data, size_t len, uint32_t duration_ms);
bool dtmf_init(void);
bool dtmf_calc_periods(uint32_t init_i, char letter, uint32_t* const N, uint32_t* const M);

#endif /* DTMF_IF_H */
