#ifndef IR_CAR_CONFIG_H
#define IR_CAR_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "ir_car_types.h"
#include "ir_car_dep.h"

extern const IrCarConfig_t IrCarConfig[];
extern IrCarHandle_t IrCarInstance[];

uint32_t ir_car_get_cnt(void);


#ifdef __cplusplus
}
#endif

#endif /* IR_CAR_CONFIG_H */
