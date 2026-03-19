
#ifndef TBFP_CONFIG_H
#define TBFP_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "tbfp_types.h"

#ifndef HAS_TBFP
#error " +HAS_TBFP"
#endif

//#define TBFP_MAX_PAYLOAD (256)

extern const TbfpConfig_t TbfpConfig[];
extern TbfpProtocol_t TbfpInstance[];

uint32_t tbfp_get_cnt(void);

#endif /* TBFP_CONFIG_H */
