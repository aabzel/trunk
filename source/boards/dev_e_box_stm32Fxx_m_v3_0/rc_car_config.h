#ifndef RC_CAR_CONFIG_H
#define RC_CAR_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "rc_car_types.h"
#include "rc_car_dep.h"

extern const RcCarConfig_t RcCarConfig[];
extern RcCarHandle_t RcCarInstance[];

uint32_t rc_car_get_cnt(void);


#ifdef __cplusplus
}
#endif

#endif /* RC_CAR_CONFIG_H */
