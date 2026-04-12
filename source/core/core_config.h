#ifndef CORE_CONFIG_H
#define CORE_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "core_types.h"

extern const CoreConfig_t CoreConfig[];
extern CoreHandle_t CoreInstance[];

uint32_t core_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* CORE_CONFIG_H */
