#ifndef GPIO_MAPPER_CONFIG_H
#define GPIO_MAPPER_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "gpio_mapper_types.h"
#include "gpio_mapper_dep.h"

typedef enum {
    GPIO_MAP_INIT_LEN = 1,
    GPIO_MAP_ERR_CODE = 2,
} GpioMapLegalNums_t;

extern const GpioMapperConfig_t GpioMapperConfig[];
extern GpioMapperHandle_t GpioMapperInstance[];

uint32_t gpio_mapper_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_MAPPER_CONFIG_H */
