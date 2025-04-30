#ifndef CRYP_CONFIG_GEN_H
#define CRYP_CONFIG_GEN_H

#include <stdbool.h>
#include <stdint.h>

#include "cryp_types.h"

#ifndef HAS_CRYP
#error "Add HAS_CRYP"
#endif /*HAS_CRYP*/

#define CRYP_SW_NUM 1

extern const CrypConfig_t CrypConfigLut[];
extern CrypHandle_t CrypItem[];

uint32_t cryp_get_cnt(void);

#endif /* CRYP_CONFIG_GEN_H  */
