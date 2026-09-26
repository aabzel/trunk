#ifndef BPSK_CONFIG_H
#define BPSK_CONFIG_H

#include "bpsk_types.h"

extern const BpskConfig_t BpskConfig[];
extern BpskHandle_t BpskInstance[];

uint32_t bpsk_get_cnt(void);

#endif /* BPSK_CONFIG_H  */
