#ifndef DID_CONFIG_H
#define DID_CONFIG_H

#include "uds_types.h"

extern const DidConfig_t DidConfig[];
extern DidHandle_t DidInstance[];

uint32_t did_get_cnt(void);

#endif /*DID_CONFIG_H*/
