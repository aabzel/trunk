
#ifndef MX25R6435F_CONFIG_H
#define MX25R6435F_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "mx25r6435f_types.h"

#ifndef HAS_MX25R6435F
#error "+HAS_MX25R6435F"
#endif

extern const Mx25r6435fConfig_t Mx25r6435fConfig;
extern Mx25r6435fItem_t Mx25r6435fItem;

uint32_t mx25r6435f_get_config_cnt(void);

#endif /* MX25R6435F_CONFIG_H */
