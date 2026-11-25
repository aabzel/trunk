#ifndef CAN_CAT_CONFIG_H
#define CAN_CAT_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_cat_types.h"
#include "can_cat_dep.h"

extern const CanCatConfig_t CanCatConfig[];
extern CanCatHandle_t CanCatInstance[];

uint32_t can_cat_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* CAN_CAT_CONFIG_H */
