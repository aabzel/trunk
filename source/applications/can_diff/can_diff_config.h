#ifndef CAN_DIFF_CONFIG_H
#define CAN_DIFF_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_diff_types.h"
#include "can_diff_dep.h"

extern const CanDiffConfig_t CanDiffConfig[];
extern CanDiffHandle_t CanDiffInstance[];

uint32_t can_diff_get_cnt(void);
uint32_t can_diff_inst_get_cnt(void);


#ifdef __cplusplus
}
#endif

#endif /* CAN_DIFF_CONFIG_H */
