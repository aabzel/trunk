#ifndef ACC_CONFIG_H
#define ACC_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "acc_types.h"
#include "acc_dep.h"

extern const AccConfig_t AccConfig[];
extern AccHandle_t AccInstance[];

uint32_t acc_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* ACC_CONFIG_H */
