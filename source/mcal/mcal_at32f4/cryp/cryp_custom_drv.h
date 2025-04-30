#ifndef CRYP_CUSTOM_DRV_H
#define CRYP_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cryp_cbc_drv.h"
#include "cryp_ecb_drv.h"
#include "artery_at32f4xx.h"

#ifndef HAS_CRYP
#error "+HAS_CRYP"
#endif

#ifndef HAS_CUSTOM
#error "+HAS_CUSTOM"
#endif

bool cryp_hw_init(void);
int8_t CrypInstance2Num(CRYP_TypeDef* Instance);

#ifdef __cplusplus
}
#endif

#endif /* CRYP_CUSTOM_DRV_H */
