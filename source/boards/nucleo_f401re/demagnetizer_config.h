#ifndef DEMAGNETIZER_CONFIG_H
#define DEMAGNETIZER_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "demagnetizer_types.h"
#include "demagnetizer_dep.h"

extern const DeMagnetizerConfig_t DeMagnetizerConfig[];
extern DeMagnetizerHandle_t DeMagnetizerInstance[];

uint32_t demagnetizer_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* DEMAGNETIZER_CONFIG_H */
