#ifndef TRNG_CONFIG_H
#define TRNG_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "trng_types.h"
#include "trng_dep.h"

extern const tRngConfig_t tRngConfig[];
extern tRngHandle_t tRngInstance[];

uint32_t trng_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* TRNG_CONFIG_H */
