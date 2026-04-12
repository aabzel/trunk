#ifndef MAM_CONFIG_H
#define MAM_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "mam_types.h"
#include "mam_dep.h"

extern const MamConfig_t MamConfig[];
extern MamHandle_t MamInstance[];

uint32_t mam_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* MAM_CONFIG_H */
