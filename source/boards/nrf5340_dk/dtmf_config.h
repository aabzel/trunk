#ifndef DTMF_CONFIG_H
#define DTMF_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "dtmf_types.h"

extern const DtmfConfig_t DtmfConfig[];
extern DtmfHandle_t DtmfInstance[];

uint32_t dtmf_get_cnt(void);

#endif /* DTMF_CONFIG_H  */
