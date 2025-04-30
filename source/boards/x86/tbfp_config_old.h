
#ifndef TBFP_CONFIG_H
#define TBFP_CONFIG_H

#include "std_includes.h"
#include "tbfp_types.h"

#ifndef HAS_TBFP
#error " +HAS_TBFP"
#endif

#define TBFP_MAX_TX_BUFF 512U

extern const TbfpConfig_t TbfpConfig[];
extern volatile TbfpHandle_t TbfpInstance[];

uint32_t tbfp_get_cnt(void);

#endif /* TBFP_CONFIG_H */
